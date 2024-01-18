/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

__attribute__ ((long_call, section (".code_in_pram")))   void process_2(uint32_t process_id)
{
uint32_t	wakeup;
	create_timer(TIMER_ID_0,400,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			wakeup=0;
		}

	}
}

