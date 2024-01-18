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
 * Project : bb1xx_743_00 
*/
/*
 * process_3.c
 *
 *  Created on: Jan 3, 2024
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"


void process_3(uint32_t process_id)
{
uint32_t	wakeup;

	create_timer(TIMER_ID_0,500,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
	}
}
