/*
 * USART_Interface.h
 *
 *  Created on: Jul 18, 2022
 *      Author: hazemahmed
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#define UCSRA *((volatile u8*)0x2B)
#define UCSRB *((volatile u8*)0x2A)
#define UCSRC *((volatile u8*)0x40)
#define UBRRL *((volatile u8*)0x29)
#define UDR *((volatile u8*)0x2C)

void USART_init();
void USART_Send(u8 data);
u8 USART_Receive();
#endif /* USART_INTERFACE_H_ */
