#ifndef MMIO_H
#define MMIO_H

typedef volatile uint32_t reg_t;

#define REG(addr) (*(reg_t *)(addr))

#define SCS_BASE                        0xE000E000UL
  #define NVIC_BASE                     (SCS_BASE + 0x100UL)
    #define NVIC_ISER(n)                REG(NVIC_BASE + 0x000UL + (n) * 4UL)
    #define NVIC_ICER(n)                REG(NVIC_BASE + 0x080UL + (n) * 4UL)
    #define NVIC_ISPR(n)                REG(NVIC_BASE + 0x100UL + (n) * 4UL)
    #define NVIC_ICPR(n)                REG(NVIC_BASE + 0x180UL + (n) * 4UL)
    #define NVIC_IABR(n)                REG(NVIC_BASE + 0x200UL + (n) * 4UL)

#define PERIPH_BASE                     0x40000000UL
  #define APB2PERIPH_BASE               (PERIPH_BASE + 0x00010000UL)
    #define SYSCFG_BASE                 (APB2PERIPH_BASE + 0x3800UL)
      #define SYSCFG_EXTICR(n)          REG(SYSCFG_BASE + 0x08UL + (n) * 4UL)
    #define EXTI_BASE                   (APB2PERIPH_BASE + 0x3C00UL)
      #define EXTI_IMR                  REG(EXTI_BASE + 0x00UL)
      #define EXTI_RTSR                 REG(EXTI_BASE + 0x08UL)
      #define EXTI_FTSR                 REG(EXTI_BASE + 0x0CUL)
      #define EXTI_PR                   REG(EXTI_BASE + 0x14UL)
  #define AHB1PERIPH_BASE               (PERIPH_BASE + 0x00020000UL)
    #define RCC_BASE                    (AHB1PERIPH_BASE + 0x3800UL)
      #define RCC_AHB1ENR               REG(RCC_BASE + 0x30UL)
        #define RCC_AHB1ENR_GPIOAEN     (1 << 0)
        #define RCC_AHB1ENR_GPIODEN     (1 << 3)
      #define RCC_APB2ENR               REG(RCC_BASE + 0x44UL)
        #define RCC_APB2ENR_SYSCFGEN    (1 << 14)
    #define GPIOA_BASE                  (AHB1PERIPH_BASE + 0x0000UL)
    #define GPIOD_BASE                  (AHB1PERIPH_BASE + 0x0C00UL)
      #define GPIO_OSPEEDR(base)        REG((base) + 0x08UL)
        #define GPIO_OSPEEDR_LOW        0x0
        #define GPIO_OSPEEDR_MED        0x1
        #define GPIO_OSPEEDR_HI         0x2
        #define GPIO_OSPEEDR_VERYHI     0x3
      #define GPIO_OTYPER(base)         REG((base) + 0x04UL)
        #define GPIO_OTYPER_PP          0x0
        #define GPIO_OTYPER_OD          0x1
      #define GPIO_PUPDR(base)          REG((base) + 0x0CUL)
        #define GPIO_PUPDR_NONE         0x0
        #define GPIO_PUPDR_PU           0x1
        #define GPIO_PUPDR_PD           0x2
      #define GPIO_MODER(base)          REG((base) + 0x00UL)
        #define GPIO_MODER_INPUT        0x0
        #define GPIO_MODER_OUTPUT       0x1
        #define GPIO_MODER_ALT          0x2
        #define GPIO_MODER_ANALOG       0x3
      #define GPIO_IDR(base)            REG((base) + 0x10UL)
      #define GPIO_ODR(base)            REG((base) + 0x14UL)
      #define GPIO_BSRR(base)           REG((base) + 0x18UL)

#endif
