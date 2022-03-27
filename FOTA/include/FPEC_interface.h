#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE

/* macros */
#define FPEC_START_APP_PAGE		10


void FPEC_voidEraseAppArea(u8 Copy_u8PageNumber);
	
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

#endif
