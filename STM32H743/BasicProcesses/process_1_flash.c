/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

uint8_t qspi_dataw[128],qspi_datar[128];

void process_1_flash(uint32_t process_id)
{
	uint32_t	wakeup;

		allocate_hw(HW_QSPI);
		A_qspi_init();
		A_qspi_read(qspi_datar,0, 64);
		if ( qspi_datar[0] != 'C' )
		{
			A_qspi_erase_block(0);
			A_qspi_enable_write();
			sprintf((char *)qspi_dataw,"Ciao Fil\n\r");
			A_qspi_write(qspi_dataw,0, 64);
			A_qspi_disable_write();
		}

		create_timer(TIMER_ID_0,500,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
		while(1)
		{
			wakeup = wait_event(EVENT_TIMER );
			if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
			{
				//HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
				A_qspi_read(qspi_datar,0, 64);
				bzero((char *)qspi_datar,64);
			}
		}
}

