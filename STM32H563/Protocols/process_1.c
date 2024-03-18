/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"
#ifdef	STM32H563xx

//#define	USE_XMODEM
#define	USE_MODBUS

#ifdef	USE_XMODEM

#define	xmodem_data_area	0x20020000

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
	allocate_hw(HW_UART3,0);
	xmodem_init(HW_UART3,(uint8_t *)xmodem_data_area);
	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_UART1_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			xmodem_process(wakeup);
			HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
		}
		if (( wakeup & WAKEUP_FROM_UART3_IRQ) == WAKEUP_FROM_UART3_IRQ)
		{
			if (( flags & WAKEUP_FLAGS_UART_RX) == WAKEUP_FLAGS_UART_RX )
			{
				HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
				xmodem_process(wakeup);
			}
		}
	}
}
#endif

#ifdef	USE_MODBUS
#define	LOCAL_MODBUS_BUFFERLEN		513
uint8_t 	modbus_rx_buf[LOCAL_MODBUS_BUFFERLEN];
#define	LOCAL_MODBUS_ADDRESS		1

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags,modbus_error=0;
	allocate_hw(HW_UART3,0);
	if ( modbus_init(HW_UART3,LOCAL_MODBUS_ADDRESS,modbus_rx_buf,LOCAL_MODBUS_BUFFERLEN) != 0 )
		modbus_error=1;

	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_UART3_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( modbus_error == 0 )
			{
				HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
				if ( modbus_get_coil(0) )
					HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_SET);
				else
					HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_RESET);
				if ( modbus_get_coil(1) )
					HAL_GPIO_WritePin(LED_2_GPIOPORT, LED_2_GPIOBIT,GPIO_PIN_SET);
				else
					HAL_GPIO_WritePin(LED_2_GPIOPORT, LED_2_GPIOBIT,GPIO_PIN_RESET);
			}
			else
				HAL_GPIO_WritePin(LED_3_GPIOPORT, LED_3_GPIOBIT,GPIO_PIN_SET);
		}
		if (( wakeup & WAKEUP_FROM_UART3_IRQ) == WAKEUP_FROM_UART3_IRQ)
		{
			if (( flags & WAKEUP_FLAGS_UART_RX) == WAKEUP_FLAGS_UART_RX )
			{
				if ( modbus_process() == 0)
				{

				}
			}
		}
	}
}
#endif

#endif // #ifdef	STM32H563xx

