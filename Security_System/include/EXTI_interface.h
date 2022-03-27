/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: EXTI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_

#define EXTI_FALLING    1
#define EXTI_RISING     3
#define EXTI_IOC        5

#define EXTI_LINE0      0
#define EXTI_LINE1      1
#define EXTI_LINE2      2
#define EXTI_LINE3      3
void MEXTI_voidInit(void);

void MEXTI_voidSetSignalLatch(u8 Copy_u8LineID,u8 Copy_u8SenseMode);

void MEXTI_voidEnable(u8 Copy_u8LineID);

void MEXTI_voidDisable(u8 Copy_u8LineID);

void MEXTI_voidSetSoftWareTrigger(u8 Copy_u8LineID);

void EXTI0_voidSetCallBack(void (*pf)(void));
void EXTI1_voidSetCallBack(void (*pf)(void));
void EXTI3_voidSetCallBack(void (*pf)(void));

#endif
