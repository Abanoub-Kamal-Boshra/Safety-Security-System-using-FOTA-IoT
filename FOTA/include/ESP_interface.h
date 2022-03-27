/********************************************************************************/
/* Author  : BESHO																*/
/* Version : V01																*/
/* Date    : 28 SEP 2020														*/
/********************************************************************************/


#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H


/* macros */
#define HEX_FILE_LENGTH 		16000


/* function prototypes */

void ESP_voidInit(void);

u8 u8ValidateCmd(u32 Copy_u32UartRecEchoTime);

u8 u8ValidateCmd1(u32 Copy_u32UartRecEchoTime);

void ESP_voidConnectToWifi(void);

void ESP_voidConnectToSrvTcp(void);

u8 *ESP_u8WebState(void);



#endif
