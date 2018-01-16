#ifndef __SUN_H_
#define __SUN_H_

#include <stdint.h>
#include "rtc.h"

extern void SunSetLocalGeography( float longitude, float latitude );
extern void SunGetAngle (_RTC time,float *azimuth,float *zenith);

#endif

