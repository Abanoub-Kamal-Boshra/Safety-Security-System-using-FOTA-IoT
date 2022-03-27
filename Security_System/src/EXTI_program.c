/***********		Author: Adel Magdy   	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: EXTI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*EXTI0_CallBack)(void);
static void (*EXTI1_CallBack)(void);
static void (*EXTI3_CallBack)(void);


void MEXTI_voidInit(void)
{
	#if EXTI_SENSE_MODE == EXTI_FALLING
		SET_BIT(EXTI->EXTI_FTSR,EXTI_LINE);
	#elif EXTI_SENSE_MODE == EXTI_RAISING
		SET_BIT(EXTI->EXTI_RTSR,EXTI_LINE);
	#elif EXTI_SENSE_MODE == EXTI_IOC
		SET_BIT(EXTI->EXTI_FTSR,EXTI_LINE);
		SET_BIT(EXTI->EXTI_RTSR,EXTI_LINE); 
	#else 
		#error "Wrong choice of external interruptsense mode"
	#endif
	/*IN INTIALIZATION func we diable interrupts*/
	CLR_BIT(EXTI->EXTI_IMR,EXTI_LINE);
}

void MEXTI_voidSetSignalLatch(u8 Copy_u8LineID,u8 Copy_u8SenseMode)
{
	switch(Copy_u8SenseMode)
	{  
		case EXTI_FALLING :SET_BIT(EXTI->EXTI_FTSR,Copy_u8LineID);
						   CLR_BIT(EXTI->EXTI_RTSR,Copy_u8LineID);break;
	    case EXTI_RISING :SET_BIT(EXTI->EXTI_RTSR,Copy_u8LineID);
						   CLR_BIT(EXTI->EXTI_FTSR,Copy_u8LineID);break;
	    case EXTI_IOC :SET_BIT(EXTI->EXTI_FTSR,Copy_u8LineID);
		                   SET_BIT(EXTI->EXTI_RTSR,Copy_u8LineID);break;
	}
	/*we enable line*/
	SET_BIT(EXTI->EXTI_IMR,EXTI_LINE);
	
}


void MEXTI_voidEnable(u8 Copy_u8LineID)
{
	SET_BIT(EXTI->EXTI_IMR,Copy_u8LineID);
}

void MEXTI_voidDisable(u8 Copy_u8LineID)
{
	CLR_BIT(EXTI->EXTI_IMR,Copy_u8LineID);
}

void MEXTI_voidSetSoftWareTrigger(u8 Copy_u8LineID)
{
	SET_BIT(EXTI->EXTI_SWIER,Copy_u8LineID);
}
void EXTI0_voidSetCallBack(void (*pf)(void))
{
	EXTI0_CallBack=pf;
}
void EXTI1_voidSetCallBack(void (*pf)(void))
{
	EXTI1_CallBack=pf;
}

void EXTI3_voidSetCallBack(void (*pf)(void))
{
	EXTI3_CallBack=pf;
}
void EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();
	SET_BIT(EXTI->EXTI_PR,EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
	EXTI1_CallBack();
	SET_BIT(EXTI->EXTI_PR,EXTI_LINE1);
}
void EXTI3_IRQHandler(void)
{
	EXTI3_CallBack();
	SET_BIT(EXTI->EXTI_PR,EXTI_LINE3);
}
