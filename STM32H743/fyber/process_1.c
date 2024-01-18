/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

void process_1(uint32_t process_id)
{
uint32_t	wakeup;
	create_timer(TIMER_ID_0,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER | EVENT_UART3_IRQ);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
	}
}

