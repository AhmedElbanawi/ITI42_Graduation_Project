#ifndef CFG_PAR_H
#define CFG_PAR_H

#define FEES_NO_OF_BYTES 1

#define BALANCE_NO_OF_BYTES 8

#define FEES_BASE_ADDRESS 70

#define BALANCE_BASE_ADDRESS 90

extern UINT64_t
Balance_Read(void);

extern UINT64_t
Fees_Read(void);


extern void
Balance_Write(UINT64_t Balance);

extern void
Fees_Write(UINT64_t Fees);

#endif
