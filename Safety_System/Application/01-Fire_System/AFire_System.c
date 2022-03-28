/***********************************************       Documentation     *********************************************/
/*** Author  :  Solyma                      ****************/
/*** AFire_System.c							****************/
/*** Layer    : Application                 ****************/
/*** Date    : 30/6/2021                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/
/***********************************************************************************************************************/



/*******************************************  Librariers Which we will need *******************************************/
#include"A_STD_TYPES.h"
#include"A_BIT_MATH.h"
/* Filles Of MCAL */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "MSTK_interface.h"

/*Files OF HAL layers*/
#include "MQ_2_interface.h"         //MQ_2 Sensor for firing gases detection
#include "DC_MOTOR_interface.h"     //DC_Motor For turnning on/Off Windows
#include "FLAME_SENSOR_interface.h" //Flaame Sensor for flame's fire detection


/***********************************************************************************************************************/
/* Prototype of the fire function */
void APP_SET_FIRE_SYSTEM(u8 MQ_2ROOM, u8 FLAME_SENSOR_1ROOM ,u8 FLAME_SENSOR_2ROOM , u8 FIRE_MESSAGE_ROOM ,u8 LED_ROOM,u8 Relay_ROOM ,u8 BUZZER_ROOM ,u8 DC_MOTOR_PIN_A_ROOM ,u8 DC_MOTOR_PIN_B_ROOM )

void main(void)
{
/**********************************************     CLOCK INITIALIZATION     *******************************************/		

RCC_voidInitSysClock(void);//Clock of the processor
RCC_voidEnableClock(RCC_APB2 , IOPA); //Enable Clock for GPIOA Peripheral
RCC_voidEnableClock(RCC_APB2 , IOPB); //Enable Clock for GPIOA Peripheral
RCC_voidEnableClock(RCC_APB2 , IOPC); //Enable Clock for GPIOA Peripheral
RCC_voidEnableClock(RCC_APB2 , ADC1); //Enable Clock for ADC1 Peripheral



/***************************************************** PINS FOR ROOM '1' **************************************************************/
//Pins Connected at Port 'A' 
#define  MQ_2ROOM_1             ADC_CH1
#define  FLAME_SENSOR_1ROOM_1   ADC_CH2 
#define  FLAME_SENSOR_2ROOM_1   ADC_CH3 

//Pins Connected at Port 'B' 
#define  FIRE_MESSAGE_ROOM_1       PIN0                
#define  BUZZER_ROOM_1             PIN1
#define  DC_MOTOR_PIN_A_ROOM_1     PIN5
#define  DC_MOTOR_PIN_B_ROOM_1     PIN6
#define  LED_ROOM_1                PIN7
#define  Relay_ROOM_1              PIN8
              
	
/**********************************************       PINS Configuration     *******************************************/	

/**********************************************       ROOM '1'     *******************************************/
GPIO_voidSetPinDirection( GPIOB , FIRE_MESSAGE_ROOM_1 , OUTPUT_SPEED_2MHZ_PP);    // >>> MESSAGE_PIN_Room1	
GPIO_voidSetPinDirection( GPIOB , LED_ROOM_1    , OUTPUT_SPEED_2MHZ_PP);          // >>> Led_PIN_Room1
GPIO_voidSetPinDirection( GPIOB , BUZZER_ROOM_1 , OUTPUT_SPEED_2MHZ_PP);          // >>> Buzzer_PIN_Room1
GPIO_voidSetPinDirection( GPIOB , Relay_ROOM_1 , OUTPUT_SPEED_2MHZ_PP);           // >>> Buzzer_PIN_Room1
GPIO_voidSetPinDirection( GPIOB , DC_MOTOR_PIN_A_ROOM_1 , OUTPUT_SPEED_2MHZ_PP);  // >>> PIN_A For H_bridge of DC_Motor
GPIO_voidSetPinDirection( GPIOB , DC_MOTOR_PIN_B_ROOM_1 , OUTPUT_SPEED_2MHZ_PP);  // >>> PIN_B For H_bridge of DC_Motor
	
/***********************************************************************************************************************/


while(1)
	{
		/* Calling the Function */
		APP_SET_FIRE_SYSTEM(MQ_2ROOM_1, FLAME_SENSOR_1ROOM_1 ,FLAME_SENSOR_2ROOM_1 , FIRE_MESSAGE_ROOM_1, LED_ROOM_1, Relay_ROOM_1 , BUZZER_ROOM_1 , DC_MOTOR_PIN_A_ROOM_1 , DC_MOTOR_PIN_B_ROOM_1 );
	
	}
APP_SET_FIRE_SYSTEM(u8 MQ_2ROOM, u8 FLAME_SENSOR_1ROOM ,u8 FLAME_SENSOR_2ROOM , u8 FIRE_MESSAGE_ROOM ,u8 LED_ROOM,u8 Relay_ROOM ,u8 BUZZER_ROOM ,u8 DC_MOTOR_PIN_A_ROOM ,u8 DC_MOTOR_PIN_B_ROOM )
{
	
	/* Connect MQ_2 sensor at an analog pin  */
	u32 MQ_2Value = HMQ_2_u32ReadAnalogVolt_mv( MQ_2ROOM ); // Pass the channel(A1) which is connected with MQ2 Sensor
	
	/* Connect Flame_Sensors at another analog pins  */
	u32 Flame_Sensor_1Value = HFLAME_SENSOR_u32ReadAnalogVolt_mv( FLAME_SENSOR_1ROOM );
	u32 Flame_Sensor_2Value = HFLAME_SENSOR_u32ReadAnalogVolt_mv( FLAME_SENSOR_2ROOM );


	if (MQ_2Value > MQ2_ON_Fire_Value_mv) // checking for most Dangerous sitiuation !!
	{
		if ( (Flame_Sensor_1Value >= FLAME_SENSOR_FIRE_mV) ||((Flame_Sensor_2Value >= FLAME_SENSOR_FIRE_mV))) //If "True" there is fire surely
		{
			/* 1- Send A message to the owner */
				GPIO_voidSetPinValue( GPIOB, FIRE_MESSAGE_ROOM , GPIO_HIGH);
				GPIO_voidSetPinValue( GPIOB, FIRE_MESSAGE_ROOM , GPIO_LOW);
			/* 2- Power On The Led and The buzzer */
				GPIO_voidSetPinValue( GPIOB, LED_ROOM     , GPIO_HIGH); // >>> Power On the Led
				GPIO_voidSetPinValue( GPIOB, BUZZER_ROOM  , GPIO_HIGH); // >>> Power On the Buzzer
			
			/* 3- Turn On DC_Motor CW "Clock Wise" to Open the window/Balcony */
				HDC_MOTOR_voidMoveMotor( ClockWise_DC_MOTOR , GPIOB , DC_MOTOR_PIN_A_ROOM , DC_MOTOR_PIN_B_ROOM);
				/* Delay for '1' Secods to open the door */
				MSTK_voidInit(); //Clock = AHB / 8 , hence 'tick = 1 us'
				MSTK_voidSetBusyWait( 1000000 );//Wait for the door/window to be opened 
				HDC_MOTOR_voidMoveMotor( STOP_DC_MOTOR , GPIOB , DC_MOTOR_PIN_A_ROOM , DC_MOTOR_PIN_B_ROOM);
			
			/* 4- Turn Off Source of Electricity */
				GPIO_voidSetPinValue( GPIOB , Relay_ROOM , GPIO_HIGH); // >>> Turn on The relay
			
		}
		else 
		{
			/* Turn On DC_Motor CW "Clock Wise" to Open the window/Balcony */
			HDC_MOTOR_voidMoveMotor( ClockWise_DC_MOTOR , GPIOB , DC_MOTOR_PIN_A_ROOM , DC_MOTOR_PIN_B_ROOM);
			/* Delay for '1' Secods to open the door */
			MSTK_voidInit(); //(Clock = AHB / 8 ) , hence 'tick = 1 us'
			MSTK_voidSetBusyWait( 1000000 );				
			HDC_MOTOR_voidMoveMotor( STOP_DC_MOTOR , GPIOB , DC_MOTOR_PIN_A_ROOM , DC_MOTOR_PIN_B_ROOM);
		}
		
	}
	else if ((MQ_2Value >= MQ2_Smoking_Value_mv) && (MQ_2Value <= MQ2_ON_Fire_Value_mv))
	{
		/* Power On The Led and The buzzer */
		GPIO_voidSetPinValue( GPIOB, LED_ROOM     , GPIO_HIGH); // >>> Power On the Led
		GPIO_voidSetPinValue( GPIOB, BUZZER_ROOM  , GPIO_HIGH); // >>> Power On the Buzzer
		
	}
	else if (MQ_2Value < MQ2_Smoking_Value_mv)
	{
		/* Power On The Led and The buzzer */
		GPIO_voidSetPinValue( GPIOB, LED_ROOM     , GPIO_LOW); // >>> Power off the Led
		GPIO_voidSetPinValue( GPIOB, BUZZER_ROOM  , GPIO_LOW); // >>> Power off the Buzzer
		
	}





}
