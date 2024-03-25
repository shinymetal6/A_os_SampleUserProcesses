/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32U575xx

void process_2(uint32_t process_id)
{
uint32_t	wakeup,flags,counter = 0;
	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER );
		get_wakeup_flags(&wakeup,&flags);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			counter++;
			if ( counter > 4 )
			{
				HAL_GPIO_WritePin(LED_3_GPIOPORT, LED_3_GPIOBIT,GPIO_PIN_RESET);
				//dfu_run_bootloader();
			}
		}
	}
}

#endif // #ifdef	STM32H743xx

