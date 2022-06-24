#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "URT.h"
#include "UDS.h"
#include "APP.h"
#include "util/delay.h"
#include "CFG_PAR.h"
#include  "BOOTLOADER_STATES.h"
#include "BOOTLOADER_CFG.h"
#include "BOOTLOADER.h"

/**
 * @brief this enum used to define bootloader indicator states
 *
 */
typedef enum{

	BLD_INDICATOR_START=0,
	BLD_INDICATOR_END,
	BLD_INDICATOR_IDLE

}BLD_INDICATOR_STATE_t;


/**
 * @brief this array used to store default application state and UDS request in e2prom
 *
 */
const UINT8_t __attribute__((section(".eeprom"))) Updates[] = {

		APP_NOT_EXIST,
		UDS_REQ_DATA_TRANSFER,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/**
 * @brief this variable used to express the bootloader current state
 *
 */
static BOOTLOADER_STATE_t Bootloader_State;

static UDS_t UDS_Req_Type;

/**
 * @brief this function used as indication when entering bootloader section
 *
 */
static void
BootLoader_Indicator(void);


void
BOOTLOADER_Main(void){

	BootLoader_Indicator();
	BOOTLOADER_STATE_Init();

	UDS_Req_Type = UDS_Read_Request();

	while (1) {

		Bootloader_State = BOOTLOADER_STATE_Get();

		switch (Bootloader_State) {

		case CHECKING_APPLICATION_EXIST:

			if (APP_EXIST == APP_Read_State()) {

				BOOTLOADER_STATE_Set(CHECKING_REQUEST_EXIST) ;

			} else {

				BOOTLOADER_STATE_Set(CHECKING_TYPE_OF_REQUEST);

			}

			break;
		case CHECKING_REQUEST_EXIST:

			if (UDS_Req_Type != UDS_NO_REQ) {

				BOOTLOADER_STATE_Set(CHECKING_TYPE_OF_REQUEST);

			} else {

				BOOTLOADER_STATE_Set(JMP_TO_APPLICATION_SECTION);

			}

			break;
		case CHECKING_TYPE_OF_REQUEST:

			if (UDS_REQ_DATA_TRANSFER == UDS_Req_Type) {

				BOOTLOADER_STATE_Set(REQUEST_DATA_TRANSFER);

				UDS_Send_Positive_Response();

			}else if(UDS_CFG_FEES == UDS_Req_Type){

				/*get new fees*/
				CFG_PAR_Fees_Update();

				BOOTLOADER_STATE_Set(JMP_TO_APPLICATION_SECTION);

			}else if(UDS_CFG_BALANCE == UDS_Req_Type){

				/*get new balance*/
				CFG_PAR_Balance_Update();

				BOOTLOADER_STATE_Set(JMP_TO_APPLICATION_SECTION);

			}

			break;

		case REQUEST_DATA_TRANSFER:

			if (TRUE == APP_Rx()) {

				BOOTLOADER_STATE_Set(JMP_TO_APPLICATION_SECTION);

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

}

static void
BootLoader_Indicator(void){

	UINT8_t i;

	static BLD_INDICATOR_STATE_t BootLoader_Indicator_Curr_State = BLD_INDICATOR_START;

	/*application pin indicator*/
	DIO_WRITE_PIN_VALUE(APP_PIN_INDICATOR, DIO_PIN_STATE_LOW);
	/*bootloader pin indicator*/
	DIO_WRITE_PIN_VALUE(BLD_PIN_INDICATOR, DIO_PIN_STATE_LOW);

	for(i=0; i<5; ++i){

		DIO_WRITE_PIN_VALUE(BLD_PIN_INDICATOR, 1^DIO_READ_PIN_VALUE(BLD_PIN_INDICATOR));
		_delay_ms(1000);

	}
	switch(BootLoader_Indicator_Curr_State){

	case BLD_INDICATOR_START:

		DIO_WRITE_PIN_VALUE(BLD_PIN_INDICATOR, DIO_PIN_STATE_HIGH);

		BootLoader_Indicator_Curr_State = BLD_INDICATOR_END;

		break;

	case BLD_INDICATOR_END:

			DIO_WRITE_PIN_VALUE(BLD_PIN_INDICATOR, DIO_PIN_STATE_LOW);

			BootLoader_Indicator_Curr_State = BLD_INDICATOR_IDLE;

			break;
	default:

		break;
	}

}
