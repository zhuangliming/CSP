#ifndef __BOARD_H_
#define __BOARD_H_
/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "stm32f10x_conf.h"
#include "ucos_ii.h"
void BoardInit(void);
void OSHwLedON(INT8U id);
void OSHwLedOFF(INT8U id);

#endif
