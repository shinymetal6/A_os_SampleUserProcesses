/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

uint8_t	theflag = 0;
uint8_t	sd_data[128];
extern	char 	SDPath[4];   /* SD logical drive path */
extern	FATFS 	SDFatFS;    /* File system object for SD logical drive */
extern	FIL 	SDFile;       /* File object for SD */

uint8_t wtext[] = "Fyberloom STM32 FatFs running";
uint8_t rtext[256];

void process_2_fat(uint32_t process_id)
{
uint32_t	wakeup;
uint32_t	bytesread,byteswritten;
uint8_t		res;

	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			res = 1;
			if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
			{
		        if(f_open(&SDFile, "STM32.TXT", FA_READ) == FR_OK)
		        {
		        	res = f_read(&SDFile, rtext, sizeof(rtext), (void *)&bytesread);
		            f_close(&SDFile);
		        }
		        else
		        {
		        	res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);
		            f_close(&SDFile);
		        }
			}
	        if ( res == 0 )
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
		}
	}
}


