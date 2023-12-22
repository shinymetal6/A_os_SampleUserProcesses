/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../../A_os/kernel/A.h"
#include "../../../A_os/kernel/A_exported_functions.h"
#include "../../../A_os/kernel/system_default.h"
#include <string.h>
#include <stdio.h>

extern	USRprcs_t	UserProcesses[USR_PROCESS_NUMBER];


uint8_t* qspi_data[128];

void process_1(uint32_t process_id)
{
uint32_t	wakeup;
QSPI_HandleTypeDef	*A_hqspi;

	allocate_hw(HW_QSPI);
	A_qspi_init();

	create_timer(TIMER_ID_0,500,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER );
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
			//A_qspi_read(A_hqspi,qspi_data,0, 128);
		}
	}
}

