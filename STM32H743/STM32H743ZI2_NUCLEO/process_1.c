/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32H743ZI2_NUCLEO

uint8_t	state;
uint8_t	replyBuf[256];

void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
	allocate_hw(HW_TIM,0);
	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	dcc_init(0,0,0,0);
	dcc_start_timer_channel(0);
	dcc_enable_output(0);
	state = 0;
	//A_hw_timers_start_pwm(0,TIM_CHANNEL_1);
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_UART3_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
				switch (state )
				{
				case 0 :
					one_byte_commands('A',replyBuf);
					state++;
					break;
				case 1 :
					//one_byte_commands('R',replyBuf);
					state++;
					break;
				case 2 :
					two_bytes_commands('T',1,0x55,0xaa,replyBuf);
					state++;
					break;
				case 3 :
					three_bytes_commands('T',1,0x7e,0xe7,0xcc,replyBuf);
					state++;
					break;
				case 4 :
					one_byte_commands('R',replyBuf);
					state++;
					break;
				case 5 :
					one_byte_commands('x',replyBuf);
					state++;
					break;
				case 6 :
					state = 0;
					break;

				}
		}
	}
}

#endif // #ifdef	STM32H743xx
