/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : fy-201023-00 
*/
/*
 * process1_ism_pong.c
 *
 *  Created on: Dec 28, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../A_os/kernel/A.h"
#include "../../A_os/kernel/A_exported_functions.h"
#include "../../A_os/kernel/system_default.h"

#include <string.h>
#include <stdio.h>

uint8_t	counter = 0x30;

uint8_t	nrf_address[5] = {0xb3,0xb4,0xb5,0xb6,0x05};
uint8_t tx_data[48] = {0x30,' ','R', '0', '1', '2', '3', '4', '5', '6', '7','\n','\r'};

uint8_t rx_data[48];
uint8_t		nrf24l01_irq,nrf24l01_txdr=0,nrf24l01_txds=0,nrf24l01_txdt=0,nrf24l01_maxrt=0;
void process1_ism_pong(uint32_t process_id)
{
uint32_t	wakeup;
	create_timer(TIMER_ID_0,50,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	nrf24l01_init(2500, NRF24L01_2Mbps, NRF24L01_MODE_RX,nrf_address);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER | EVENT_NRF24L01_IRQ);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{

		}
		if (( wakeup & WAKEUP_FROM_NRF24L01_IRQ) == WAKEUP_FROM_NRF24L01_IRQ)
		{
			nrf24l01_irq = nrf24l01_get_status();
			if ( nrf24l01_irq & NRF24L01_IRQ_IS_TX_DS )
			{
				nrf24l01_get_tx_irq_goto_rx();
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
			}
			if ( nrf24l01_irq & NRF24L01_IRQ_IS_TX_DR )
			{
				nrf24l01_irq = nrf24l01_rx(rx_data);
				nrf24l01_txdr++;
				nrf24l01_tx(tx_data , nrf_address);
			}
		}
	}
}


