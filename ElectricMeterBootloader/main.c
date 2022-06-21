#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "URT.h"
#include "UDS.h"
#include "APP.h"
#include "util/delay.h"

/**
 * @brief this enum used to define bootloader states
 * 
 */
typedef enum{

	CHECKING_APPLICATION_EXIST=0,
	CHECKING_REQUEST_EXIST,
	CHECKING_TYPE_OF_REQUEST,

	REQUEST_DATA_TRANSFER,

	JMP_TO_APPLICATION_SECTION

}BOOTLOADER_STATE_t;

/**
 * @brief this variable used to express the bootloader current state
 * 
 */
BOOTLOADER_STATE_t Bootloader_State=CHECKING_APPLICATION_EXIST;


/**
 * @brief this array used to store default application state and UDS request in e2prom
 * 
 */
UINT8_t __attribute__((section(".eeprom"))) Updates[] = {
		APP_NOT_EXIST,
		UDS_REQ_DATA_TRANSFER
};

/**
 * @brief this function used as indication when entering bootloader section
 * 
 */
void
BootLoader_Indicator(void);


int
main(void){

	GIC;
	DIO_INIT();
	URT_Init();
	BootLoader_Indicator();

	while(1){

		switch(Bootloader_State){

		case CHECKING_APPLICATION_EXIST:

			if(APP_EXIST==APP_Read_State()){
				Bootloader_State=CHECKING_REQUEST_EXIST;
			}else {
				Bootloader_State=CHECKING_TYPE_OF_REQUEST;
			}

			break;
		case CHECKING_REQUEST_EXIST:

			if(UDS_Read_Request()!=UDS_NO_REQ){
				Bootloader_State=CHECKING_TYPE_OF_REQUEST;
			}else {
				Bootloader_State=JMP_TO_APPLICATION_SECTION;
			}

			break;
		case CHECKING_TYPE_OF_REQUEST:

			if (UDS_REQ_DATA_TRANSFER==UDS_Read_Request()) {
				Bootloader_State = REQUEST_DATA_TRANSFER;
				UDS_Send_Positive_Response();
			}
			break;

		case REQUEST_DATA_TRANSFER:

			if(TRUE==APP_Rx()){

				Bootloader_State=JMP_TO_APPLICATION_SECTION;

			}
			break;

		case JMP_TO_APPLICATION_SECTION:

			APP_Write_State(APP_EXIST);
			UDS_Write_Request(UDS_NO_REQ);
			BootLoader_Indicator();
			asm("jmp 0");
			break;

		default:
			break;

		}


	}
	return 0;
}

void
BootLoader_Indicator(void){

	UINT8_t i;
	DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_LOW);
	DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_LOW);
	for(i=0; i<5; ++i){

		DIO_WRITE_PIN_VALUE(DIO_PINC0, 1^DIO_READ_PIN_VALUE(DIO_PINC0));
		_delay_ms(1000);

	}

	DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_HIGH);

}
