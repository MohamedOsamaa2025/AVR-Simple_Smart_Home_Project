/*
 * Keypad_Program.c
 *
 *  Created on: Jul 5, 2022
 *      Author: hazemahmed
 */

#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include<util/delay.h>
u8 Keypad_GetKey(){
	u8 key='u';
	u8 arr[4][4]={{'7','8','9','D'},{'4','5','6','x'},{'1','2','3','-'},{'O','0','=','+'}};
	for(u8 i=0;i<4;i++){
		SET_Value(PORT_A, i, LOW);
		for(u8 j=0;j<4;j++){
			if(GET_Value(PORT_B, j)==LOW){
				while(GET_Value(PORT_B, j)==LOW){
					_delay_ms(25);
				}
				key=arr[j][i];
				return key;
			}
		}
		SET_Value(PORT_A, i, HIGH);
	}
	return key;
}
