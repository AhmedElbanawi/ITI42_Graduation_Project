#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "URT.h"
#include "BOOTLOADER.h"

int
main(void){

	GIC;
	DIO_INIT();
	URT_Init();

	BOOTLOADER_Main();

	return 0;
}
