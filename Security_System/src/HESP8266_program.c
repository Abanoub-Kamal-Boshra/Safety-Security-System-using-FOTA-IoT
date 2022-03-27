

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUSART1_interface.h"

#include "HESP8266_interface.h"
#include "HESP8266_private.h"

#include "STK_interface.h"

u16 volatile Iterator = 0  ;
u8  volatile DataCome[1500] ;
u8  x = 0 ;

void HESP8266_CallBack ( void ){

	/* Receive ESP8266 Response */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */
	Iterator++;
	MUSART1_voidClearFlags();

}

void HESP8266_voidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	MUSART1_voidSetCallBack( HESP8266_CallBack );

	while( HESP8266_voidValidateBuffer() == 0 ){

		/* Clear ESP8266 Buffer */
		HESP8266_voidClearBuffer();
		/* Sending AT Command To Check ESP8266 Is Working Or Not  */
		MUSART1_voidSendSrtingSynch( (u8 *)"AT\r\n" );
		MSTK_voidSetBusyWait(1000000);

	}
	/* Clear ESP8266 Buffer */
	HESP8266_voidClearBuffer();

	while( HESP8266_voidValidateBuffer() == 0 ){


		HESP8266_voidClearBuffer();


		MUSART1_voidSendSrtingSynch( (u8 *)"AT+CWMODE=1\r\n" );
		MUSART1_voidSendSrtingSynch( (u8 *)"AT+CIFSR\r\n" );


		MUSART1_voidSendSrtingSynch( (u8 *)"AT+CIPMUX=0\r\n" );
		MSTK_voidSetBusyWait(1000000);

	}
	HESP8266_voidClearBuffer();



}


void HESP8266_voidConnectToWiFi ( u8 * SSID , u8 * Password ){

	HESP8266_voidClearBuffer();

	while( HESP8266_voidValidateBuffer() == 0 ){

		/* Clear ESP8266 Buffer */
		HESP8266_voidClearBuffer();

		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CWJAP=\"" );
		MUSART1_voidSendSrtingSynch( (u8 *) SSID );
		MUSART1_voidSendSrtingSynch( (u8 *) "\",\"" );
		MUSART1_voidSendSrtingSynch( (u8 *) Password);
		MUSART1_voidSendSrtingSynch( (u8 *) "\"\r\n");
		MSTK_voidSetBusyWait(1000000);

	}

}

void HESP8266_voidConnectToSrvTcp ( u8 * Copy_u8IP , u8 * Copy_u8Port ){

	HESP8266_voidClearBuffer();

	while( HESP8266_voidValidateBuffer() == 0 ){

		/* Clear ESP8266 Buffer */
		HESP8266_voidClearBuffer();

		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8IP  );
		MUSART1_voidSendSrtingSynch( (u8 *) "\"," );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Port );
		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n" );

		MSTK_voidSetBusyWait(1000000);
	}

}

void HESP8266_voidConnectToSrvTcp2 ( u8 * Copy_u8thingspeak , u8 * Copy_u8Port ){

	HESP8266_voidClearBuffer();

	while( HESP8266_voidValidateBuffer() == 0 ){

		/* Clear ESP8266 Buffer */
		HESP8266_voidClearBuffer();

		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8thingspeak  );
		MUSART1_voidSendSrtingSynch( (u8 *) "\"," );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Port );
		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n" );

		MSTK_voidSetBusyWait(1000000);
	}

}

static void HESP8266_voidClearBuffer ( void ){

	u16 LOC_u8Iterator1 = 0 ;
	Iterator            = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 1500 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}


static u8 HESP8266_voidValidateBuffer( void ){

	u8  LOC_u8Status    = 0 ;
	u16 LOC_u8Iterator1 = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 1500  ; LOC_u8Iterator1++ ){

		if( ( DataCome[ LOC_u8Iterator1 ] == 'O' )  && ( DataCome[ LOC_u8Iterator1 + 1 ] == 'K' ) ){

			LOC_u8Status = 1 ;
			break ;

		}

	}
	return LOC_u8Status ;

}

//-----------------------------------------------------------------------------------------------------
/*massage*/


void HESP8266_voidCIPsend(u8 * Copy_u8Length)
{
	u8	LOC_U8Result=0 ;
	while(LOC_U8Result==0 )
	{
		HESP8266_voidClearBuffer();
		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CIPSEND=" );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Length );
		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n" );
		MSTK_voidSetBusyWait(1000000);
		LOC_U8Result = HESP8266_voidValidateBuffer() ;

		HESP8266_voidClearBuffer();
	}
}
void HESP8266_voidStealingSys(u8* Copy_u8Value)
{
	u8	LOC_U8Result=0 ;
	while(LOC_U8Result==0 )
	{
		MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=F4EJ50ZYJNUACA8X&field3=");
		MUSART1_voidSendSrtingSynch( (u8*) Copy_u8Value);

		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
		MSTK_voidSetBusyWait(1000000);
		LOC_U8Result = HESP8266_voidValidateBuffer() ;
	}
}
/*u8  S(u8 Copy_u8Port , u8 Copy_u8Pin)
{
	u8 status = MGPIO_u8GetPinValue(Copy_u8Port , Copy_u8Pin );
	if (status == 1)
	{
		HESP8266_voidStealingSys((u8*) "1");
	}
	else
	{
		HESP8266_voidStealingSys((u8*) "0");
	}
	return status;
}

*/






//--------------------------------------------------------------------------------------------------------


/***********************************************************************************/

u8 HESP8266_u8ReceiveHttpReq( u8 * Copy_u8FileID , u8 * Copy_u8Length ){

	HESP8266_voidClearBuffer();
	while(HESP8266_voidValidateBuffer()==0 )
	{
		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CIPSEND=" );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Length );
		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n" );
		MSTK_voidSetBusyWait(1000000);
	}
	HESP8266_voidClearBuffer();
	while(HESP8266_voidValidateBuffer()==0 )
	{
		MUSART1_voidSendSrtingSynch( (u8 *) "GET http://efraimyousef3.freevar.com/" );
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8FileID );
		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n" );
		MSTK_voidSetBusyWait(1000000);
	}
	return  DataCome[37] ;

}

void CIP_send(void)
{

	u8	LOC_U8Result=0 ;
	while(LOC_U8Result==0 )
	{
		HESP8266_voidClearBuffer();
		MUSART1_voidSendSrtingSynch( (u8 *) "AT+CIPSEND=95\r\n" );
		MSTK_voidSetBusyWait(1000000);
		LOC_U8Result = HESP8266_voidValidateBuffer() ;
	}
	HESP8266_voidClearBuffer();
}

void HESP8266_voidSendHttpReq5( u8*Copy_u8temprature,u8*Copy_humidity,u8*Copy_gas)
{
	u8	LOC_U8Result=0 ;

	while(LOC_U8Result==0 )
	{

		MUSART1_voidSendSrtingSynch( (u8 *) "GET /index.php?tmp=");
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8temprature);
		MUSART1_voidSendSrtingSynch( (u8 *) "&hum=");
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_humidity);
		MUSART1_voidSendSrtingSynch( (u8 *) "&gas=");
		MUSART1_voidSendSrtingSynch( (u8 *) Copy_gas);



		MUSART1_voidSendSrtingSynch( (u8 *) " HTTP/1.1\r\nHost: efraimyousef3.freevar.com\r\n\r\n");

		MSTK_voidSetBusyWait(1000000);
		LOC_U8Result = HESP8266_voidValidateBuffer() ;
	}
}

/***********************************************************************************/


/*void HESP8266_voidSendHttpReq( u8*copy_u8fieldNum,u8*Copy_u8Value)
{
	u8	LOC_U8Result=0 ;
while(LOC_U8Result==0 )
{
	if (copy_u8fieldNum == 1) // for co(carbon oxide)(MQ7)
	{
	   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=NFLXE9EBLC1MN1E2&field1=");
	    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

		MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
		MSTK_voidSetBusyWait(1000000);
		LOC_U8Result = HESP8266_voidValidateBuffer() ;
	}
	else if (copy_u8fieldNum == 2) // for Natural_gas(MQ4)
		{
		   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=0UXWOI5K2OEIJ2GR&field1=");
		    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

			MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
			MSTK_voidSetBusyWait(1000000);
			LOC_U8Result = HESP8266_voidValidateBuffer() ;
		}
	else if (copy_u8fieldNum == 3) // for MQ2_alarm
			{
			   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=35JKNUE28XSI2FLK&field1=");
			    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

				MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
				MSTK_voidSetBusyWait(1000000);
				LOC_U8Result = HESP8266_voidValidateBuffer() ;
			}
	else if (copy_u8fieldNum == 4) // for fire_alarm(flaming_sensor)
			{
			   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=Q6FEIUR7AFIKUMZX&field1=");
			    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

				MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
				MSTK_voidSetBusyWait(1000000);
				LOC_U8Result = HESP8266_voidValidateBuffer() ;
			}
	else if (copy_u8fieldNum == 5) // for stealing_alarm(ultrasonic_sensor)
			{
			   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=86XCIE538A07W34V&field1=");
			    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

				MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
				MSTK_voidSetBusyWait(1000000);
				LOC_U8Result = HESP8266_voidValidateBuffer() ;
			}
	else if (copy_u8fieldNum == 6) // for temperature_alarm(temp_sensor)
				{
				   MUSART1_voidSendSrtingSynch( (u8 *) "GET /update?api_key=DUL8YM1KIUZVB5PQ&field1=");
				    MUSART1_voidSendSrtingSynch( (u8 *) Copy_u8Value);

					MUSART1_voidSendSrtingSynch( (u8 *) "\r\n\r\n\r\n\r\n" );
					MSTK_voidSetBusyWait(1000000);
					LOC_U8Result = HESP8266_voidValidateBuffer() ;
				}
}
}

 */
