#ifndef __RTC_H_
#define __RTC_H_

#include "board.h"
#include "ucos_ii.h"

typedef struct
{
    INT16U w_year;
    INT16U w_month;
    INT16U w_date;
    INT16U week;
    INT16U hour;
    INT16U min;
    INT16U sec;
} _RTC;

void STM32HwRTCInit(void);
void STM32HwGetTime(_RTC *timer);
#endif