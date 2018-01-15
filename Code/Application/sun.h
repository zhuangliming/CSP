#ifndef __SUN_H_
#define __SUN_H_

#include <stdint.h>

#define SunSetLocalGeography    set_local_geography
#define SunGetAngle             get_sun_angle
typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint16_t w_year;
    uint8_t w_month;
    uint8_t w_date;
    uint8_t week;
} tm;

extern void set_local_geography( float longitude, float latitude );
extern void get_sun_angle(tm time,float *azimuth,float *zenith);

#endif

