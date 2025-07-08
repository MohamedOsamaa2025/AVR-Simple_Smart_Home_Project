/*
 * main.c
 *
 *  Created on: Jul 19, 2022
 *      Author: hazemahmed
 */

#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include"SPI_Interface.h"
#include"Timer_Interface.h"
#include<util/delay.h>

int main(){
	/* DC Motor */
		SET_Direction(PORT_B, PIN_0, OUTPUT);
		SET_Direction(PORT_B, PIN_1, OUTPUT);
		SET_Value(PORT_B, PIN_0, HIGH);
		SET_Value(PORT_B, PIN_1, LOW);
		SET_Direction(PORT_B, PIN_3, OUTPUT);
		/*SPI*/
	SET_Direction(PORT_B, PIN_5, INPUT);
	SET_Direction(PORT_B, PIN_6, OUTPUT);
	SET_Direction(PORT_B, PIN_4, INPUT);
	SET_Direction(PORT_B, PIN_7, INPUT);
	SPI_Init_Slave();
	Timer_Init();
	u8 data;
	while(1){
		data=SPI_SendData('0');
		if(data=='H'){
			Timer_Set_CTC(255);
		}
		else if(data=='M'){
			Timer_Set_CTC(125);
		}
		else if(data=='L'){
			Timer_Set_CTC(0);
		}
	}

	return 0;
}
