/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32H743ZI2_NUCLEO

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_UART3_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
		}
	}
}

#endif // #ifdef	STM32H743xx
