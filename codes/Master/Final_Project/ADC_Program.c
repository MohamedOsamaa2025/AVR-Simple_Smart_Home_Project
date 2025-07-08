/*
 * ADC_Program.c
 *
 *  Created on: Jul 6, 2022
 *      Author: hazemahmed
 */

#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"ADC_Interface.h"
void ADC_Init(){
	// Reference voltage is AVCC
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	// Right adjustment
	CLR_BIT(ADMUX,5);
	// Prescaler of 128
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	//ADC Enable
	SET_BIT(ADCSRA,7);
}
void ADC_Start(u8 Channel){
	ADMUX&=0b11100000;
	ADMUX|=Channel;
	SET_BIT(ADCSRA,6);
	while(!GET_BIT(ADCSRA,4));
}
u16 ADC_Result(){
	return ADC_Data;
}
u16 Analog_Value(u16 Digital_Value){
	u16 Analog;
	Analog=Digital_Value*(5000UL)/1024;
	return Analog;
}
