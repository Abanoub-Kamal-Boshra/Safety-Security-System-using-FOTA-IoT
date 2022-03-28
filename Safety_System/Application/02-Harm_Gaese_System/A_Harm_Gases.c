/***********************************************       Documentation     *********************************************/
/*** Author  :  Solyma & Adel                       ****************/
/*** AFire_System.c				 	    			****************/
/*** Layer    : Application             		    ****************/
/*** Date    : 11/7/2021                    		****************/
/*** Version :  01                          		****************/
/*******************************************************************/
/***********************************************************************************************************************/



/*******************************************  Librariers Which we will need *******************************************/
#include"A_STD_TYPES.h"
#include"A_BIT_MATH.h"
/* Filles Of MCAL */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "MSTK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "TIM_interface.h"


/*Files OF HAL layers*/
#include "MQ_4_interface.h"         //MQ_4 Sensor for Natural gase detection
#include "DC_MOTOR_interface.h"     //DC_Motor For turnning on/Off Windows
#include "MQ_7_interface.h"         //MQ_7 Sensor for CO gase detectionn
#include "SERVO_interface.h"/*Servo motor */

			/***************************************   PINS DEFINITIONS   ***************************************/
u8  S(u8 Copy_u8Port , u8 Copy_u8Pin);

 /************* Pins For NAtural Gas System *************/

//(1) Analog Pins	
#define MQ_4ROOM1                 		 ADC_CH1 //PIN A1
//(2) Digital Pins
#define NATURAL_GAS_MESSAGE_ROOM1	     PIN0    //PIN B0 (Message + LED)
//#define NATURAL_GAS_LED_ROOM1      		 PIN1    //PIN B5
#define NATURAL_GAS_SERVO_MPTOR_ROOM1    PIN6    //PIN B6
#define NATURAL_GAS_BUZZER_ROOM1     	 PIN5 	 //PIN b5
#define NATURAL_GAS_DC_MPTOR_PINA_ROOM1  PIN9	 //PIN B9
#define NATURAL_GAS_DC_MPTOR_PINB_ROOM1  PIN10	 //PIN B10


/************* Pins For CO Gas System *************/

//(1) Analog Pins	
#define MQ_7ROOM1                    ADC_CH2 //PIN A2
//(2) Digital Pins
#define CO_GAS_MESSAGE_ROOM1	     PIN1     //PIN B1
//#define CO_GAS_LED_ROOM1      		 PIN10    //PIN B10
#define CO_GAS_SERVO_MPTOR_ROOM1     PIN7     //PIN B7
#define CO_GAS_BUZZER_ROOM1     	 PIN11 	  //PIN b11
#define CO_GAS_DC_MPTOR_PINA_ROOM1   PIN12	  //PIN B12
#define CO_GAS_DC_MPTOR_PINB_ROOM1   PIN13	  //PIN B13

/******************** PIN For General Key "Source of Gas "****************/

#define GENERAL_KEY_SERVO_MOTOR      PIN8      //PIN B8

			/* Prototypes of Used Functions */
void APP_SET_NATURAL_GAS_SYSTEM(u8 NATURAL_GAS_MESSAGE_ROOM_PIN , u8 NATURAL_GAS_SERVO_MPTOR_ROOM_PIN ,u8 NATURAL_GAS_BUZZER_ROOM_PIN, u8 NATURAL_GAS_DC_MPTOR_PINA_ROOM_PIN ,u8 NATURAL_GAS_DC_MPTOR_PINB_ROOM_PIN );
void APP_SET_CO_GAS_SYSTEM(u8 CO_GAS_MESSAGE_ROOM_PIN , u8 CO_GAS_SERVO_MPTOR_ROOM_PIN ,u8 CO_GAS_BUZZER_ROOM_PIN, u8 CO_GAS_DC_MPTOR_PINA_ROOM_PIN ,u8 CO_GAS_DC_MPTOR_PINB_ROOM_PIN );

/*************************************************************************************************************************/
void main(void)
{
	/**********************************************    Clock Initialization      *****************************************/

	RCC_voidInitSysClock(); //Clock of the processor
	RCC_voidEnableClock(RCC_APB2 , IOPA); //Enable Clock for GPIOA Peripheral
	RCC_voidEnableClock(RCC_APB2 , IOPB); //Enable Clock for GPIOA Peripheral
	RCC_voidEnableClock(RCC_APB2 , IOPC); //Enable Clock for GPIOA Peripheral
	RCC_voidEnableClock(RCC_APB2 , ADC1); //Enable Clock for ADC1 Peripheral
	RCC_voidEnableClock(RCC_APB2 , AFIO); //Enable Clock for AFIO Peripheral "So we may use External interrupts"
	RCC_voidEnableClock(RCC_APB1 , TIM4);/*Timer*/
	RCC_voidEnableClock(RCC_APB2 , USART1);//Enable Clock for USART For "IOT"


/*************************************************************************************************************************/

	/**********************************************    Interrupt Handling      *****************************************/

	MNVIC_voidEnableInterrupt( NVIC_TIM4);   //Enable interrupt for Tim4
	MNVIC_voidEnableInterrupt( NVIC_EXTI0);  //Enable interrupt for EXTI0
	MNVIC_voidEnableInterrupt( NVIC_ADC1_2); //Enable interrupt for ADC
	MNVIC_voidEnableInterrupt( 37 ); //Enable Interrupt For USART

	MNVIC_voidInitPriority(); //NVIC_GROUP_2_SUB_2
	MNVIC_voidSetPriority (NVIC_TIM4   , 0b0000 ); //First Priority
	MNVIC_voidSetPriority (NVIC_EXTI0  , 0b0100 ); //Second Priority
	MNVIC_voidSetPriority (NVIC_ADC1_2 , 0b1000 );//Third Priority

	/**********************************************       PINS Configuration     *******************************************/	

/**********************************************       NATURAL_GAS_ROOM1     *******************************************/
	GPIO_voidSetPinDirection( GPIOB , NATURAL_GAS_MESSAGE_ROOM1    , OUTPUT_SPEED_2MHZ_PP);    // >>> MESSAGE_PIN_Room1
	GPIO_voidSetPinDirection( GPIOB , NATURAL_GAS_SERVO_MPTOR_ROOM1, OUTPUT_SPEED_50MHZ_AFPP);/*Servo motor*/
	GPIO_voidSetPinDirection( GPIOB , NATURAL_GAS_BUZZER_ROOM1     , OUTPUT_SPEED_2MHZ_PP);
	

	
/**********************************************       NATURAL_GAS_ROOM1     *******************************************/
	GPIO_voidSetPinDirection( GPIOB , CO_GAS_MESSAGE_ROOM1    , OUTPUT_SPEED_2MHZ_PP);    // >>> MESSAGE_PIN_Room1
	GPIO_voidSetPinDirection( GPIOB , CO_GAS_SERVO_MPTOR_ROOM1, OUTPUT_SPEED_50MHZ_AFPP);/*Servo motor*/
	GPIO_voidSetPinDirection( GPIOB , CO_GAS_BUZZER_ROOM1     , OUTPUT_SPEED_2MHZ_PP);
	
	/****************************************   PIN For General Key "Source of Gas"  **************************/
	GPIO_voidSetPinDirection( GPIOB , GENERAL_KEY_SERVO_MOTOR , OUTPUT_SPEED_50MHZ_AFPP);/*Servo motor*/

	/***************************************** Pins for WiFi *********************************/
	   GPIO_voidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_2MHZ_AFPP);
	   GPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);
	/****************************************************************************************************/
	
	   /* Initialize USART1 */
	   	MUSART1_voidInit();
	   	/* Initialize ESP8266 */
	   	HESP8266_voidInit();
	/* Initialization of some peripherals */
	MSTK_voidInit(); //Clock = AHB / 8 , hence 'tick = 1 us'
	
	u32 MQ_4Value;
	u32 MQ_7Value;

	while(1)
	{
		MQ_4Value = HMQ_4_u32ReadAnalogVolt_mv(MQ_4ROOM1);

		if (MQ_4Value >= MQ4_THRESHOLD_VALUE_mv)
		{
			APP_SET_NATURAL_GAS_SYSTEM( NATURAL_GAS_MESSAGE_ROOM1 , NATURAL_GAS_SERVO_MPTOR_ROOM1 , NATURAL_GAS_BUZZER_ROOM1, NATURAL_GAS_DC_MPTOR_PINA_ROOM1 ,NATURAL_GAS_DC_MPTOR_PINB_ROOM1 );

		}
		MQ_7Value = HMQ_7_u32ReadAnalogVolt_mv(MQ_7ROOM1);
		if (MQ_7Value >= MQ7_THRESHOLD_Value_mv)
		{
			APP_SET_CO_GAS_SYSTEM( CO_GAS_MESSAGE_ROOM1 , CO_GAS_SERVO_MPTOR_ROOM1 ,CO_GAS_BUZZER_ROOM1 , CO_GAS_DC_MPTOR_PINA_ROOM1 , CO_GAS_DC_MPTOR_PINB_ROOM1 );

		}
	}




}
void APP_SET_NATURAL_GAS_SYSTEM(u8 NATURAL_GAS_MESSAGE_ROOM_PIN , u8 NATURAL_GAS_SERVO_MPTOR_ROOM_PIN ,u8 NATURAL_GAS_BUZZER_ROOM_PIN, u8 NATURAL_GAS_DC_MPTOR_PINA_ROOM_PIN ,u8 NATURAL_GAS_DC_MPTOR_PINB_ROOM_PIN )
{
	
		/* (1) Send a message to the user*/

		GPIO_voidSetPinValue(GPIOB , NATURAL_GAS_MESSAGE_ROOM_PIN , GPIO_HIGH);
		//HESP8266_voidCIPsend( (u8 *) "53"); //Length >> 53
		HESP8266_voidConnectToWiFi((u8 *)"AndroidAP",(u8 *)"akne9573");
		HESP8266_voidConnectToSrvTcp((u8 *)"api.thingspeak.com" , (u8 *)"80");
		HESP8266_voidCIPsend( (u8 *) "53");
		u8 d= S(GPIOB ,NATURAL_GAS_MESSAGE_ROOM_PIN);

		/* (2) Turning Off the source of Natural gas "Using servo motor"*/
		HSERVO_viodSetServoAngle( 90 , SERVO_CHANNEL_1);
		
		/* (3) Alarming : Turning on the Buzzer and LED */
		GPIO_voidSetPinValue(GPIOB , NATURAL_GAS_BUZZER_ROOM_PIN , GPIO_HIGH);
		
		/* (4) Opening Window to increase Fresh air in the place */
		HDC_MOTOR_voidMoveMotor( ClockWise_DC_MOTOR , GPIOB , NATURAL_GAS_DC_MPTOR_PINA_ROOM_PIN , NATURAL_GAS_DC_MPTOR_PINB_ROOM_PIN);
		/* Delay for '1' Seconds to open the door */
		MSTK_voidSetBusyWait( 1000000 );//Wait for the door/window to be opened 
		HDC_MOTOR_voidMoveMotor( STOP_DC_MOTOR , GPIOB , NATURAL_GAS_DC_MPTOR_PINA_ROOM_PIN , NATURAL_GAS_DC_MPTOR_PINB_ROOM_PIN);
		
}

void APP_SET_CO_GAS_SYSTEM(u8 CO_GAS_MESSAGE_ROOM_PIN , u8 CO_GAS_SERVO_MPTOR_ROOM_PIN ,u8 CO_GAS_BUZZER_ROOM_PIN, u8 CO_GAS_DC_MPTOR_PINA_ROOM_PIN ,u8 CO_GAS_DC_MPTOR_PINB_ROOM_PIN )
{
	
		/* (1) Send a message to the user*/
		GPIO_voidSetPinValue(GPIOB , CO_GAS_MESSAGE_ROOM_PIN , GPIO_HIGH);

		/* (2) Turning Off the source of Natural gas "Using servo motor"*/
		HSERVO_viodSetServoAngle( 90 , SERVO_CHANNEL_2);
		
		/* (3) Alarming : Turning on the Buzzer and LED */
		GPIO_voidSetPinValue(GPIOB , CO_GAS_BUZZER_ROOM_PIN , GPIO_HIGH);
		
		/* (4) Opening Window to increase Fresh air in the place */
		HDC_MOTOR_voidMoveMotor( ClockWise_DC_MOTOR , GPIOB , CO_GAS_DC_MPTOR_PINA_ROOM_PIN , CO_GAS_DC_MPTOR_PINB_ROOM_PIN);
		/* Delay for '1' Seconds to open the door */
		MSTK_voidSetBusyWait( 1000000 );//Wait for the door/window to be opened 
		HDC_MOTOR_voidMoveMotor( STOP_DC_MOTOR , GPIOB , CO_GAS_DC_MPTOR_PINA_ROOM_PIN , CO_GAS_DC_MPTOR_PINB_ROOM_PIN);
		
}
u8  S(u8 Copy_u8Port , u8 Copy_u8Pin)
{
	u8 status = GET_BIT(Copy_u8Port , Copy_u8Pin );
		if (status == 1)
		{
			HESP8266_voidHarmGases((u8*) "1");
		}
		else
		{
			HESP8266_voidHarmGases((u8*) "0");
		}
	return status;
}
