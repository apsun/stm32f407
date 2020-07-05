#include "stdint.h"
#include "stdbool.h"
#include "mmio.h"

#define GPIO_PIN_LED3 13
#define GPIO_PIN_LED4 12
#define GPIO_PIN_LED5 14
#define GPIO_PIN_LED6 15

void gpio_clock_on(void) {
    *(reg_t *)RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}

void gpio_set(int pin, bool on) {
    *(reg_t *)GPIOD_BSRR = ((1U << pin) << ((uint32_t)on << 4U));
}

bool gpio_get(int pin) {
    return (*(reg_t *)GPIOD_ODR & (1 << pin)) == (1U << pin);
}

void gpio_init_for_led(int pin) {
    *(reg_t *)GPIOD_OSPEEDR |= GPIOD_OSPEEDR_HI << (pin * 2U);
    *(reg_t *)GPIOD_OTYPER |= GPIOD_OTYPER_PP;
    *(reg_t *)GPIOD_PUPDR |= GPIOD_PUPDR_PU << (pin * 2U);
    *(reg_t *)GPIOD_MODER |= GPIOD_MODER_OUTPUT << (pin * 2U);
}

int main(void) {
    gpio_clock_on();
    gpio_init_for_led(GPIO_PIN_LED3);
    gpio_init_for_led(GPIO_PIN_LED4);
    gpio_init_for_led(GPIO_PIN_LED5);
    gpio_init_for_led(GPIO_PIN_LED6);
    gpio_set(GPIO_PIN_LED4, true);
    while (1) {
    }
    return 0;
}
