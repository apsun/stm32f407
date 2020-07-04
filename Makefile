AR = arm-none-eabi-ar
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS += -Wall -Wextra -Werror -nostdinc -ffreestanding
LDFLAGS += -Tlinker.ld -nostdlib -static

all: rom.bin

rom.bin: rom.elf
	$(OBJCOPY) -O binary $< $@

rom.elf: main.o startup.o
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: install
install: rom.bin
	st-flash write $< 0x8000000

.PHONY: clean
clean:
	$(RM) rom.elf rom.bin *.o
