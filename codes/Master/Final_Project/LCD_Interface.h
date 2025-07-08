/*
 * LCD_Interface.h
 *
 *  Created on: Jul 5, 2022
 *      Author: hazemahmed
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define Function_SET 0b00101000
#define DIsplay_ON_OFF 0b00001111
#define Display_Clear 0b00000001
#define Entry_Mode 0b00000110
void LCD_Init();
void LCD_SendCommands(u8 Command);
void LCD_SendData(u8 Data);
void LCD_SendData_4BitMode(u8 Data);
void LCD_SendNumbers(u16 Number);
void LCD_String(u8 * String);

#endif /* LCD_INTERFACE_H_ */
