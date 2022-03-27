#include	"STD_TYPES.h"
#include	"BIT_MATH.h"

#include   "GPIO_interface.h"

#include	"SPI_interface.h"
#include	"SPI_private.h"
#include	"SPI_config.h"



void MSPI1_voidInit(void)
{
#if DATA_FRAM_FORMAT == EIGHT_BIT
	CLR_BIT(MSPI1->CR1,11);
#elif DATA_FRAM_FORMAT == SIXTEEN_BIT
	SET_BIT(MSPI1->CR1,11);

#endif

#if SLAVE_SELECT_MODE == SOFTWARE_MODE
	SET_BIT(MSPI1->CR1,9);
#if INTERNAL_SLAVE_SELECT == 1
	SET_BIT(MSPI1->CR1,8);
#endif
#endif



#if DATA_ORDER == MSB
	CLR_BIT(MSPI1->CR1,7);
#endif
#if BOUD_RATE == DIVIDED_BY_2
	CLR_BIT(MSPI1->CR1,5);
	CLR_BIT(MSPI1->CR1,4);
	CLR_BIT(MSPI1->CR1,3);
#endif
#if MASTER_OR_SLAVE == MASTER
	SET_BIT(MSPI1->CR1,2);
#endif
#if CLOCK_POLARITY == 0
	CLR_BIT(MSPI1->CR1,1);
#elif CLOCK_POLARITY == 1
	SET_BIT(MSPI1->CR1,1);
#endif

#if CLOCK_PHASE == 1
	SET_BIT(MSPI1->CR1,0);
#endif

	/*able SPI*/
	SET_BIT(MSPI1->CR1,6);


	MSPI1->CR1=0X0347;
}
void MSPI1_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 * Copy_DataToReceive)
{
	/*clear for slave select pin*/
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_PIN_LOW);
	
	/*Send Data*/
	MSPI1->DR = Copy_u8DataToTransmit;
	/*Wait busy flag to finsh*/
	while(GET_BIT(MSPI1->SR,7)==1);
	
	/*Return to the received data*/
	* Copy_DataToReceive = MSPI1->DR ;
	
	/*Set slave select pin*/
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_PIN_HIGH);

	/*Enable SPI*/
	//SET_BIT(MSPI1->CR1,6);
}
