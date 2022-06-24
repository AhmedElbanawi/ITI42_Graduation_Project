#ifndef APP_H
#define APP_H

/**
 * @brief this enum used to express the application state in the e2prom
 * 
 */

typedef enum{

	APP_NOT_EXIST=0x70,

	APP_EXIST=0x90

}APP_STATE_t;

/**
 * @brief this function used to get the application current state from e2prom
 * 
 * @return APP_STATE_t 
 */

APP_STATE_t
APP_Read_State(void);

/**
 * @brief  this function used to store the application current state inside e2prom
 * 
 * @param State 
 */

void
APP_Write_State(APP_STATE_t State);

/**
 * @brief this function used to receive the application from server
 * 
 * @return BOOL_t return true if the application received and flashed successfully
 */

BOOL_t
APP_Rx(void);
#endif
