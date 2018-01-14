#ifndef __MODBUS_APP_H_
#define __MODBUS_APP_H_

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 	1
#define REG_INPUT_NREGS 	64
#define REG_HOLDING_START 	1
#define REG_HOLDING_NREGS 	64

/* ----------------------- Defines ------------------------------------------*/
#define REG_COILS_START     (1000-1)
#define REG_COILS_SIZE      128
extern UCHAR	ucRegCoilsBuf[REG_COILS_SIZE / 8];
extern USHORT   usRegInputBuf[REG_INPUT_NREGS];
extern USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

#endif