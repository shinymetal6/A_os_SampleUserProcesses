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
#include "ff.h"
#include <string.h>
#include <stdio.h>

uint8_t	theflag = 0;
uint8_t	sd_data[128];
extern	char 	SDPath[4];   /* SD logical drive path */
extern	FATFS 	SDFatFS;    /* File system object for SD logical drive */
extern	FIL 	SDFile;       /* File object for SD */

uint8_t FS_FileOperations(void)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  uint8_t wtext[] = "This is MY STM32 working with FatFs"; /* File write buffer */
  uint8_t rtext[100];                                   /* File read buffer */


  /* Register the file system object to the FatFs module */
  if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
  {
    /* Create and Open a new text file object with write access */
    if(f_open(&SDFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    {
      /* Write data to the text file */
      res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);

      if((byteswritten > 0) && (res == FR_OK))
      {
        /* Close the open text file */
        f_close(&SDFile);

        /* Open the text file object with read access */
        if(f_open(&SDFile, "STM32.TXT", FA_READ) == FR_OK)
        {
          /* Read data from the text file */
          res = f_read(&SDFile, rtext, sizeof(rtext), (void *)&bytesread);

          if((bytesread > 0) && (res == FR_OK))
          {
            /* Close the open text file */
            f_close(&SDFile);

            /* Compare read data with the expected data */
            if((bytesread == byteswritten))
            {
              /* Success of the demo: no error occurrence */
              return 0;
            }
          }
        }
      }
    }
  }
  /* Error */
  return 1;
}

void process_2_fat(uint32_t process_id)
{
uint32_t	wakeup;

	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	//FS_FileOperations();
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( FS_FileOperations() == 0 )
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);

		}
	}
}


