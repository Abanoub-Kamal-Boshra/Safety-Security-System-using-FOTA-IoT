/*******************************************************************/
/*******************************************************************/
/***************************     Author: Magdy     *************/
/***************************     Layer:HALL            *************/
/***************************     SWC:KPD               *************/
/***************************     Version:1.00          *************/
/***************************     Data:1-9-2020        *************/
/*******************************************************************/
/*******************************************************************/

#include "STD_TYPES.h"
#include "GPIO_interface.h"
//#include "CLCD_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"
//#include <util/delay.h>




u8 KPD_U8GetPressedKey(void)
{
	// this is the iterator of the COLUMNS
	u8 Local_u8ColIdx;

	// this is the iterator of the ROWS
	u8 Local_u8RowIdx;

	//this variable is to show if there is no pressed key
	u8 Local_u8PressedKey=NO_PRESSED_KEY;

	u8 Local_u8PinState;


	// this [array] takes the number of columns and  the number of rows
	//and all the values of both the columns and the rows are given by
	//the user in the process of configuration
	u8 Local_KPDArr[ROW_NUMBER][COLLUM_NUMBER]=KPD_BUTTONS_VAL;

	u8 Local_u8ColArr[COLLUM_NUMBER]={COLLUM_PIN0,COLLUM_PIN1,COLLUM_PIN2,COLLUM_PIN3};

	u8 Local_u8RowArr[ROW_NUMBER]={ROW_PIN0,ROW_PIN1,ROW_PIN2,ROW_PIN3};



  // this first Outer "for loop" is used to activate the needed column
	for(Local_u8ColIdx=0;Local_u8ColIdx<COLLUM_NUMBER;Local_u8ColIdx++)
	{
		// 01_Step One :   activate the current column : //makes it OUTPUT_LOW//
		MGPIO_voidSetPinValue(KPD_PORT,Local_u8ColArr[Local_u8ColIdx],GPIO_PIN_LOW);

		// this second inner "for loop" is used to find which
		//Button of the for keys corresponding to this column is pressed
		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUMBER;Local_u8RowIdx++)
		{
			Local_u8PinState = MGPIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx]/*,&Local_u8PinState*/);
			if(Local_u8PinState==GPIO_PIN_LOW)
			{
				Local_u8PressedKey=Local_KPDArr[Local_u8RowIdx][Local_u8ColIdx];
				while(Local_u8PinState==GPIO_PIN_LOW)
				{
					Local_u8PinState = MGPIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx]/*,&Local_u8PinState*/);
				}
				return Local_u8PressedKey;
			}
		}
		MGPIO_voidSetPinValue(KPD_PORT,Local_u8ColArr[Local_u8ColIdx],GPIO_PIN_HIGH);
	}
	return Local_u8PressedKey;
}


