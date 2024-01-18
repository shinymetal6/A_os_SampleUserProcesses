/*
 * process_3.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

uint8_t	nrf_address[5] = {0xb3,0xb4,0xb5,0xb6,0x05};

void process_3_SPItest(uint32_t process_id)
{
uint32_t	wakeup;

	HAL_GPIO_WritePin( SX126X_RESET_GPIO_Port, SX126X_RESET_Pin,GPIO_PIN_RESET);
	create_timer(TIMER_ID_0,500,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
		    HAL_GPIO_WritePin( SX126X_RESET_GPIO_Port, SX126X_RESET_Pin,GPIO_PIN_SET);
			SX126xGetCRCRegs();
			//HAL_GPIO_TogglePin(NRF24L01_SS_PIN_PORT, NRF24L01_SS_PIN_NUMBER);


		}
	}
}
