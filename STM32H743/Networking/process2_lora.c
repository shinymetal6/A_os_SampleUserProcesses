/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : fy-201023-00 
*/
/*
 * process2_lora.c
 *
 *  Created on: Dec 28, 2023
 *      Author: fil
 */
#include "main.h"
#include "../../A_os/kernel/A.h"
#include "../../A_os/kernel/A_exported_functions.h"
#include "../../A_os/kernel/system_default.h"

#include <stdio.h>
#include <string.h>

void process2_lora(uint32_t process_id)
{
uint32_t	wakeup;

	sx1278_Init();
	create_timer(TIMER_ID_0,800,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			wakeup=0;
		}
	}
}

