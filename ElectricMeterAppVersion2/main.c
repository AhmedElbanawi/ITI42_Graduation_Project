#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "URT.h"
#include "CFG_PAR.h"
#include "util/delay.h"
#include "REQ.h"


int
main(void){

	GIE;
	DIO_INIT();
	URT_Init();
	REQ_Init();
	DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_LOW);
	DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_LOW);
	_delay_ms(3000);

	while(1){

		DIO_WRITE_PIN_VALUE(DIO_PINC1, 1^DIO_READ_PIN_VALUE(DIO_PINC1));
		_delay_ms(50);
		DIO_WRITE_PIN_VALUE(DIO_PINC0, 1^DIO_READ_PIN_VALUE(DIO_PINC0));
		_delay_ms(50);

	}

	return 0;
}

