TARGET  = firmware
CWD     ?= $(realpath $(CURDIR))
DOCKER 	?= docker run --rm -v $(CWD):$(CWD) -w $(CWD) mdashnet/armgcc
CROSS   ?= arm-none-eabi
CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
						-Wformat-truncation -fno-common -Wconversion \
						-g3 -Os -ffunction-sections -fdata-sections \
						-mcpu=cortex-m0 -mthumb -mfloat-abi=soft \
						-I.  $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = boot.c main.c syscalls.c

all build example: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(DOCKER) $(CROSS)-objcopy -O ihex $< $@

$(TARGET).elf: $(SOURCES) mcu.h
	$(DOCKER) $(CROSS)-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

# Show top 10 stack-hungry functions
su: CFLAGS += -fstack-usage
su: clean $(TARGET).elf
	cat *.su | sort -rnk2 | head -10

flash: $(TARGET).hex
	(echo device xmc1100-0064; echo si 1; echo speed 1000;\
		echo loadfile $?; echo reset; echo quit) | JLinkExe

clean:
	@rm -rf $(TARGET).* *.su
