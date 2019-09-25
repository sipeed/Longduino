#include "pins_arduino.h"

#include "gd32vf103_libopt.h"



gpio_dev_t gpioa = {
    .gpio_port = GPIOA,
    .clk_id = RCU_GPIOA,
};

gpio_dev_t * const GPIO_A = &gpioa;

gpio_dev_t gpiob = {
    .gpio_port = GPIOB,
    .clk_id = RCU_GPIOB,
};

gpio_dev_t * const GPIO_B = &gpiob;

gpio_dev_t gpioc = {
    .gpio_port = GPIOC,
    .clk_id = RCU_GPIOC,
};

gpio_dev_t * const GPIO_C = &gpioc;

gpio_dev_t gpiod = {
    .gpio_port = GPIOD,
    .clk_id = RCU_GPIOD,
};

gpio_dev_t * const GPIO_D = &gpiod;

gpio_dev_t gpioe = {
    .gpio_port = GPIOE,
    .clk_id = RCU_GPIOE,
};
gpio_dev_t * const GPIO_E = &gpioe;

adc_dev_t adc0 = {
    .adc_dev = ADC0,
    .clk_id = RCU_ADC0,
};
adc_dev_t * const ADC_0 = &adc0;

// TODO: add timer remap descriptor

timer_dev_t timer0 = {
    .timer_dev = TIMER0,
    .clk_id = RCU_TIMER0,
};
timer_dev_t * const TIMER_0 = &timer0;

timer_dev_t timer1 = {
    .timer_dev = TIMER1,
    .clk_id = RCU_TIMER1,
};
timer_dev_t * const TIMER_1 = &timer1;

timer_dev_t timer2 = {
    .timer_dev = TIMER2,
    .clk_id = RCU_TIMER2,
};
timer_dev_t * const TIMER_2 = &timer2;

timer_dev_t timer3 = {
    .timer_dev = TIMER3,
    .clk_id = RCU_TIMER3,
};
timer_dev_t * const TIMER_3 = &timer3;

timer_dev_t timer4 = {
    .timer_dev = TIMER4,
    .clk_id = RCU_TIMER4,
};
timer_dev_t * const TIMER_4 = &timer4;

const gd32v_pin_info_t PIN_MAP[VARIANT_GPIO_NUM] = {
/*
    gpio_dev *gpio_device;      GPIO device 
    timer_dev *timer_device;    Pin's timer device, if any.
    const adc_dev *adc_device;  ADC device, if any. 
    uint8 gpio_bit;             Pin's GPIO port bit. 
    uint8 timer_channel;        Timer channel, or 0 if none. 
    uint8 adc_channel;          Pin ADC channel, or ADCx if none. 
*/
    {&gpioa, &timer1, &adc0, 0, 0, 0}, /* PA0 */
    {&gpioa, &timer1, &adc0, 1, 1, 1}, /* PA1 */
    {&gpioa, &timer1, &adc0, 2, 2, 2}, /* PA2 */
    {&gpioa, &timer1, &adc0, 3, 3, 3}, /* PA3 */
    {&gpioa, 0, &adc0, 4, 0, 4}, /* PA4 */
    {&gpioa, 0, &adc0, 5, 0, 5}, /* PA5 */
    {&gpioa, &timer2, &adc0, 6, 0, 6}, /* PA6 */
    {&gpioa, &timer2, &adc0, 7, 1, 7}, /* PA7 */
    {&gpioa, &timer0, 0, 8, 0, 0}, /* PA8 */
    {&gpioa, &timer0, 0, 9, 1, 0}, /* PA9 */
    {&gpioa, &timer0, 0, 10, 2, 0}, /* PA10 */
    {&gpioa, &timer0, 0, 11, 3, 0}, /* PA11 */
    {&gpioa, 0, 0, 12, 0, 0}, /* PA12 */
    {&gpioa, 0, 0, 13, 0, 0}, /* PA13 */
    {&gpioa, 0, 0, 14, 0, 0}, /* PA14 */
    {&gpioa, 0, 0, 15, 0, 0}, /* PA15 */

    {&gpiob, &timer2, &adc0, 0, 2, 8}, /* PB0 */
    {&gpiob, &timer2, &adc0, 1, 3, 9}, /* PB1 */
    {&gpiob, 0, 0, 2, 0, 0}, /* PB2 */
    {&gpiob, 0, 0, 3, 0, 0}, /* PB3 */
    {&gpiob, 0, 0, 4, 0, 0}, /* PB4 */
    {&gpiob, 0, 0, 5, 0, 0}, /* PB5 */
    {&gpiob, &timer3, 0, 6, 0, 0}, /* PB6 */
    {&gpiob, &timer3, 0, 7, 1, 0}, /* PB7 */
    {&gpiob, &timer3, 0, 8, 2, 0}, /* PB8 */
    {&gpiob, &timer3, 0, 9, 3, 0}, /* PB9 */
    {&gpiob, 0, 0, 10, 0, 0}, /* PB10 */
    {&gpiob, 0, 0, 11, 0, 0}, /* PB11 */
    {&gpiob, 0, 0, 12, 0, 0}, /* PB12 */
    {&gpiob, 0, 0, 13, 0, 0}, /* PB13 */
    {&gpiob, 0, 0, 14, 0, 0}, /* PB14 */
    {&gpiob, 0, 0, 15, 0, 0}, /* PB15 */

    {&gpioc, 0, &adc0, 0, 0, 10}, /* PC0 */
    {&gpioc, 0, &adc0, 1, 0, 11}, /* PC1 */
    {&gpioc, 0, &adc0, 2, 0, 12}, /* PC2 */
    {&gpioc, 0, &adc0, 3, 0, 13}, /* PC3 */
    {&gpioc, 0, &adc0, 4, 0, 14}, /* PC4 */
    {&gpioc, 0, &adc0, 5, 0, 15}, /* PC5 */
    {&gpioc, 0, 0, 6, 0, 0}, /* PC6 */
    {&gpioc, 0, 0, 7, 0, 0}, /* PC7 */
    {&gpioc, 0, 0, 8, 0, 0}, /* PC8 */
    {&gpioc, 0, 0, 9, 0, 0}, /* PC9 */
    {&gpioc, 0, 0, 10, 0, 0}, /* PC10 */
    {&gpioc, 0, 0, 11, 0, 0}, /* PC11 */
    {&gpioc, 0, 0, 12, 0, 0}, /* PC12 */
    {&gpioc, 0, 0, 13, 0, 0}, /* PC13 */
    {&gpioc, 0, 0, 14, 0, 0}, /* PC14 */
    {&gpioc, 0, 0, 15, 0, 0}, /* PC15 */

    {&gpiod, 0, 0, 0, 0, 0}, /* PD0 */
    {&gpiod, 0, 0, 1, 0, 0}, /* PD1 */
    {&gpiod, 0, 0, 2, 0, 0}, /* PD2 */
    {&gpiod, 0, 0, 3, 0, 0}, /* PD3 */
    {&gpiod, 0, 0, 4, 0, 0}, /* PD4 */
    {&gpiod, 0, 0, 5, 0, 0}, /* PD5 */
    {&gpiod, 0, 0, 6, 0, 0}, /* PD6 */
    {&gpiod, 0, 0, 7, 0, 0}, /* PD7 */
    {&gpiod, 0, 0, 8, 0, 0}, /* PD8 */
    {&gpiod, 0, 0, 9, 0, 0}, /* PD9 */
    {&gpiod, 0, 0, 10, 0, 0}, /* PD10 */
    {&gpiod, 0, 0, 11, 0, 0}, /* PD11 */
    {&gpiod, 0, 0, 12, 0, 0}, /* PD12 */
    {&gpiod, 0, 0, 13, 0, 0}, /* PD13 */
    {&gpiod, 0, 0, 14, 0, 0}, /* PD14 */
    {&gpiod, 0, 0, 15, 0, 0}, /* PD15 */

    {&gpioe, 0, 0, 0, 0, 0}, /* PE0 */
    {&gpioe, 0, 0, 1, 0, 0}, /* PE1 */
    {&gpioe, 0, 0, 2, 0, 0}, /* PE2 */
    {&gpioe, 0, 0, 3, 0, 0}, /* PE3 */
    {&gpioe, 0, 0, 4, 0, 0}, /* PE4 */
    {&gpioe, 0, 0, 5, 0, 0}, /* PE5 */
    {&gpioe, 0, 0, 6, 0, 0}, /* PE6 */
    {&gpioe, 0, 0, 7, 0, 0}, /* PE7 */
    {&gpioe, 0, 0, 8, 0, 0}, /* PE8 */
    {&gpioe, 0, 0, 9, 0, 0}, /* PE9 */
    {&gpioe, 0, 0, 10, 0, 0}, /* PE10 */
    {&gpioe, 0, 0, 11, 0, 0}, /* PE11 */
    {&gpioe, 0, 0, 12, 0, 0}, /* PE12 */
    {&gpioe, 0, 0, 13, 0, 0}, /* PE13 */
    {&gpioe, 0, 0, 14, 0, 0}, /* PE14 */
    {&gpioe, 0, 0, 15, 0, 0}, /* PE15 */
};


