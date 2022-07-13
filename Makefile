TARGET  = firmware
CROSS   ?= arm-none-eabi
CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
						-Wformat-truncation -fno-common -Wconversion \
						-g3 -Os -ffunction-sections -fdata-sections \
						-mcpu=cortex-m0 -mthumb -mfloat-abi=soft \
						-I. $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = boot.c main.c syscalls.c

all build example: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(CROSS)-objcopy -O ihex $< $@

$(TARGET).elf: $(SOURCES) mcu.h
	$(CROSS)-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

# Show top 10 stack-hungry functions
su: CFLAGS += -fstack-usage
su: clean $(TARGET).elf
	cat *.su | sort -rnk2 | head -10

flash: $(TARGET).hex
	(echo device xmc1100-0064; echo si 1; echo speed 4000;\
		echo loadfile $?; echo reset; echo quit) | JLinkExe

gdb-server:
	JLinkGDBServerCLExe -device xmc1100-0064 -if swd -speed 1000

gdb: $(TARGET).elf
	$(CROSS)-gdb -q \
  -ex 'set confirm off' \
  -ex 'file $(TARGET).elf' \
  -ex 'target remote :2331' \
  -ex 'monitor reset' \
  -ex 'load ' \
  -ex 'b main' \
  -ex 'continue'

clean:
	@rm -rf $(TARGET).* *.su
