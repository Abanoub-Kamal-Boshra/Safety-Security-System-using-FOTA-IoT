/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: EXTI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef _EXTI_PRIVATE_H_ 
#define _EXTI_PRIVATE_H_

typedef struct
{
	volatile u32 EXTI_IMR;
	volatile u32 EXTI_EMR;
	volatile u32 EXTI_RTSR;
	volatile u32 EXTI_FTSR;
	volatile u32 EXTI_SWIER;
	volatile u32 EXTI_PR;
}EXTI_type;
 #define EXTI     ((volatile EXTI_type *)0x40010400)
   
#endif