/********************************************************************************/
/* Author  : BESHO & Abanoub													*/
/* Version : V01																*/
/* Date    : 28 SEP 2020														*/
/********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "UART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"


u8 ESP_u8Response[ ESP_RESPONSE_LENGTH ] ;
volatile u8 u8ResponseHEX[ HEX_FILE_LENGTH ] ;


void ESP_voidInit(void)
{
	u8 Local_u8ValidFlag = 0;

	while(Local_u8ValidFlag == 0)
	{
		/*Stop Echo*/
		MUART_voidTransmit("ATE0\r\n");
		/*	Check command is done right
			ATE0 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(150);
	}
	
	Local_u8ValidFlag = 0;

	while(Local_u8ValidFlag == 0)
	{
		/*Set ESP station mode*/
		MUART_voidTransmit("AT+CWMODE=1\r\n");
		/*	Check command is done right
			AT+CWMODE=1 returns OK if all is okay*/
		Local_u8ValidFlag = u8ValidateCmd(150);
	}
}


u8 u8ValidateCmd(u32 Copy_u32UartRecEchoTime)
{
	u8 Local_u8ValidFlag = 0;
	u8 Local_u8Counter   = 0;
	u8 Local_u8TempChar  = 0;
	u8 i;

	for(i=0 ; i<ESP_RESPONSE_LENGTH ; i++)
	{
		ESP_u8Response[i] = 0;
	}

	/*Make sure that the MC is not receiving any more data from the ESP*/
	while (Local_u8TempChar != 255)
	{
		Local_u8TempChar = MUART_u8Receive(Copy_u32UartRecEchoTime);
		ESP_u8Response[Local_u8Counter] = Local_u8TempChar;
		Local_u8Counter++;
	}

	/*	Deleting last element as it is always 255 for stop receiving data	*/
	ESP_u8Response[Local_u8Counter-1] = 0;

	/* Checks if any of the received data contains the word "OK" meaning the command is done successfully
	 * Local_u8Counter-2 ---> as the last two elements is \r\n */
	for( i = 0; i < Local_u8Counter-2; i ++)
	{
		if(ESP_u8Response[i] == 'O' && ESP_u8Response[i+1] == 'K')
		{
			Local_u8ValidFlag = 1;
		}
	}
	return Local_u8ValidFlag;
}


u8 u8ValidateCmd1(u32 Copy_u32UartRecEchoTime)
{
	u8 Local_u8ValidFlag = 0;
	u16 Local_u8Counter  = 0;
	u8 Local_u8TempChar  = 0;
	u16 i;

	for(i=0 ; i < HEX_FILE_LENGTH ; i++)
	{
		u8ResponseHEX[i] = 0;
	}

	/*Make sure that the MC is not receiving any more data from the ESP*/
	while (Local_u8TempChar != 255)
	{
		Local_u8TempChar = MUART_u8Receive(Copy_u32UartRecEchoTime);
		u8ResponseHEX[Local_u8Counter] = Local_u8TempChar;
		Local_u8Counter++;
	}

	/*	Deleting last element as it is always 255 for stop receiving data	*/
	u8ResponseHEX[Local_u8Counter-1] = 0;

	/* Checks if any of the received data contains the word "OK" meaning the command is done successfully*/
	for(i = 0; i < Local_u8Counter - 2; i ++)
	{
		if(u8ResponseHEX[i] == 'O' && u8ResponseHEX[i+1] == 'K')
		{
			Local_u8ValidFlag = 1;
		}
	}
	return Local_u8ValidFlag;
}


void ESP_voidConnectToWifi(void)
{
	u8 Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* AT+CWJAP_CUR="wifi_name","wifi_password" */
		MUART_voidTransmit("AT+CWJAP_CUR=\"abanoub\",\"99999999\"\r\n");
		Local_u8Result = u8ValidateCmd(10000);
	}
}

void ESP_voidConnectToSrvTcp(void)
{
	u8 Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* set IP
		 * AT+CIPSTART = "TCP","162.253.155.226",80 */
		MUART_voidTransmit("AT+CIPSTART=\"TCP\",\"162.253.155.226\",80\r\n");
		Local_u8Result = u8ValidateCmd(30000);
	}

	Local_u8Result = 0;


}

u8* ESP_u8WebState(void)
{
	u8 i = 0;
	u8 Local_u8Result = 0;

	/* Send no of command chars */
	while(Local_u8Result == 0)
	{
		/* 46 IS  no of char of GET request
	   	   AT+CIPSEND=46+2(\r\n) = 49 */
		MUART_voidTransmit("AT+CIPSEND=49\r\n");
		Local_u8Result = u8ValidateCmd(10000);
	}

	Local_u8Result = 0;

	/* Send GET command ---> GET --- the address of file wanted to read */
	while(Local_u8Result == 0)
	{
		/* get state
		 * 49 -> GET http://efraimyousef2.freevar.com/status.txt
	   	    ->   */
		MUART_voidTransmit("GET http://efraimyousef2.freevar.com/status.txt\r\n");
		Local_u8Result = u8ValidateCmd1(900000);
	}
	Local_u8Result = 0;

	return u8ResponseHEX;
}

