#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "avr/boot.h"
#include "util/delay.h"
#include "FLASHER.h"

void
boot_program_page (UINT32_t page, UINT8_t *buf)
{
	UINT16_t i;
	UINT8_t sreg;
	UINT32_t address;
	UINT16_t word ;

	// Disable interrupts.
	GIC;
	sreg = SREG;
	address = page * PAGE_SIZE ;


	boot_page_erase_safe (address);

	for (i=0; i<PAGE_SIZE; i+=2)
	{
		// Set up little Endian word.
		word  = *buf++;
		word += (*buf++) << 8;

		boot_page_fill_safe(address + i, word);
	}

	boot_page_write_safe (address);     // Store buffer in flash page.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable_safe();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
	GIE;
}
