/*
 * process_4.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32H743xx

void process_4(uint32_t process_id)
{
	wait_event(HW_SLEEP_FOREVER);
}

#endif //#ifdef	STM32H743xx
