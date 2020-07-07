This repo contains random stuff that I use to play around with my
STM32F4DISCOVERY board. The goal is to have a complete end to end
development workflow using only basic Unix tools (i.e. make, gcc,
gdb, your text editor of choice, etc).

Massive disclaimer: I have literally no experience with the ARM
architecture. Do not take anything in this repo and run it in prod.

Want to follow along at home? You can buy this board in the US
[here](https://www.newark.com/stmicroelectronics/stm32f407g-disc1/dev-board-foundation-line-mcu/dp/72Y1168?st=STM32F407G-DISC1).

The reference manual can be found [here](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405415-stm32f407417-stm32f427437-and-stm32f429439-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
and documents the system architecture and registers.

The [ARMv7-M reference manual](https://static.docs.arm.com/ddi0403/eb/DDI0403E_B_armv7m_arm.pdf)
contains a reference for the instruction set. Be careful not to
accidentally use the ARMv7-A/R manual; it is completely different
from the ARMv7-M manual.

The [STM32CubeF4 projects](https://github.com/STMicroelectronics/STM32CubeF4)
can also be super useful as a code reference.

List of tools you'll need:
- gcc and gdb cross compiled for ARM
- openocd (for debugging)
- stlink (for flashing the board)

Running `make install` will flash the board. `make debug` will
do the same and start gdb afterwards.
