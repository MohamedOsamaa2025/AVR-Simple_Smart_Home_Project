/*
 * LCD_Program.c
 *
 *  Created on: Jul 5, 2022
 *      Author: hazemahmed
 */
#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include"LCD_Interface.h"
#include<util/delay.h>
void LCD_Init(){
	LCD_SendCommands(Function_SET>>4);
	LCD_SendCommands(Function_SET>>4);
	LCD_SendCommands(Function_SET);
	LCD_SendCommands(DIsplay_ON_OFF>>4);
	LCD_SendCommands(DIsplay_ON_OFF);
	LCD_SendCommands(Display_Clear>>4);
	LCD_SendCommands(Display_Clear);
	_delay_ms(2);
	LCD_SendCommands(Entry_Mode>>4);
	LCD_SendCommands(Entry_Mode);
}
void LCD_SendCommands(u8 Command){
	//RS pin connected to port C pin 0
	SET_Value(PORT_C, PIN_0, LOW);
	//RW pin connected to port C pin 1
	SET_Value(PORT_C,PIN_1,LOW);
	// Data pins are connected to the 4 MSB in port C
	SET_Value_4MSB(PORT_C, Command);
	SET_Value(PORT_C, PIN_2, HIGH);
	_delay_ms(5);
	SET_Value(PORT_C, PIN_2, LOW);
	_delay_ms(1);
}
void LCD_SendData(u8 Data){
	//RS pin connected to port C pin 0
		SET_Value(PORT_C, PIN_0, HIGH);
		//RW pin connected to port C pin 1
		SET_Value(PORT_C,PIN_1,LOW);
		// Data pins are connected to the 4 MSB in port C
		SET_Value_4MSB(PORT_C, Data);
		SET_Value(PORT_C, PIN_2, HIGH);
		_delay_ms(5);
		SET_Value(PORT_C, PIN_2, LOW);
		_delay_ms(1);
}
void LCD_SendData_4BitMode(u8 Data){
	LCD_SendData(Data>>4);
	LCD_SendData(Data);
}
void LCD_SendNumbers(u16 Number){
	u8 arr[5];
	u8 i=0;
	if(Number==0){
		LCD_SendData_4BitMode('0');
	}
	else{
	while(Number!=0){
		arr[i]=Number%10;
		Number/=10;
		i++;
	}
	}
	for(s8 j=i-1;j>=0;j--){
		LCD_SendData_4BitMode(arr[j]+48);
	}
}
void LCD_String(u8 * String){
	for(u8 i=0;*(String+i)!='\0';i++){
		LCD_SendData_4BitMode(*(String+i));
	}
}
