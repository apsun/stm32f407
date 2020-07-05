#include "stdint.h"
#include "stdbool.h"
#include "mmio.h"

#define GPIO_PIN_LED3 13
#define GPIO_PIN_LED4 12
#define GPIO_PIN_LED5 14
#define GPIO_PIN_LED6 15

void gpio_clock_on(void) {
    *(reg_t *)RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    (void)*(reg_t *)RCC_AHB1ENR;
}

void gpio_set(int pin, bool on) {
    *(reg_t *)GPIOD_BSRR = ((1U << pin) << (on ? 0 : 16));
}

bool gpio_get(int pin) {
    return (*(reg_t *)GPIOD_ODR & (1U << pin)) == (1U << pin);
}

void gpio_init_for_led(int pin) {
    *(reg_t *)GPIOD_OSPEEDR |= GPIOD_OSPEEDR_HI << (pin * 2);
    *(reg_t *)GPIOD_OTYPER |= GPIOD_OTYPER_PP << pin;
    *(reg_t *)GPIOD_PUPDR |= GPIOD_PUPDR_PU << (pin * 2);
    *(reg_t *)GPIOD_MODER |= GPIOD_MODER_OUTPUT << (pin * 2);
}

void delay(void) {
    for (int i = 0; i < 200000; ++i) {
        __asm volatile("nop");
    }
}

int main(void) {
    gpio_clock_on();
    gpio_init_for_led(GPIO_PIN_LED3);
    gpio_init_for_led(GPIO_PIN_LED4);
    gpio_init_for_led(GPIO_PIN_LED5);
    gpio_init_for_led(GPIO_PIN_LED6);
    while (1) {
        for (int i = 0; i < 16; ++i) {
            gpio_set(GPIO_PIN_LED3, (i + 0) % 4 == 0);
            gpio_set(GPIO_PIN_LED4, (i + 1) % 4 == 0);
            gpio_set(GPIO_PIN_LED6, (i + 2) % 4 == 0);
            gpio_set(GPIO_PIN_LED5, (i + 3) % 4 == 0);
            delay();
        }

        for (int i = 0; i < 16; ++i) {
            gpio_set(GPIO_PIN_LED3, (i + 0) % 8 >= 4);
            gpio_set(GPIO_PIN_LED4, (i + 1) % 8 >= 4);
            gpio_set(GPIO_PIN_LED6, (i + 2) % 8 >= 4);
            gpio_set(GPIO_PIN_LED5, (i + 3) % 8 >= 4);
            delay();
        }

        for (int i = 0; i < 16; ++i) {
            gpio_set(GPIO_PIN_LED3, i % 2 == 0);
            gpio_set(GPIO_PIN_LED4, i % 2 == 1);
            gpio_set(GPIO_PIN_LED6, i % 2 == 0);
            gpio_set(GPIO_PIN_LED5, i % 2 == 1);
            delay();
        }
    }
}
