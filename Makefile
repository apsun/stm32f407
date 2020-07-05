AR = arm-none-eabi-ar
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
DB = arm-none-eabi-gdb

CFLAGS += -Wall -Wextra -nostdinc -ffreestanding -mthumb -mcpu=cortex-m4 -g -Og
LDFLAGS += -Tlinker.ld -nostdlib -static

all: rom.bin

rom.bin: rom.elf
	$(OBJCOPY) -O binary $< $@

rom.elf: main.o startup.o
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: install
install: rom.bin
	st-flash write $< 0x8000000

.PHONY: debug
debug: rom.elf install
	$(DB) -x openocd.gdbinit rom.elf

.PHONY: clean
clean:
	$(RM) rom.elf rom.bin *.o
