/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** FLAME_SENSOR_program.c					****************/
/*** Date    : 3/7/2021                     ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#include"A_STD_TYPES.h"
#include"A_BIT_MATH.h"

#include "FLAME_SENSOR_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"


u32 HFLAME_SENSOR_u32ReadAnalogVolt_mv(u8 Copy_u8Channel )
{
	u8 Copy_u8Sample_Time  = 7;

	//u32 Local_u32Result = 0; //(V_RL) >> Vout(Analog)
	u32 Local_u32Analog_mv = 0 ;
	if (Copy_u8Channel <= 9) // As we have only 10 channels for ADC1 peripheral in stm32 
		
		{
			GPIO_voidSetPinDirection(GPIOA ,Copy_u8Channel,INPUT_ANALOG); //configurations of the pin
			ADC_voidInit(Copy_u8Channel , Copy_u8Sample_Time );

		//	Local_u32Result = ADC_u32StartConversion(Copy_u8Channel); //Digital (Out of ADC)
		              
					  /*********    As Analog(mv) = Digital * V_ref_mv / 4096    *********/
			Local_u32Analog_mv = ((u16)ADC_u16StartConversion(Copy_u8Channel)* V_REF_mv) / 4096UL ; //3600 in case of Vref = 3600
		}
	else 
	{
		//printf("You choosed wrong channel");
	}
		
	

	return Local_u32Analog_mv ;
}