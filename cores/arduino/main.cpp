#define ARDUINO_MAIN
#include "Arduino.h"
#include "ArduinoAPI.h"
#include "Common.h"
#include "gd32vf103_libopt.h"


#define cmb() __asm__ __volatile__ ("" ::: "memory")
extern "C"{ void * __dso_handle = 0 ;}

void com_init(uint32_t com)
{
    if(com == USART0){
        /* enable GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /* enable USART clock */
        rcu_periph_clock_enable(RCU_USART0);
        /* connect port to USARTx_Tx */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        /* connect port to USARTx_Rx */
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    }else if(com == USART1){
        /* enable GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /* enable USART clock */
        rcu_periph_clock_enable(RCU_USART1);
        /* connect port to USARTx_Tx */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

        /* connect port to USARTx_Rx */
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    }else{
        return;
    }
    /* USART configure */
    usart_deinit(com);
    usart_baudrate_set(com, 115200U);
    usart_word_length_set(com, USART_WL_8BIT);
    usart_stop_bit_set(com, USART_STB_1BIT);
    usart_parity_config(com, USART_PM_NONE);
    usart_hardware_flow_rts_config(com, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(com, USART_CTS_DISABLE);
    usart_receive_config(com, USART_RECEIVE_ENABLE);
    usart_transmit_config(com, USART_TRANSMIT_ENABLE);
    usart_enable(com);
    return;
}

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
    com_init(USART0);

    setup();
  
    do {
        loop();
        //if (serialEventRun)
        //  serialEventRun();
    } while (1);

    return 0;
}
