/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../A_os/kernel/A.h"
#include "../../A_os/kernel/A_exported_functions.h"
#include "../../A_os/kernel/system_default.h"

#define	PRC1_I2C				HW_I2C1

__attribute__ ((long_call, section (".code_in_pram")))   void process_2(uint32_t process_id)
{
uint32_t	wakeup;

	create_timer(TIMER_ID_0,400,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	allocate_hw(PRC1_I2C,0);

	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			/*
			HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
			HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
			HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
			*/
		}
	}
}

