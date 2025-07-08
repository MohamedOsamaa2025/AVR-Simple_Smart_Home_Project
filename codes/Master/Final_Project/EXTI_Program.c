/*
 * EXTI_Program.c
 *
 *  Created on: Jul 5, 2022
 *      Author: hazemahmed
 */

#include"BIT_OP.h"
#include"STD_TYPES.h"
#include"GIE_Interface.h"
#include"EXTI_Interface.h"

void EXTI_Enable(u8 INT_NUM){
	switch(INT_NUM){
	case 0:
#if Sense_Control==LOW_Level
		CLR_BIT(MCUCR,0);
		CLR_BIT(MCUCR,1);
#elif Sense_Control==Any_Logical_Change
		SET_BIT(MCUCR,2);
		CLR_BIT(MCUCR,3);
#elif Sense_Control==FALLING_EDGE
		CLR_BIT(MCUCR,0);
		SET_BIT(MCUCR,1);
#elif Sense_Control==RISING_EDGE
		SET_BIT(MCUCR,0);
		SET_BIT(MCUCR,1);
#else
#error "Wrong Sense Control"
#endif
		SET_BIT(GICR,6);
		break;
	case 1:
	#if Sense_Control==LOW_Level
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
	#elif Sense_Control==Any_Logical_Change
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
	#elif Sense_Control==FALLING_EDGE
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
	#elif Sense_Control==RISING_EDGE
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
	#else
	#error "Wrong Sense Control"
	#endif
			SET_BIT(GICR,7);
			break;
	}
}
