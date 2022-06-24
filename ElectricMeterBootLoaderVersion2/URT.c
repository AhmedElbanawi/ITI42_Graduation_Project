#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "URT.h"

void URT_Rx(const URT_MODE_t MODE){
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 4);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 4);
		break;
	}
}
void URT_Tx(const URT_MODE_t MODE){
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 3);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 3);
		break;
	}
}
void URT_Init(void){
	SET_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	UBRRH = URT_BAUD_RATE >> 8;
	UBRRL = URT_BAUD_RATE;

	/*enable full duplex mode*/
	URT_Tx(URT_ENABLE);
	URT_Rx(URT_ENABLE);
}

UINT8_t URT_Rx_Char(void){
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<7)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}
void URT_Tx_Char(const UINT8_t CHAR){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<5)) )
	;
	/* Put data into buffer, sends the data */
	UDR = CHAR;
}
