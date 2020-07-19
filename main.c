#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "mmio.h"

#define GPIO_PIN_BUTTON 0
#define GPIO_PIN_LED3 13
#define GPIO_PIN_LED4 12
#define GPIO_PIN_LED5 14
#define GPIO_PIN_LED6 15

#define IRQ_EXTI0 6

static volatile int pattern = 0;

static void clock_enable(reg_t *clock, uint32_t bits) {
    *clock |= bits;
    (void)*clock;
}

static void led_init_gpio(int pin) {
    GPIO_OSPEEDR(GPIOD_BASE) |= GPIO_OSPEEDR_HI << (pin * 2);
    GPIO_OTYPER(GPIOD_BASE) |= GPIO_OTYPER_PP << pin;
    GPIO_PUPDR(GPIOD_BASE) |= GPIO_PUPDR_PU << (pin * 2);
    GPIO_MODER(GPIOD_BASE) |= GPIO_MODER_OUTPUT << (pin * 2);
}

static void led_init(void) {
    clock_enable(&RCC_AHB1ENR, RCC_AHB1ENR_GPIODEN);
    led_init_gpio(GPIO_PIN_LED3);
    led_init_gpio(GPIO_PIN_LED4);
    led_init_gpio(GPIO_PIN_LED5);
    led_init_gpio(GPIO_PIN_LED6);
}

static void led_set(int pin, bool on) {
    GPIO_BSRR(GPIOD_BASE) = ((1U << pin) << (on ? 0 : 16));
}

static void button_init_gpio(void) {
    clock_enable(&RCC_AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    GPIO_OSPEEDR(GPIOA_BASE) |= GPIO_OSPEEDR_HI << (GPIO_PIN_BUTTON * 2);
    GPIO_OTYPER(GPIOA_BASE) |= GPIO_OTYPER_PP << GPIO_PIN_BUTTON;
    GPIO_PUPDR(GPIOA_BASE) |= GPIO_PUPDR_NONE << (GPIO_PIN_BUTTON * 2);
    GPIO_MODER(GPIOA_BASE) |= GPIO_MODER_INPUT << (GPIO_PIN_BUTTON * 2);
}

static void exti_map_gpio(int exti, int port) {
    // System configuration controller is needed to manage EXTI so we
    // have to enable its clock here
    clock_enable(&RCC_APB2ENR, RCC_APB2ENR_SYSCFGEN);

    // EXTICR1 contains EXTI0-EXTI3, EXTICR2 contains EXTI4-EXTI7, etc.
    // Each register is 4 lines * 4 bits each, bits are 0 for port A,
    // 1 for port B, 2 for port C, etc.
    SYSCFG_EXTICR(exti / 4) |= (port << (4 * (exti % 4)));
}

static void exti_clear_irq(int exti) {
    EXTI_PR = (1U << exti);
}

static void button_init_exti(void) {
    // Connect GPIO port A to EXTI0
    exti_map_gpio(0 /* EXTI0 */, 0 /* GPIOA */);

    // Interrupt mode, raise on rising edge
    EXTI_IMR |= (1U << GPIO_PIN_BUTTON);
    EXTI_RTSR |= (1U << GPIO_PIN_BUTTON);
}

static void button_init_nvic(void) {
    NVIC_ISER(IRQ_EXTI0 / 32) = (1U << (IRQ_EXTI0 % 32));
}

static void button_init(bool interrupts) {
    button_init_gpio();
    if (interrupts) {
        button_init_exti();
        button_init_nvic();
    }
}

static bool button_get(void) {
    return (GPIO_IDR(GPIOA_BASE) & (1U << GPIO_PIN_BUTTON)) == (1U << GPIO_PIN_BUTTON);
}

static void handle_irq_button(void) {
    pattern = (pattern + 1) % 3;
    exti_clear_irq(GPIO_PIN_BUTTON);
}

static void halt(void) {
    while (1);
}

static void delay(void) {
    for (int i = 0; i < 200000; ++i) {
        asm volatile("nop");
    }
}

void isr(int n) {
    if (n < 16) {
        halt();
    } else if (n == 16 + IRQ_EXTI0) {
        handle_irq_button();
    }
}

int main(void) {
    led_init();
    button_init(true);

    for (int i = 0; ; ++i) {
        if (button_get()) {
            led_set(GPIO_PIN_LED3, true);
            led_set(GPIO_PIN_LED4, true);
            led_set(GPIO_PIN_LED6, true);
            led_set(GPIO_PIN_LED5, true);
            continue;
        }

        switch (pattern) {
        case 0:
            led_set(GPIO_PIN_LED3, (i + 0) % 4 == 0);
            led_set(GPIO_PIN_LED4, (i + 1) % 4 == 0);
            led_set(GPIO_PIN_LED6, (i + 2) % 4 == 0);
            led_set(GPIO_PIN_LED5, (i + 3) % 4 == 0);
            break;
        case 1:
            led_set(GPIO_PIN_LED3, (i + 0) % 8 >= 4);
            led_set(GPIO_PIN_LED4, (i + 1) % 8 >= 4);
            led_set(GPIO_PIN_LED6, (i + 2) % 8 >= 4);
            led_set(GPIO_PIN_LED5, (i + 3) % 8 >= 4);
            break;
        case 2:
            led_set(GPIO_PIN_LED3, i % 2 == 0);
            led_set(GPIO_PIN_LED4, i % 2 == 1);
            led_set(GPIO_PIN_LED6, i % 2 == 0);
            led_set(GPIO_PIN_LED5, i % 2 == 1);
            break;
        }

        delay();
    }
}
