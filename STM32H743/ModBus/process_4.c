/*
 * process_4.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../A_os/kernel/A.h"
#include "../../A_os/kernel/A_exported_functions.h"

void process_4(uint32_t process_id)
{
uint32_t	wakeup;
	create_timer(TIMER_ID_0,800,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	allocate_hw(HW_SPI1,0);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			wakeup=0;

		}
	}
}
