/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: First
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "TIM_interface.h"
#include "TFT_interface.h"
#include "SPI_interface.h"
#include "KPD_interface.h"
#include "BUZERR_interface.h"
#include "SERVO_interface.h"
#include "ULTRASONIC_interface.h"
#include "EXTI_interface.h"

#include "MUSART1_interface.h"
#include "HESP8266_interface.h"

#define Open  0
void UltraSonicFuntion(void);

void adel(void)
{
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_HIGH);
}

void main()

{


	MRCC_voidInitSysClock();                          // enable clock of the processor
	MRCC_voidEnableClock(RCC_APB2,2);                 // enable clock of PORTA
	MRCC_voidEnableClock(RCC_APB2,3);                 // enable clock of PORTB
	MRCC_voidEnableClock(RCC_APB2,12);				  // enable clock of spi
	MRCC_voidEnableClock(RCC_APB2 , RCC_AFIO_EN);	// enable clock of alternative function

	/* Enable The Clock Of SPI1 */
	MRCC_voidEnableClock( RCC_APB2 , RCC_USART1_EN );

	MRCC_voidEnableClock(RCC_APB2 , RCC_TIM1_EN);  	// enable clock of timer1 for ultrasonic
	MRCC_voidEnableClock(RCC_APB1 , RCC_TIM2_EN);  	// enable clock of timer2 for busy wait
	MRCC_voidEnableClock(RCC_APB1 , RCC_TIM3_EN);	// enable clock of timer3 for trigger source for ultrasonec
	MRCC_voidEnableClock(RCC_APB1 , RCC_TIM4_EN);	// enable clock of timer4 for PWM

	//MGPIO_voidSetPinDirection(GPIO_U8_A,GPIO_U8_PIN0,GPIO_OUTPUT_2MHZ_PP);

	/*FOR TFT */
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN1,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN2,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN7,GPIO_OUTPUT_SPEED_10MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN5,GPIO_OUTPUT_SPEED_10MHZ_AFPP);
	/*FOR BUZZER*/
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN12,GPIO_OUTPUT_SPEED_2MHZ_PP);

	//----------------------------------------------------------------------------------------
	/*FOR KPD*/
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN0,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN1,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN5,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN11,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN12,GPIO_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN13,GPIO_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN14,GPIO_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN10,GPIO_INPUT_PULL_UP_DOWN);

	// FOR switch between ultrasonic and login system
	/*	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN15,GPIO_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN15,GPIO_PIN_HIGH);*/


	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN0,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN1,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN5,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN11,GPIO_PIN_HIGH);

	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN12,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN13,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN14,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(GPIO_PORTB,GPIO_PIN10,GPIO_PIN_HIGH);
	//---------------------------------------------------------------------------------

	// pin configuration for test delay with TIM1
	MGPIO_voidSetPinDirection(GPIO_PORTA , GPIO_PIN8 , GPIO_INPUT_FLOATION); 		// PIN_A8 is Floating for TIM1
	MGPIO_voidSetPinDirection(GPIO_PORTA , GPIO_PIN11 , GPIO_OUTPUT_SPEED_2MHZ_PP); 	// PIN_A0 for output trigger

	//-------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------
	// pin configuration
	MGPIO_voidSetPinDirection(GPIO_PORTB , GPIO_PIN6 , GPIO_OUTPUT_SPEED_50MHZ_AFPP); 	// PIN_B6 for output PWM_CH1
	MGPIO_voidSetPinDirection(GPIO_PORTB , GPIO_PIN7 , GPIO_OUTPUT_SPEED_50MHZ_AFPP); 	// PIN_B7 for output PWM_CH2
	MGPIO_voidSetPinDirection(GPIO_PORTB , GPIO_PIN8 , GPIO_OUTPUT_SPEED_50MHZ_AFPP); 	// PIN_B8 for output PWM_CH3
	MGPIO_voidSetPinDirection(GPIO_PORTB , GPIO_PIN9 , GPIO_OUTPUT_SPEED_50MHZ_AFPP); 	// PIN_B9 for output PWM_CH4
	//-----------------------------------------------------------------------------------------
	//-------------------------------------------------------------------
	/*wifi*/
	MGPIO_voidSetPinDirection(GPIO_PORTA, GPIO_PIN9, GPIO_OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, GPIO_PIN10, GPIO_INPUT_FLOATION );
	//---------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	/*IR sensor*/

	MGPIO_voidSetPinDirection(GPIO_PORTA, GPIO_PIN4, GPIO_INPUT_FLOATION );
	//----------------------------------------------------------


	//---------------------------------------------------------------------------------------
	/*EXTI Intrapt*/
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN3,GPIO_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(GPIO_PORTA,GPIO_PIN6,GPIO_OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN3,GPIO_PIN_HIGH);
	EXTI3_voidSetCallBack(adel);

	MEXTI_voidInit();
	//	 MNVIC_u8SetInterruptPriority(9,1,0,GROUP5);
	MEXTI_voidSetSignalLatch(EXTI_LINE3,EXTI_FALLING);
	MEXTI_voidEnable(EXTI_LINE3);

	//----------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	MSTK_voidInit();
	MSPI1_voidInit();
	HTFT_voidInit();
	HUltrasonicInti();
	/* Initialize NVIC */
	MNVIC_voidInit();
	/* Enable USART1 From NVIC */
	MNVIC_u8EnableInterrupt( 37 );
	// enable the IRQ from NVIC
	MNVIC_u8EnableInterrupt(30); 					// Enable the INT for TIM4

	// setup the priority
	MNVIC_voidSetInterruptPriority(30 , 3 , 0);		// Priority for TIM4

	MNVIC_u8EnableInterrupt(9);                    //Exti intrapt
	//------------------------------------------------------------------------------------------

	/* Initialize USART1 */
	MUSART1_voidInit();
	/* Initialize ESP8266 */
	HESP8266_voidInit();

	HESP8266_voidConnectToWiFi((u8 *)"AndroidAP",(u8 *)"akne9573");

	//------------------------------------------------------------------------------------------
	//MSTK_voidSetIntervalPeriodic(100 , HUltraSonicTriger);		// Send Trigger with 10Hz frequency
	//	MTIM3_voidSetIntervalPeriodic(10,HUltraSonicTriger);

	//HTFT_voidDisplayImage(image);
	//HTFT_voidFillColor(0xf0f0);
	//HTFT_voidDrawRect(0,10,0,30,0);
	//u8 Local_buttom;
	//u8 x;

	u8 name[]="welcome";
	u8 name1[]="Adel can";
	u8 name2[]="you enter";
	u8 name3[]="pass :";

	u16 LOCAL_PASS =1010 ;
	u8 Local_index;
	u8 flag = 0 ;

	//HTFT_voidWriteNumber(30,10,0xf0f0,0xffff,1200);
	HTFT_voidFillColor(0x0000);
	while(1)
	{
		UltraSonicFuntion();
		u8 Local_u8SwitchValue = MGPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN6);

		if(Local_u8SwitchValue == 1)
		{
			HTFT_voidFillColor(0x0000);
			HTFT_voidDrawString(20,0,0xffff,0x0000,name);
			HTFT_voidDrawString(0,20,0xffff,0x0000,name1);
			HTFT_voidDrawString(0,40,0xffff,0x0000,name2);
			HTFT_voidDrawString(0,60,0xffff,0x0000,name3);
			u8 Local_u8Number=0xff;
			for (Local_index=0;Local_index<4;Local_index++)
			{
				u16 pass=0;
				u8 x_axis = 0;
				Local_u8Number=KPD_U8GetPressedKey();
				while (Local_u8Number==0xff)
				{
					Local_u8Number=KPD_U8GetPressedKey();
				}

				while(Local_u8Number!='*')
				{
					HTFT_voidWriteNumber(20+x_axis,80,0xffff,0x0000,Local_u8Number);
					MSTK_voidSetBusyWait(500000);
					HTFT_voidDrawChar(20+x_axis,80,0xffff,0x0000,'*');
					x_axis=x_axis+20;
					pass=pass*10+Local_u8Number;
					Local_u8Number=KPD_U8GetPressedKey();
					while (Local_u8Number==0xff)
					{
						Local_u8Number=KPD_U8GetPressedKey();
					}
				}
				if (pass == LOCAL_PASS)
				{
					flag = 1 ;
					u8 door[]="it's open";
					HTFT_voidFillColor(0x0000);
					HTFT_voidDrawString(20,0,0xff00,0x0000,name);
					HTFT_voidDrawString(0,20,0xff00,0x0000,door);
					MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_LOW);
					break;
				}
				else
				{
					flag = 0;
					if(Local_index==3)
					{
						break;
					}

					HTFT_voidFillColor(0x0000);
					u8 name4[]="OPSS!!";
					HTFT_voidDrawString(20,0,0xf0f0,0x0000,name4);
					HTFT_voidDrawString(0,20,0xffff,0x0000,name1);
					HTFT_voidDrawString(0,40,0xffff,0x0000,name2);
					HTFT_voidDrawString(0,60,0xffff,0x0000,name3);
				}
			}

			if(flag==1)
			{
				HSERVO_viodSetServoAngle(90 , SERVO_CHANNEL_1);
				//HSERVO_viodSetServoAngle(180 , SERVO_CHANNEL_1);
				MSTK_voidSetBusyWait(20000);
				MSTK_voidSetBusyWait(2000000);
				u8 return_sensor_IR=MGPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN4);
				while(return_sensor_IR==Open)
				{
					return_sensor_IR=MGPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN4);
				}
				HSERVO_viodSetServoAngle(180 , SERVO_CHANNEL_1);
				MSTK_voidSetBusyWait(20000);
				HTFT_voidFillColor(0x0000);
			}
			else
			{
				HTFT_voidFillColor(0x0000);
				MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_LOW);
				u8 name5[]="lock";
				HTFT_voidDrawString(0,40,0xf0f0,0x0000,name5);
				HESP8266_voidConnectToSrvTcp2((u8 *)"api.thingspeak.com" , (u8 *)"80");
				HESP8266_voidCIPsend( (u8 *) "53");
				HESP8266_voidStealingSys((u8*) "1");
				for(u8 i = 0; i<10;i++)
				{
					HBUZERR_HighAlarm();

				}
				HTFT_voidFillColor(0x0000);
			}
		}
		else
		{
			// the code of ultrasonic
			UltraSonicFuntion();
			HESP8266_voidConnectToSrvTcp((u8 *)"162.253.155.226" , (u8 *)"80");
			u8 reseve =	HESP8266_u8ReceiveHttpReq((u8*)"__door.txt",(u8*)"49");
			reseve=reseve-48;
			if(reseve==1)
			{
				HSERVO_viodSetServoAngle(90,SERVO_CHANNEL_1);

			}
			else if(reseve==0)
			{
				HSERVO_viodSetServoAngle(180,SERVO_CHANNEL_1);
			}

		}

		UltraSonicFuntion();
	}
}

void UltraSonicFuntion(void)
{
	for(u8 i=0;i<5;i++)
	{
		HUltraSonicTriger();
		volatile f32 distance =HUltrasonicReturnDistance();
		MSTK_voidSetBusyWait(50000);
		if((distance>5) && (distance<30))
		{

			for(u8 i = 0; i<10;i++)
			{
				HBUZERR_HighAlarm();

			}
		}
	}




}
