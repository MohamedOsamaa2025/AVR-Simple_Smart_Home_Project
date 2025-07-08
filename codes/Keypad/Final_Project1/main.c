/*
 * main.c
 *
 *  Created on: Jul 19, 2022
 *      Author: hazemahmed
 */


#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include"Keypad_Interface.h"
#include"USART_Interface.h"
#include<util/delay.h>

int main(){
	SET_Direction_4LSB(PORT_A, OUTPUT);
	SET_Direction_4LSB(PORT_B, INPUT);
	SET_Value_4LSB(PORT_B, 0b00001111);
	SET_Value_4LSB(PORT_A, 0x0F);
	SET_Direction(PORT_D, PIN_0, INPUT);
	SET_Direction(PORT_D, PIN_1, OUTPUT);
	USART_init();

	u8 key='u';
	while(1){
		key=Keypad_GetKey();
		if(key!='u'){
			USART_Send(key);
		}
		else{

		}

	}

	return 0;

}
