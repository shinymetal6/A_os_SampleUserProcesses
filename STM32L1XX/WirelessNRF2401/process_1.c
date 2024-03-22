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
 * Project : A_os
*/
/*
 * process_1.c
 *
 *  Created on: Mar 22, 2024
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef	STM32L152xE

uint8_t	counter = 0x30;

uint8_t tx_data[32] = {0x30,' ','-', '0', '1', '2', '3', '4', '5', '6', '7','\n','\r'};
uint8_t rx_data[32];
uint8_t	nrf_address[5] = {0xb3,0xb4,0xb5,0xb6,0x05};

uint8_t		nrf24l01_irq,nrf24l01_txds=0,nrf24l01_txdr=0,nrf24l01_maxrt=0;
uint8_t		irqfromnrf = 0;

void A_os_nrf24l01_callback(void)
{
	irqfromnrf++;
}
void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;

	allocate_hw_with_irq_callback(HW_SPI2,HWDEV_NRF24L01,HWDEV_STATUS_PRC_WAKEUP,A_os_nrf24l01_callback);
	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	nrf24l01_init(2500, NRF24L01_2Mbps, NRF24L01_MODE_TX,nrf_address);
	while(1)
	{
		wait_event(EVENT_TIMER  | EVENT_NRF24L01_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			nrf24l01_tx(tx_data , nrf_address);	// tx buffer
		}
		if (( wakeup & WAKEUP_FROM_SPI2_IRQ) == WAKEUP_FROM_SPI2_IRQ)
		{
			if (( flags & HWDEV_NRF24L01) == HWDEV_NRF24L01)
			{
				HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
				nrf24l01_irq = nrf24l01_get_status();
				if ( nrf24l01_irq & NRF24L01_IRQ_IS_TX_DS )
				{
					HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
					nrf24l01_get_tx_irq_goto_rx();
					nrf24l01_txds++;
					task_delay(5);
				}
				if ( nrf24l01_irq & NRF24L01_IRQ_IS_TX_DR )
				{
					nrf24l01_rx(rx_data);
					nrf24l01_txdr++;
					task_delay(150);
				}
				if ( nrf24l01_irq & NRF24L01_IRQ_IS_MAX_RT )
				{
					nrf24l01_maxrt++;
				}
			}
		}
	}
}


#endif // #ifdef	STM32L152xE

