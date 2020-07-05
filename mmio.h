#ifndef MMIO_H
#define MMIO_H

typedef volatile uint32_t reg_t;

#define PERIPH_BASE                     0x40000000UL
  #define AHB1PERIPH_BASE               (PERIPH_BASE + 0x00020000UL)
    #define RCC_BASE                    (AHB1PERIPH_BASE + 0x3800UL)
      #define RCC_AHB1ENR               (RCC_BASE + 0x30UL)
        #define RCC_AHB1ENR_GPIODEN     (1 << 3)
    #define GPIOD_BASE                  (AHB1PERIPH_BASE + 0x0C00UL)
      #define GPIOD_OSPEEDR             (GPIOD_BASE + 0x08UL)
        #define GPIOD_OSPEEDR_LOW       0x0
        #define GPIOD_OSPEEDR_MED       0x1
        #define GPIOD_OSPEEDR_HI        0x2
        #define GPIOD_OSPEEDR_VERYHI    0x3
      #define GPIOD_OTYPER              (GPIOD_BASE + 0x04UL)
        #define GPIOD_OTYPER_PP         0x0
        #define GPIOD_OTYPER_OD         0x1
      #define GPIOD_PUPDR               (GPIOD_BASE + 0x0CUL)
        #define GPIOD_PUPDR_NONE        0x0
        #define GPIOD_PUPDR_PU          0x1
        #define GPIOD_PUPDR_PD          0x2
      #define GPIOD_MODER               (GPIOD_BASE + 0x00UL)
        #define GPIOD_MODER_INPUT       0x0
        #define GPIOD_MODER_OUTPUT      0x1
        #define GPIOD_MODER_ALT         0x2
        #define GPIOD_MODER_ANALOG      0x3
      #define GPIOD_BSRR                (GPIOD_BASE + 0x18UL)
      #define GPIOD_ODR                 (GPIOD_BASE + 0x14UL)

#endif
