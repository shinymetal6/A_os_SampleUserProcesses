/*
 * process_4.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32H743xx

uint8_t step = 0;
void step_leds(void)
{
	switch ( step)
	{
	case	0	:
		  HAL_GPIO_WritePin(J10_CH2_GPIO_Port, J10_CH2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J2_CH1_GPIO_Port, J2_CH1_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	1	:
		  HAL_GPIO_WritePin(J2_CH1_GPIO_Port, J2_CH1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J2_CH2_GPIO_Port, J2_CH2_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	2	:
		  HAL_GPIO_WritePin(J2_CH1_GPIO_Port, J2_CH2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J3_CH1_GPIO_Port, J3_CH1_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	3	:
		  HAL_GPIO_WritePin(J3_CH1_GPIO_Port, J3_CH1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J3_CH2_GPIO_Port, J3_CH2_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	4	:
		  HAL_GPIO_WritePin(J3_CH2_GPIO_Port, J3_CH2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J9_CH1_GPIO_Port, J9_CH1_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	5	:
		  HAL_GPIO_WritePin(J9_CH1_GPIO_Port, J9_CH1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J9_CH2_GPIO_Port, J9_CH2_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	6	:
		  HAL_GPIO_WritePin(J9_CH2_GPIO_Port, J9_CH2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J10_CH1_GPIO_Port, J10_CH1_Pin, GPIO_PIN_SET);
		  step++;
		  break;
	case	7	:
		  HAL_GPIO_WritePin(J10_CH1_GPIO_Port, J10_CH1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(J10_CH2_GPIO_Port, J10_CH2_Pin, GPIO_PIN_SET);
		  step=0;
		  break;

	}
}

void all_on(void)
{
	  HAL_GPIO_WritePin(J2_CH1_GPIO_Port,  J2_CH1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J2_CH2_GPIO_Port,  J2_CH2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J3_CH1_GPIO_Port,  J3_CH1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J3_CH2_GPIO_Port,  J3_CH2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J9_CH1_GPIO_Port,  J9_CH1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J9_CH2_GPIO_Port,  J9_CH2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J10_CH1_GPIO_Port, J10_CH1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(J10_CH2_GPIO_Port, J10_CH2_Pin, GPIO_PIN_SET);
}

void all_off(void)
{
	  HAL_GPIO_WritePin(J2_CH1_GPIO_Port,  J2_CH1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J2_CH2_GPIO_Port,  J2_CH2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J3_CH1_GPIO_Port,  J3_CH1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J3_CH2_GPIO_Port,  J3_CH2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J9_CH1_GPIO_Port,  J9_CH1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J9_CH2_GPIO_Port,  J9_CH2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J10_CH1_GPIO_Port, J10_CH1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(J10_CH2_GPIO_Port, J10_CH2_Pin, GPIO_PIN_RESET);
}

void process_4(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	cycle=0;
	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	while(1)
	{
		wait_event(EVENT_TIMER);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			wakeup=0;
			/*
			cycle++;
			cycle &= 1;
			if ( cycle )
				all_on();
			else
				all_off();
				*/
			step_leds();
		}
	}
}

#endif // #ifdef	STM32H743xx
