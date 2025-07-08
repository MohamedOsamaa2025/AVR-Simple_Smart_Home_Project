/*
 * main.c
 *
 *  Created on: Jul 19, 2022
 *      Author: hazemahmed
 */
#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"ADC_Interface.h"
#include"DIO_Interface.h"
#include"EXTI_Interface.h"
#include"GIE_Interface.h"
#include"USART_Interface.h"
#include"LCD_Interface.h"
#include"SPI_Interface.h"
#include<util/delay.h>

u16 temp;
u16 temp_prev=0;
u16 digital;
u8 flag=0;
u8 flag1=0;
u8 code[4]={'1','2','3','4'};
void System_ON();
int main(){
	u8 key[4];
	u8 i=0;
	/*LCD Pins*/
	SET_Direction(PORT_C, PIN_0, OUTPUT);
	SET_Direction(PORT_C, PIN_1, OUTPUT);
	SET_Direction(PORT_C, PIN_2, OUTPUT);
	SET_Direction_4MSB(PORT_C, OUTPUT);

	/*Temp sensor*/
	SET_Direction(PORT_A, PIN_0, INPUT);

	/* Emergency PB*/
	SET_Direction(PORT_D, PIN_2, INPUT);
	SET_Value(PORT_D, PIN_2, HIGH);

	/*Lock PB*/
	SET_Direction(PORT_D, PIN_3, INPUT);
	SET_Value(PORT_D, PIN_3, HIGH);

	/*Emergency LED*/
	SET_Direction(PORT_B, PIN_2, OUTPUT);

	/*UART*/
	SET_Direction(PORT_D, PIN_0, INPUT);
	SET_Direction(PORT_D, PIN_1, OUTPUT);
	/* SPI*/
	SET_Direction(PORT_B, PIN_5, OUTPUT);
	SET_Direction(PORT_B, PIN_6, INPUT);
	SET_Direction(PORT_B, PIN_4, OUTPUT);
	SET_Direction(PORT_B, PIN_7, OUTPUT);
	SET_Value(PORT_B, PIN_4, LOW);

	LCD_Init();
	ADC_Init();
	USART_init();
	SPI_Init_Master();
	EXTI_Enable(0);
	Interrupt_Enable();
	LCD_String("System is Locked");
	_delay_ms(1500);
	while(1){
		if(flag1==2){
			LCD_SendCommands(0b00000001<<4);
			LCD_SendCommands(0b00000001);
			LCD_String("System is Locked");
			flag1=0;
		}
		if(USART_Receive()=='O'&&flag==0){
			LCD_SendCommands(0b00000001<<4);
			LCD_SendCommands(0b00000001);
			LCD_String("Code:");
			_delay_ms(250);
			flag=1;
		}
		else{

		}
		while(flag){
			key[i]=USART_Receive();
			if(i==0){
				LCD_SendData_4BitMode(key[i]);
				i++;
			}
			else{
				if(key[i-1]!=key[i]){
					LCD_SendData_4BitMode(key[i]);
					i++;
				}
			}
			if(i==4){
				if(key[0]==code[0]&&key[1]==code[1]&&key[2]==code[2]&&key[3]==code[3]){
					EXTI_Enable(1);
					LCD_SendCommands(0b00000001<<4);
					LCD_SendCommands(0b00000001);
					LCD_String("Welcome");
					_delay_ms(1500);
					ADC_Start(0);
					digital=ADC_Result();
					temp=Analog_Value(digital);
					LCD_SendCommands(0b00000001<<4);
					LCD_SendCommands(0b00000001);
					LCD_String("Current Temp:");
					LCD_SendNumbers(temp/10);
					temp_prev=temp;
					_delay_ms(1500);
					System_ON();
				}
				else{
					LCD_SendCommands(0b00000001<<4);
					LCD_SendCommands(0b00000001);
					LCD_String("Wrong code");
					_delay_ms(1500);
					LCD_SendCommands(0b00000001<<4);
					LCD_SendCommands(0b00000001);
					LCD_String("System is Locked");

				}
				flag=0;
				i=0;
			}
		}
	}
	return 0;
}
void System_ON(){
	while(1){
		if(flag1==0){
			if(temp>30){
				SPI_SendData('H');
			}
			else if(temp<30&&temp>20){
				SPI_SendData('M');
			}
			else if(temp<20){
				SPI_SendData('L');
			}
			if(temp!=temp_prev){
				LCD_SendCommands(0b00000001<<4);
				LCD_SendCommands(0b00000001);
				LCD_String("Current Temp:");
				LCD_SendNumbers(temp);
				temp_prev=temp;
			}
			ADC_Start(0);
			digital=ADC_Result();
			temp=Analog_Value(digital)/10;

		}
		else if(flag1==1){
			LCD_SendCommands(0b00000001<<4);
			LCD_SendCommands(0b00000001);
			LCD_String("System is Locked");
			SPI_SendData('L');
			flag1=0;
			return;
		}
		else if(flag1==2){
			LCD_SendCommands(0b00000001<<4);
			LCD_SendCommands(0b00000001);
			LCD_String("Current Temp:");
			LCD_SendNumbers(temp);
			flag1=0;
		}

	}

}

void __vector_1(void)  __attribute__((signal));
void __vector_2(void)  __attribute__((signal));
void __vector_1(void){
	u8 i=0;
	u8 key[4];
	SET_Value(PORT_B, PIN_2, HIGH);
	LCD_SendCommands(0b00000001<<4);
	LCD_SendCommands(0b00000001);
	LCD_String("Enter code: ");
	while(1){
		key[i]=USART_Receive();
		if(i==0){
			LCD_SendData_4BitMode(key[i]);
			i++;
		}
		else{
			if(key[i-1]!=key[i]){
				LCD_SendData_4BitMode(key[i]);
				i++;
			}
		}
		if(i==4){
			if(key[0]==code[0]&&key[1]==code[1]&&key[2]==code[2]&&key[3]==code[3]){
				SET_Value(PORT_B, PIN_2, LOW);
				flag1=2;
				return;
			}
			else{
				LCD_SendCommands(0b00000001<<4);
				LCD_SendCommands(0b00000001);
				LCD_String("Wrong code");
				_delay_ms(2000);
				LCD_SendCommands(0b00000001<<4);
				LCD_SendCommands(0b00000001);
				LCD_String("Enter code: ");
				i=0;
			}
		}
	}
}

void __vector_2(void){
	u8 i=0;
	u8 key[4];
	LCD_SendCommands(0b00000001<<4);
	LCD_SendCommands(0b00000001);
	LCD_String("Enter code: ");
	while(1){
		key[i]=USART_Receive();
		if(i==0){
			LCD_SendData_4BitMode(key[i]);
			i++;
		}
		else{
			if(key[i-1]!=key[i]){
				LCD_SendData_4BitMode(key[i]);
				i++;
			}
		}
		if(i==4){
			if(key[0]==code[0]&&key[1]==code[1]&&key[2]==code[2]&&key[3]==code[3]){
				flag1=1;
				return;
			}
			else{
				LCD_SendCommands(0b00000001<<4);
				LCD_SendCommands(0b00000001);
				LCD_String("Wrong code");
				_delay_ms(2000);
				LCD_SendCommands(0b00000001<<4);
				LCD_SendCommands(0b00000001);
				LCD_String("Enter code: ");
				i=0;
			}
		}
	}
}

