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


extern const gd32v_pin_info_t PIN_MAP[VARIANT_GPIO_NUM] = {
/*
    gpio_dev *gpio_device;      GPIO device 
    timer_dev *timer_device;    Pin's timer device, if any.
    const adc_dev *adc_device;  ADC device, if any. 
    uint8 gpio_bit;             Pin's GPIO port bit. 
    uint8 timer_channel;        Timer channel, or 0 if none. 
    uint8 adc_channel;          Pin ADC channel, or ADCx if none. 
*/
    {&gpioa, /*&timer2*/&adc0, 0 /*, 1*/, 0}, /* PA0 */
    {&gpioa, /*&timer2*/&adc0, 1 /*, 1*/, 1}, /* PA1 */
    {&gpioa, /*&timer2*/&adc0, 2 /*, 1*/, 2}, /* PA2 */
    {&gpioa, /*&timer2*/&adc0, 3 /*, 1*/, 3}, /* PA3 */
    {&gpioa, /*&timer2*/&adc0, 4 /*, 1*/, 4}, /* PA4 */
    {&gpioa, /*&timer2*/&adc0, 5 /*, 1*/, 5}, /* PA5 */
    {&gpioa, /*&timer2*/&adc0, 6 /*, 1*/, 6}, /* PA6 */
    {&gpioa, /*&timer2*/&adc0, 7 /*, 1*/, 7}, /* PA7 */
    {&gpioa, /*&timer2*/0, 8 /*, 1*/, 0}, /* PA8 */
    {&gpioa, /*&timer2*/0, 9 /*, 1*/, 0}, /* PA9 */
    {&gpioa, /*&timer2*/0, 10 /*, 1*/, 0}, /* PA10 */
    {&gpioa, /*&timer2*/0, 11 /*, 1*/, 0}, /* PA11 */
    {&gpioa, /*&timer2*/0, 12 /*, 1*/, 0}, /* PA12 */
    {&gpioa, /*&timer2*/0, 13 /*, 1*/, 0}, /* PA13 */
    {&gpioa, /*&timer2*/0, 14 /*, 1*/, 0}, /* PA14 */
    {&gpioa, /*&timer2*/0, 15 /*, 1*/, 0}, /* PA15 */

    {&gpiob, /*&timer2*/&adc0, 0 /*, 1*/, 8}, /* PB0 */
    {&gpiob, /*&timer2*/&adc0, 1 /*, 1*/, 9}, /* PB1 */
    {&gpiob, /*&timer2*/0, 2 /*, 1*/, 0}, /* PB2 */
    {&gpiob, /*&timer2*/0, 3 /*, 1*/, 0}, /* PB3 */
    {&gpiob, /*&timer2*/0, 4 /*, 1*/, 0}, /* PB4 */
    {&gpiob, /*&timer2*/0, 5 /*, 1*/, 0}, /* PB5 */
    {&gpiob, /*&timer2*/0, 6 /*, 1*/, 0}, /* PB6 */
    {&gpiob, /*&timer2*/0, 7 /*, 1*/, 0}, /* PB7 */
    {&gpiob, /*&timer2*/0, 8 /*, 1*/, 0}, /* PB8 */
    {&gpiob, /*&timer2*/0, 9 /*, 1*/, 0}, /* PB9 */
    {&gpiob, /*&timer2*/0, 10 /*, 1*/, 0}, /* PB10 */
    {&gpiob, /*&timer2*/0, 11 /*, 1*/, 0}, /* PB11 */
    {&gpiob, /*&timer2*/0, 12 /*, 1*/, 0}, /* PB12 */
    {&gpiob, /*&timer2*/0, 13 /*, 1*/, 0}, /* PB13 */
    {&gpiob, /*&timer2*/0, 14 /*, 1*/, 0}, /* PB14 */
    {&gpiob, /*&timer2*/0, 15 /*, 1*/, 0}, /* PB15 */

    {&gpioc, /*&timer2*/&adc0, 0 /*, 1*/, 10}, /* PC0 */
    {&gpioc, /*&timer2*/&adc0, 1 /*, 1*/, 11}, /* PC1 */
    {&gpioc, /*&timer2*/&adc0, 2 /*, 1*/, 12}, /* PC2 */
    {&gpioc, /*&timer2*/&adc0, 3 /*, 1*/, 13}, /* PC3 */
    {&gpioc, /*&timer2*/&adc0, 4 /*, 1*/, 14}, /* PC4 */
    {&gpioc, /*&timer2*/&adc0, 5 /*, 1*/, 15}, /* PC5 */
    {&gpioc, /*&timer2*/0, 6 /*, 1*/, 0}, /* PC6 */
    {&gpioc, /*&timer2*/0, 7 /*, 1*/, 0}, /* PC7 */
    {&gpioc, /*&timer2*/0, 8 /*, 1*/, 0}, /* PC8 */
    {&gpioc, /*&timer2*/0, 9 /*, 1*/, 0}, /* PC9 */
    {&gpioc, /*&timer2*/0, 10 /*, 1*/, 0}, /* PC10 */
    {&gpioc, /*&timer2*/0, 11 /*, 1*/, 0}, /* PC11 */
    {&gpioc, /*&timer2*/0, 12 /*, 1*/, 0}, /* PC12 */
    {&gpioc, /*&timer2*/0, 13 /*, 1*/, 0}, /* PC13 */
    {&gpioc, /*&timer2*/0, 14 /*, 1*/, 0}, /* PC14 */
    {&gpioc, /*&timer2*/0, 15 /*, 1*/, 0}, /* PC15 */

    {&gpiod, /*&timer2*/0, 0 /*, 1*/, 0}, /* PD0 */
    {&gpiod, /*&timer2*/0, 1 /*, 1*/, 0}, /* PD1 */
    {&gpiod, /*&timer2*/0, 2 /*, 1*/, 0}, /* PD2 */
    {&gpiod, /*&timer2*/0, 3 /*, 1*/, 0}, /* PD3 */
    {&gpiod, /*&timer2*/0, 4 /*, 1*/, 0}, /* PD4 */
    {&gpiod, /*&timer2*/0, 5 /*, 1*/, 0}, /* PD5 */
    {&gpiod, /*&timer2*/0, 6 /*, 1*/, 0}, /* PD6 */
    {&gpiod, /*&timer2*/0, 7 /*, 1*/, 0}, /* PD7 */
    {&gpiod, /*&timer2*/0, 8 /*, 1*/, 0}, /* PD8 */
    {&gpiod, /*&timer2*/0, 9 /*, 1*/, 0}, /* PD9 */
    {&gpiod, /*&timer2*/0, 10 /*, 1*/, 0}, /* PD10 */
    {&gpiod, /*&timer2*/0, 11 /*, 1*/, 0}, /* PD11 */
    {&gpiod, /*&timer2*/0, 12 /*, 1*/, 0}, /* PD12 */
    {&gpiod, /*&timer2*/0, 13 /*, 1*/, 0}, /* PD13 */
    {&gpiod, /*&timer2*/0, 14 /*, 1*/, 0}, /* PD14 */
    {&gpiod, /*&timer2*/0, 15 /*, 1*/, 0}, /* PD15 */

    {&gpioe, /*&timer2*/0, 0 /*, 1*/, 0}, /* PE0 */
    {&gpioe, /*&timer2*/0, 1 /*, 1*/, 0}, /* PE1 */
    {&gpioe, /*&timer2*/0, 2 /*, 1*/, 0}, /* PE2 */
    {&gpioe, /*&timer2*/0, 3 /*, 1*/, 0}, /* PE3 */
    {&gpioe, /*&timer2*/0, 4 /*, 1*/, 0}, /* PE4 */
    {&gpioe, /*&timer2*/0, 5 /*, 1*/, 0}, /* PE5 */
    {&gpioe, /*&timer2*/0, 6 /*, 1*/, 0}, /* PE6 */
    {&gpioe, /*&timer2*/0, 7 /*, 1*/, 0}, /* PE7 */
    {&gpioe, /*&timer2*/0, 8 /*, 1*/, 0}, /* PE8 */
    {&gpioe, /*&timer2*/0, 9 /*, 1*/, 0}, /* PE9 */
    {&gpioe, /*&timer2*/0, 10 /*, 1*/, 0}, /* PE10 */
    {&gpioe, /*&timer2*/0, 11 /*, 1*/, 0}, /* PE11 */
    {&gpioe, /*&timer2*/0, 12 /*, 1*/, 0}, /* PE12 */
    {&gpioe, /*&timer2*/0, 13 /*, 1*/, 0}, /* PE13 */
    {&gpioe, /*&timer2*/0, 14 /*, 1*/, 0}, /* PE14 */
    {&gpioe, /*&timer2*/0, 15 /*, 1*/, 0}, /* PE15 */

};


