#ifndef __RTC_H_
#define __RTC_H_

#include "board.h"
#include "ucos_ii.h"

typedef struct {
    INT8U hour;
    INT8U min;
    INT8U sec;
    INT16U w_year;
    INT8U w_month;
    INT8U w_date;
    INT8U week;
}_RTC;

void STM32HwRTCInit(void);
#endif