/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

extern	void process_1_flash(uint32_t process_id);		//This is process1
extern	void process_2_fat(uint32_t process_id);		//This is process2
extern	void process_3_SPItest(uint32_t process_id);		//This is process3
extern	void process_4(uint32_t process_id);			//This is process4

USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = process_1_flash,
				.stack_size = 1024,
		},
		{
				.user_process = process_2_fat,
				.stack_size = 1024,
		},
		{
				.user_process = process_3_SPItest,
				.stack_size = 1024,
		},
		{
				.user_process = process_4,
				.stack_size = 1024,
		}
};
