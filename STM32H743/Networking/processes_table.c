/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */


#include "main.h"
#include "../../A_os/kernel/A.h"

extern	void process1_ism_pong(uint32_t process_id);	//This is process1
extern	void process_2(uint32_t process_id);	//This is process2
extern	void process_3(uint32_t process_id);	//This is process3
extern	void process_4(uint32_t process_id);	//This is process4 of the application

USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = process1_ism_pong,
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
