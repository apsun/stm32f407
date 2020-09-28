AR = arm-none-eabi-ar
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
DB = arm-none-eabi-gdb

CFLAGS += -Wall -Wextra -nostdinc -ffreestanding -mthumb -mcpu=cortex-m4 -g -Og
LDFLAGS += -Tlinker.ld -nostdlib -static -Wl,--gc-sections

all: rom.bin

rom.bin: rom.elf
	$(OBJCOPY) -O binary $< $@

rom.elf: main.o startup.o libjustrust.a
	$(CC) $(LDFLAGS) $^ -o $@

libjustrust.a: justrust/src/lib.rs
	cargo build --manifest-path justrust/Cargo.toml --target=thumbv7em-none-eabi --release -q
	cp justrust/target/thumbv7em-none-eabi/release/libjustrust.a .

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
	$(RM) rom.elf rom.bin *.o *.a
	cargo clean --manifest-path justrust/Cargo.toml
