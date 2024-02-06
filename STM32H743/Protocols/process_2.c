/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

void process_2(uint32_t process_id)
{
uint32_t	wakeup,flags;
	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER );
		get_wakeup_flags(&wakeup,&flags);

	}
}


