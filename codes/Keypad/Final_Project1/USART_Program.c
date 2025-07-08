/*
 * USART_Program.c
 *
 *  Created on: Jul 18, 2022
 *      Author: hazemahmed
 */

#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"USART_Interface.h"

void USART_init(){
	u8 temp=0;
	CLR_BIT(temp,6);
	CLR_BIT(temp,5);
	CLR_BIT(temp,4);
	CLR_BIT(temp,3);
	SET_BIT(temp,1);
	SET_BIT(temp,2);
	SET_BIT(temp,7);
	UCSRC=temp;
	UBRRL=51;
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
	CLR_BIT(UCSRB,2);

}
void USART_Send(u8 data){
	while(!GET_BIT(UCSRA,5));
	UDR=data;
}
u8 USART_Receive(){
	while(!GET_BIT(UCSRA,7));
	return UDR;
}
