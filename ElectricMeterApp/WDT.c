#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "WDT.h"

void WDT_Enable(void){
	SET_BIT(WDTCR, 3);
}
void WDT_Priode(const WDT_PERIODE_t PERIODE){
	WDTCR &= 0XF8;
	WDTCR |= PERIODE;
}
void WDT_Refresh(void){
	asm volatile("wdr");
}
void WDT_Disable(void){
	SET_BIT(WDTCR, 3);
	SET_BIT(WDTCR, 4);
	CLEAR_BIT(WDTCR, 3);
}
void WDT_Qinit(void)
{
	WDT_Priode(WDT_1000_MS);
	WDT_Enable();
}

