/*
 * ADC_Interface.h
 *
 *  Created on: Jul 6, 2022
 *      Author: hazemahmed
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADMUX *((volatile u8*)0x27)
#define ADCSRA *((volatile u8*)0x26)
#define ADCH *((volatile u8*)0x25)
#define ADCL *((volatile u8*)0x24)
#define ADC_Data  *((volatile u16*)0x24)
#define SFIOR *((volatile u8*)0x50)

void ADC_Init();
void ADC_Start(u8 Channel);
u16 ADC_Result();
u16 Analog_Value(u16 Analog_Value);

#endif /* ADC_INTERFACE_H_ */
