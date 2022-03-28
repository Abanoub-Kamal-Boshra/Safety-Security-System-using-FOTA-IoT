/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** DC-MOTOR - Program           		    ****************/
/*** Date    : 6/4/2021                     ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#include "A_STD_TYPES.h"
#include "A_BIT_MATH.h"


#include "DC_MOTOR_interface.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "DC_MOTOR_config.h"


//(1)
void HDC_MOTOR_voidMoveMotor(u8 Copy_u8Direction ,u8 Copy_u8Port, u8 PIN_A , u8 PIN_B)
{
	if ( (PIN_A <= PIN0) &&  (PIN_A <= PIN15) )
	{
		if ((PIN_B <=PIN0) &&  (PIN_B <= PIN15))
		{
			GPIO_voidSetPinDirection( Copy_u8Port, PIN_A , OUTPUT_SPEED_2MHZ_PP);
			GPIO_voidSetPinDirection( Copy_u8Port, PIN_B , OUTPUT_SPEED_2MHZ_PP);
			
			if (Copy_u8Direction == ClockWise_DC_MOTOR )
			{
				GPIO_voidSetPinValue(Copy_u8Port , PIN_B , GPIO_LOW);
				GPIO_voidSetPinValue(Copy_u8Port , PIN_A , GPIO_HIGH);
				//GPIO_voidSetBit  ( Copy_u8Port ,PIN_A ) ;
				
		        //GPIO_voidResetBit( Copy_u8Port ,PIN_B );
			}
			else if (Copy_u8Direction == CounterClockWise_DC_MOTOR)
			{
				GPIO_voidSetPinValue(Copy_u8Port , PIN_A , GPIO_LOW);
				GPIO_voidSetPinValue(Copy_u8Port , PIN_B , GPIO_HIGH);
				//GPIO_voidSetBit  ( Copy_u8Port ,PIN_B ) ;
		        //GPIO_voidResetBit( Copy_u8Port ,PIN_A );
			}
			else if (Copy_u8Direction == STOP_DC_MOTOR)
			{
				GPIO_voidSetPinValue(Copy_u8Port , PIN_A , GPIO_LOW);
				GPIO_voidSetPinValue(Copy_u8Port , PIN_B , GPIO_LOW);
				/*Error "Wrong Direction"*/
			}
			else
			{
				/* Wrong Direction */
			}		
		}
	}
}

//(2)
void HDC_MOTOR_voidStopMotor(u8 Copy_u8Port,u8 PIN_A , u8 PIN_B)
{
	
		GPIO_voidResetBit( Copy_u8Port ,PIN_A ) ;
		GPIO_voidResetBit( Copy_u8Port ,PIN_B );
}
