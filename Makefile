AR = arm-none-eabi-ar
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
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
	$(DB) -x openocd.gdbinit $<

.PHONY: objdump
objdump: rom.elf
	$(OBJDUMP) -dw $< | less

.PHONY: clean
clean:
	$(RM) rom.elf rom.bin *.o
