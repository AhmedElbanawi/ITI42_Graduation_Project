/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "URT.h"
/****************************************************************************/
static void
URT_Rx_INT(const URT_INT_t INT);
static void
URT_Rx(const URT_MODE_t MODE);
static void
URT_Tx_INT(const URT_INT_t INT);
static void
URT_Tx(const URT_MODE_t MODE);
/****************************************************************************/
void (*UART_ISR_PTR)(void)=NULL_PTR;
/****************************************************************************/
static void
URT_Rx_INT(const URT_INT_t INT)
{
	switch (INT) {
	case URT_IE:
		SET_BIT(UCSRB, 7);
		break;
	case URT_IC:
		CLEAR_BIT(UCSRB, 7);
		break;
	}
}
/****************************************************************************/
static void
URT_Tx_INT(const URT_INT_t INT)
{
	switch (INT) {
	case URT_IE:
		SET_BIT(UCSRB, 6);
		break;
	case URT_IC:
		CLEAR_BIT(UCSRB, 6);
		break;
	}
}
/****************************************************************************/
static void
URT_Rx(const URT_MODE_t MODE)
{
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 4);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 4);
		break;
	}
}
/****************************************************************************/
static void
URT_Tx(const URT_MODE_t MODE)
{
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 3);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 3);
		break;
	}
}
/****************************************************************************/
void
URT_Init(void)
{
	SET_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	UBRRH = URT_BAUD_RATE >> 8;
	UBRRL = URT_BAUD_RATE;


	/*- init URT transmiter -*/
	URT_Tx_INT(URT_IE);
	URT_Tx(URT_ENABLE);

	/*- init URT RX -*/
		URT_Rx_INT(URT_IE);
		URT_Rx(URT_ENABLE);

}
/****************************************************************************/
UINT8_t
URT_Rx_Byte(void)
{
	return UDR;
}
BOOL_t
Str_Cmp(const UINT8_t* Str1, const UINT8_t* Str2)
{
	BOOL_t IsSame = FALSE;
	while(*Str1 == *Str2){
		if(*Str1 == '\0'){
			IsSame = TRUE;
			break;
		}
		++Str1;
		++Str2;
	}
	return IsSame;
}
/****************************************************************************/
ISR(URT_RX_OVF_VECT)
{
	if(UART_ISR_PTR!=NULL_PTR)
	{
		UART_ISR_PTR();
	}
}
/****************************************************************************/
ISR(URT_TX_OVF_VECT)
{

}
/****************************************************************************/
