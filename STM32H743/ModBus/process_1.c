/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../A_os/kernel/A.h"
#include "../../A_os/kernel/A_exported_functions.h"
#include "../../A_os/kernel/system_default.h"
#include <string.h>
#include <stdio.h>

extern	USRprcs_t	UserProcesses[USR_PROCESS_NUMBER];

uint8_t A_write_coil_from_modbus(uint16_t coil_index, uint8_t coil_value)
{
	if ( coil_index == 0 )
	{
		if ( coil_value == 0 )
		{
			HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_SET);
		}
	}
/*
	if ( coil_index == 1 )
	{
		if ( coil_value == 0 )
		{
			HAL_GPIO_WritePin(LED_2_GPIOPORT, LED_2_GPIOBIT,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_2_GPIOPORT, LED_2_GPIOBIT,GPIO_PIN_SET);
		}
	}
*/
	if ( coil_index == 2 )
	{
		if ( coil_value == 0 )
		{
			HAL_GPIO_WritePin(LED_3_GPIOPORT, LED_3_GPIOBIT,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_3_GPIOPORT, LED_3_GPIOBIT,GPIO_PIN_SET);
		}
	}

	return 0;
}

#define	UART_INTERCHAR_TIMEOUT	10
#define	MODBUS_ADDRESS			1
#define	MODBUS_RTU_MODE			0x80
#define	MODBUS_BUFFER_LEN		64

#ifdef	STM32H743xx
#define	PRC1_UART				HW_UART3
#endif

void process_1(uint32_t process_id)
{
uint32_t	wakeup;
uint8_t 	*modbus_rx_buf;
	allocate_hw(PRC1_UART,(uint32_t )&CONSOLE);
	modbus_rx_buf = mem_get(MODBUS_BUFFER_LEN);

	hw_receive_uart(PRC1_UART,modbus_rx_buf,MODBUS_BUFFER_LEN,UART_INTERCHAR_TIMEOUT);
	A_modbus_init(MODBUS_ADDRESS,MODBUS_RTU_MODE,PRC1_UART);
	create_timer(TIMER_ID_0,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER | EVENT_UART3_IRQ);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			A_set_in_to_modbus(0,HAL_GPIO_ReadPin(BUTTON_GPIOPORT, BUTTON_GPIOBIT));
			//HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);

		}
		if (( wakeup & WAKEUP_FROM_UART3_IRQ) == WAKEUP_FROM_UART3_IRQ)
		{
			A_modbus_process(modbus_rx_buf,hw_get_uart_receive_len(PRC1_UART));
		}
	}
}

