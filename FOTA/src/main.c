/*
 * main.c
 *
 *  Created on: Oct 13, 2020
 *      Author: besho & abanoub
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_int.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "ESP_interface.h"

void Get_Record(void);

volatile u8  u8RecBuffer[100] ; // used to store the Recored in it
volatile u8  u8RecCounter     ;
volatile u8  u8TimeOutFlag    ;
volatile u8  u8BLWriteReq     ;

/* var for control and clean the record */
volatile u8  *u8PtrHexFile       ;
volatile u32 u32LineOfHexFile    ;
u8           u8ipd               ;
volatile u8  u8BufCounter        ;
volatile u8  u8EndOfHexFileFlage ;

/* typedef --> pointer to function */
typedef void (*Function_t)(void);
/* create object from this type */
Function_t addr_to_call ;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002800;
	/* the first address in the flash (page_10 --> app area) 0x08002800
	 * but we use 0x08002804 as the first address contain the reset address (that initialize the stack pointer) */
	/* cast the address as pointer to function and put the value of pointee to a variable
	 * for ex: var = *(int*)y      */
	addr_to_call = *(Function_t*)(0x08002804);
	/* jump to application */
	addr_to_call();
}


void main(void)
{
	RCC_voidInitSysClock(); /* HSI */

	/* ESP ENABLE */

	RCC_voidEnableClock(RCC_APB2,14); /* USART1 */
	RCC_voidEnableClock(RCC_APB2,2);  /* PortA  */
	RCC_voidEnableClock(RCC_AHB,4);   /* FPEC   */


	/* A9 	==> TX out 50 MHz */ /* to RX of ESP */
	MGPIO_voidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
	/* A10 	==> RX input floating */ /* to TX of ESP */
	MGPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);



	/*  initialize the global variable */
	u8RecCounter     = 0;
	u8TimeOutFlag    = 0;
	u8BLWriteReq     = 1;
	/* var for control and clean the record */
	u32LineOfHexFile    = 0;
	u8ipd               = 0;
	u8BufCounter        = 0;
	u8EndOfHexFileFlage = 0;


	MUART_voidInit(); /* 115200 */

	MSTK_voidInit();

	ESP_voidInit();
	ESP_voidConnectToWifi();
	ESP_voidConnectToSrvTcp();

	/* getting the uploaded file array on u8PtrHexFile pointer */
	u8PtrHexFile = ESP_u8WebState();

	/* to know your start point of the record */
	// \r\r\nSEND OK\r\n\r\n+IPD,1420::020000040800F2\r\n:102000000050002021220008272200082B2200086F\r\n:1020100
	if(u8ipd == 0)
	{
		for(u8 i = 0 ; i < 200 ; i++)
		{
			if((u8PtrHexFile[i]) == 'I' && (u8PtrHexFile[i+1]) == 'P' && (u8PtrHexFile[i+2]) == 'D')
			{
				u8ipd = 1;
				u32LineOfHexFile = i+9;
				break;
			}
		}
	}


	while(1)
	{

		Get_Record();

		if (u8BLWriteReq == 1)
		{
			 FPEC_voidEraseAppArea(FPEC_START_APP_PAGE);
			u8BLWriteReq = 0;
		}

		/* Parse */
		Parser_voidParseRecord(u8RecBuffer);

		/* jump to the flashed application if the flag is raised */
		if(u8EndOfHexFileFlage == 1)
		{
			func();
		}

	}
}

//
// \r\r\nSEND OK\r\n\r\n+IPD,1420::020000040800F2\r\n:102000000050002021220008272200082B2200086F\r\n:1020100
void Get_Record(void)
{
	u8BufCounter = 0;

	for(u16 j = u32LineOfHexFile ; j < HEX_FILE_LENGTH ; j++)
	{
		/* this for small Recored take it only, not take from the last one */
		/* clear the reminder elements of the u8RecBuffer[] array */
		if( *(u8PtrHexFile+j) == '\r' && *(u8PtrHexFile+(j+1)) == '\n' && *(u8PtrHexFile+(j+2)) != '+')
		{
			/* set the start of the next entering for loop */
			u32LineOfHexFile = j+2;
			while(u8BufCounter !=99)
			{
				u8RecBuffer[u8BufCounter] = 0;
				u8BufCounter++;
			}
			break;
		}
		else
		{
			// as if IPD come inside the file (and can be inside the current Record too)
			if(*(u8PtrHexFile+(j)) == '+' && *(u8PtrHexFile+(j+1)) == 'I')
			{
				/* to skip the start word (+IPD,...) */
				j = j + 9;
				/* to rewrite over (\r\n) that written by error */
				u8BufCounter = u8BufCounter - 2;
				continue;
			}
			else
	 		{
				/* the end of Hex File */
				if(*(u8PtrHexFile+(j)) == 'C' && *(u8PtrHexFile+(j+1)) == 'L' && *(u8PtrHexFile+(j+2)) == 'O' && *(u8PtrHexFile+(j+3)) == 'S')
				{
					u8EndOfHexFileFlage = 1;
		 			break;
				}

				/* if all cases not achieved then we inside the record */
				u8RecBuffer[u8BufCounter] = *(u8PtrHexFile+(j));
				u8BufCounter++;

			}
		} // end of general else

	} // end of for loop

} // end of function Get_Record



