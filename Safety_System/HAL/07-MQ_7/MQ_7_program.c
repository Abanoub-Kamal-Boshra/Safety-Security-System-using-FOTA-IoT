/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** MQ_4_program.c							****************/
/*** Date    : 14/7/2020                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#include"A_STD_TYPES.h"
#include"A_BIT_MATH.h"

#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "MQ_7_interface.h"
#include "MQ_7_private.h"
#include "MQ_7_config.h"

u32 HMQ_7_u32ReadAnalogVolt_mv(u8 Copy_u8Channel )
{
	u8 Copy_u8Sample_Time  = 7;

	//u32 Local_u32Result = 0; //(V_RL) >> Vout(Analog)
	u32 Local_u32Analog_mv = 0 ;
	if (Copy_u8Channel <= 9) // As we have only 10 channels for ADC1 peripheral in stm32 
		
		{
			GPIO_voidSetPinDirection(GPIOA ,Copy_u8Channel,INPUT_ANALOG); //configurations of the pin
			ADC_voidInit(Copy_u8Channel , Copy_u8Sample_Time ); // Initialization of ADC1 Peripheral

		//	Local_u32Result = ADC_u32StartConversion(Copy_u8Channel); //Digital (Out of ADC)
				/* As Analog(mv) = Digital * V_ref_mv / 4096 */
		Local_u32Analog_mv = ((u16)ADC_u16StartConversion(Copy_u8Channel) * V_REF_mv) / 4096UL ; //3600 in case of Vref = 3600
		}
	else 
	{
		//printf("You choosed wrong channel");
	}
	
	

	return Local_u32Analog_mv ;
}

f32 HMQ_7_f32_ReadData_ppm(u8 Copy_u8Channel)
{
	u8 Copy_u8Sample_Time  = 7;
	u32 Local_u32Analog_mv = 0 ;
	f32 Local_f32SensorResistance_ohm = 0; //>> Rs

	if (Copy_u8Channel <= 9) // As we have only 10 channels for ADC1 peripheral in stm32

		{
			GPIO_voidSetPinDirection(GPIOA ,Copy_u8Channel,INPUT_ANALOG); //configurations of the pin
			ADC_voidInit(Copy_u8Channel , Copy_u8Sample_Time );
		    // As Analog(mv) = Digital * V_ref_mv / 4096
			Local_u32Analog_mv = ((u16)ADC_u32StartConversion(Copy_u8Channel) * V_REF_mv) / 4096UL ; //3600 in case of Vref = 3600

			if((ADC_u32StartConversion(Copy_u8Channel)) != 0) //to make sure that the out of ADC is not zero
		{
			// As RS = RL (Vcc/V_RL - 1)
			Local_f32SensorResistance_ohm =((V_CC_mv / (f32)Local_u32Analog_mv) - 1)* RL_ohm ;
		}

		else
		{
			/* Error ! Division by zero*/
		}

		}
	else
		{
			//printf("You choosed wrong channel");
		}


		return Local_f32SensorResistance_ohm ;
}
