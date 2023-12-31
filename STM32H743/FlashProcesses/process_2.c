/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../../A_os/kernel/A.h"
#include "../../../A_os/kernel/A_exported_functions.h"
#include "../../../A_os/kernel/system_default.h"
#include "../../../A_Libraries/ExternalLibraries/STM32H7/FatFs/src/ff.h"
#include <string.h>
#include <stdio.h>

#define	PRC1_I2C				HW_I2C1
uint8_t	theflag = 0;
uint8_t	sd_data[128];

void process_2(uint32_t process_id)
{
uint32_t	wakeup;
FATFS 		SDFatFs;  /* File system object for SD card logical drive */
FIL 		MyFile;     /* File object */
char 		SDPath[4]; /* SD card logical drive path */
FRESULT res;                                          /* FatFs function common result code */
uint32_t byteswritten;

	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) == FR_OK)
	{
		if(f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		{
			sprintf((char *)sd_data,"Ciao Fil\n\r");
			res = f_write(&MyFile, sd_data, sizeof(sd_data), (void *)&byteswritten);
			if((byteswritten > 0) && (res == FR_OK))
				theflag=1;
		}
	}
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
		}
	}
}

