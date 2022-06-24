#ifndef URT_H
#define URT_H

#define URT_BAUD_RATE 51


typedef enum{
	URT_IE = 0,
	URT_IC
}URT_INT_t;

typedef enum{
	URT_ENABLE = 0,
	URT_DISABLE
}URT_MODE_t;

extern void
URT_Init(void);

extern UINT8_t
URT_Rx_Char(void);

extern void
URT_Rx(const URT_MODE_t MODE);

extern void
URT_Tx_Char(const UINT8_t CHAR);

extern void
URT_Tx(const URT_MODE_t MODE);

#endif
