/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/*Write it in a pair port , pin*/
#define MSPI1_SLAVE_PIN  GPIO_PORTA,GPIO_PIN0

/*Data farm format options : 1- EIGHT_BIT
 * 							 2- SIXTEEN_BIT*/
#define DATA_FRAM_FORMAT    EIGHT_BIT

/*Slave select mode options : 1- SOFTWARE_MODE
 * 							  2- HARDWARE_MODE*/
#define SLAVE_SELECT_MODE  SOFTWARE_MODE

/*OPTIONS : 0
 * 			1*/
#define INTERNAL_SLAVE_SELECT  1

/*Data order Most signeficant bit or least options : MSB
 * 													 LSB*/
#define DATA_ORDER  MSB

/*OPTIONS : DIVIDED_BY_2
 * 			DIVIDED_BY_4
 * 			DIVIDED_BY_8*/
#define BOUD_RATE  DIVIDED_BY_2

/*options : MASTER
 * 			SLAVE*/
#define MASTER_OR_SLAVE   MASTER
/*OPTIONS : 0  for rising first
 * 			1  for falling first*/
#define CLOCK_POLARITY  1

/*OPTIONS : 0  for read first
 * 			1  for write first*/
#define CLOCK_PHASE   1
#endif
