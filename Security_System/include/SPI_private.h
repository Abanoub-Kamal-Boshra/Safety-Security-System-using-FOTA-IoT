/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

typedef struct 
{
	volatile u32 CR1            ; /*CONFIGURATIONS*/
	volatile u32 CR2            ;
	volatile u32 SR             ;
	volatile u32 DR             ; /*Data */
	volatile u32 CRCPR          ;
	volatile u32 RXCRCR         ;
	volatile u32 TXCRCR         ;
	volatile u32 I2SCFGR        ;
	volatile u32 I2SPR          ;
}SPI_t;

#define   MSPI1      ((volatile SPI_t *)0x40013000)

#endif
