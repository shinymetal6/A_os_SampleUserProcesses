/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32U575xx

extern	void process_1(uint32_t process_id);		//This is process1
extern	void process_2(uint32_t process_id);		//This is process2
extern	void process_3(uint32_t process_id);		//This is process3
extern	void process_4(uint32_t process_id);			//This is process4


VERSIONING	uint8_t	app_name[32] 		= "H563 sample processes";
VERSIONING	uint8_t	app_version[32] 	= "1.0.0 rc 1";

USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = process_1,
				.stack_size = 1024,
		},
		{
				.user_process = process_2,
				.stack_size = 1024,
		},
		{
				.user_process = process_3,
				.stack_size = 1024,
		},
		{
				.user_process = process_4,
				.stack_size = 1024,
		}
};

#endif // #ifdef	STM32H563xx
