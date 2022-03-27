/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void MSPI1_voidInit(void);  /*home work*/
void MSPI1_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 * Copy_DataToReceive);
void MSPI1_voidSendReceiveASynch(u8 Copy_u8DataToTransmit, void(*CallBack)(u8));
#endif