/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef STM32L431xx

#define	MAG_LEN					6
#define	MAG_LEN_BUFFER_LEN		(MAG_LEN * 1024)

uint8_t	axis_regs[MAG_LEN_BUFFER_LEN];
void sensors_power_on(void)
{
	HAL_GPIO_WritePin(SENSPOWER_GPIOPORT, SENSPOWER_GPIOBIT, GPIO_PIN_SET);
}

void sensors_power_off(void)
{
	HAL_GPIO_WritePin(SENSPOWER_GPIOPORT, SENSPOWER_GPIOBIT, GPIO_PIN_RESET);
}

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
	allocate_hw(HW_I2C1,0);
	sensors_power_on();
	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);

	LIS2DW12_Init();

	while(1)
	{
		wait_event(EVENT_TIMER );
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			LIS2DW12_GetAccData(0,axis_regs);
		}
	}
}

#endif //#ifdef STM32L431xx

