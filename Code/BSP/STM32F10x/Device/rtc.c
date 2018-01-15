#include "rtc.h"

const INT8U  TableWeek[12]= {0,3,3,6,1,4,6,2,5,0,3,5};
const INT8U  TableMonth[12]= {31,28,31,30,31,30,31,31,30,31,30,31};

void STM32HwRTCInit(void)
{
    INT16U INT16U_WaitForOscSource;
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        PWR_BackupAccessCmd(ENABLE);
        BKP_DeInit();
        RCC_LSEConfig(RCC_LSE_ON);
        for(INT16U_WaitForOscSource=0; INT16U_WaitForOscSource<5000; INT16U_WaitForOscSource++);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
        RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
        RTC_WaitForLastTask();
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        for(INT16U_WaitForOscSource=0; INT16U_WaitForOscSource<5000; INT16U_WaitForOscSource++);
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
        }
        RCC_ClearFlag();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
    }
    return;

}

static INT8U ISLeapYear(INT16U year)
{
    if(year%4==0)
    {
        if(year%100==0)
        {
            if(year%400==0)
                return 1;
            else
                return 0;
        }
        else return 1;

    }
    else
        return 0;
}


void STM32HwRTCSetTime(INT16U year,INT8U smon,INT8U sday,INT8U hour,INT8U min,INT8U sec)
{
    INT16U i;
    INT32U seccount=0;

    for(i=1970; i<year; i++)
    {
        if(ISLeapYear(i))
            seccount+=31622400;
        else
            seccount+=31536000;
    }
    smon-=1;
    for(i=0; i<smon; i++)
    {
        seccount+=(INT32U)TableMonth[i]*86400;
        if(ISLeapYear(year)&&i==1)
            seccount+=86400;
    }
    seccount+=(INT32U)(sday-1)*86400;
    seccount+=(INT32U)hour*3600;
    seccount+=(INT32U)min*60;
    seccount+=sec;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_EnterConfigMode();
    RTC_SetCounter(seccount);
    RTC_ExitConfigMode();
    RTC_WaitForLastTask();
}


static INT8U RTC_GET_Week(INT16U year,INT8U month,INT8U day)
{
    INT16U temp2;
    INT8U yearH,yearL;
    yearH=year/100;
    yearL=year%100;

    if(yearH>19) yearL+=100;
    temp2=yearL+yearL/4;
    temp2=temp2%7;
    temp2=temp2+day+TableWeek[month-1];
    if(yearL%4==0&&month<3)temp2--;
    return(temp2%7);
}

void STM32HwGetTime(_RTC *timer)
{

    static INT16U daycnt = 0;
    INT32U timecount = 0;
    INT32U temp = 0;
    INT16U temp1 = 0;
    timecount = RTC_GetCounter();
    temp = timecount/86400;
    if( daycnt != temp )
    {
        daycnt = temp;
        temp1 = 1970;
        while( temp >= 365 )
        {
            if(ISLeapYear(temp1))
            {
                if(temp>=366)
                {
                    temp-=366;
                }
                else
                {
                    temp1++;
                    break;
                }
            }
            else temp-=365;
            temp1++;
        }

        timer->w_year=temp1;
        temp1=0;
        while(temp>=28)
        {
            if(ISLeapYear(timer->w_year)&&temp1==1)
            {
                if(temp>=29)
                    temp-=29;
                else
                    break;
            }
            else
            {
                if(temp>=TableMonth[temp1])
                    temp-=TableMonth[temp1];
                else
                    break;
            }
            temp1++;
        }
        timer->w_month=temp1+1;
        timer->w_date=temp+1;
    }

    temp=timecount%86400;
    timer->hour=temp/3600;
    timer->min=(temp%3600)/60;
    timer->sec=(temp%3600)%60;
    timer->week=RTC_GET_Week(timer->w_year,timer->w_month,timer->w_date);
}

