/*
 * process_1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32U575xx

#define	DCC1_CHANNEL		TIM_CHANNEL_1
#define	CUTOUT1_CHANNEL		TIM_CHANNEL_2
#define	DCC2_CHANNEL		TIM_CHANNEL_1
#define	CUTOUT2_CHANNEL		TIM_CHANNEL_3

extern	DMA_HandleTypeDef handle_GPDMA1_Channel0;
extern	DMA_HandleTypeDef handle_GPDMA1_Channel1;
extern	DMA_HandleTypeDef handle_GPDMA1_Channel2;
extern	DMA_HandleTypeDef handle_GPDMA1_Channel3;

uint8_t	state = 0;
uint8_t	dcc_reply[64];

#define	TX_NUM	1
void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	track1 = DCC_TRACK_1;
uint32_t	track2 = DCC_TRACK_2;

	allocate_hw(HW_TIM,0);
	dcc_init(HW_TIMERS_TIMER1,DCC_TRACK_1,DCC1_CHANNEL,TX_NUM,CUTOUT1_CHANNEL,&handle_GPDMA1_Channel1,&handle_GPDMA1_Channel0);
	dcc_init(HW_TIMERS_TIMER8,DCC_TRACK_2,DCC2_CHANNEL,TX_NUM,CUTOUT2_CHANNEL,&handle_GPDMA1_Channel3,&handle_GPDMA1_Channel2);
	dcc_start(DCC_TRACK_1);
	dcc_start(DCC_TRACK_2);

	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER );
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
			switch(state)
			{
			case	0	:
				state++;
				break;
			case	1	:
				one_byte_commands('A',dcc_reply);
				one_byte_commands('B',dcc_reply);
				state++;
				break;
			case	2	:
				one_byte_commands('R',dcc_reply);
				one_byte_commands('r',dcc_reply);
				state++;
				break;
			case	3	:
				two_bytes_commands('T',track1,0x55,0xaa,dcc_reply);
				state++;
				break;
			case	4	:
				three_bytes_commands('T',track1,0x55,0xcc,0x33,dcc_reply);
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
				state++;
				break;
			case	5	:
				three_bytes_commands('T',track2,0xcc,0x55,0x77,dcc_reply);
				HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
				state++;
				break;
			case	6	:
				one_byte_commands('S',dcc_reply);
				one_byte_commands('s',dcc_reply);
				state++;
				break;
			case	7	:
				one_byte_commands('x',dcc_reply);
				state = 1;
				break;
			}
		}
	}
}

#endif //#ifdef	STM32H563xx
