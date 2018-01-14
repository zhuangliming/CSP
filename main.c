/*****************************************************************************
*								CSP
* File:main.c
* Edit:zhuangliming
* Version:V1.0
* Date:2018-01-14
*****************************************************************************/
#include <ucos_ii.h>
#include <ucos_device.h>
#include "board.h"
/* ----------------------- Modbus includes ---------------------------------*/
#include "modbus_app.h"

/*-------------------------------threads------------------------------------*/
OS_STK	STK_Entry[64];
OS_STK	STK_Tracker[128];
OS_STK	STK_Modbus[256];

void ThreadEntry(void *Par);
void ThreadTracker(void *Par);
void ThreadModbus(void *Par);

/**
 * app entry thread
 */
void ThreadEntry(void *Par)
{                            
	OS_ENTER_CRITICAL();
	OSTaskCreate( ThreadTracker,(void*)0,&STK_Tracker[sizeof(STK_Tracker)/sizeof(OS_STK)-1],3);
	OSTaskCreate( ThreadModbus,(void*)0,&STK_Modbus[sizeof(STK_Modbus)/sizeof(OS_STK)-1],4);
	OS_EXIT_CRITICAL();
    while(1)
    {
        OSHwLedON(0);
        OSTimeDly(50);
        OSHwLedOFF(0);
        OSTimeDly(50);
    }
}

void ThreadTracker(void *Par)
{
    while(1)
    {
		OSTimeDly(500);
    }
}

/**
 * Modbus Slave dispatch 50ms
 * Slave address: 1
 * Board: 19200
 */
void ThreadModbus(void *Par)
{
	eMBInit(MB_RTU, 0x01, 0, 19200, MB_PAR_NONE);/*Create a MODBUS RTU device*/
    eMBEnable();
    while(1)
    {
		eMBPoll();
        OSTimeDly(5);
    }
}
/**
 * Main Function 
 */
int main(char arg,char *arv)
{
    BoardInit();
	OSInit();
    OSTaskCreate( ThreadEntry,(void*)0,&STK_Entry[sizeof(STK_Entry)/sizeof(OS_STK)],2);
    OSStart();
    for(;;)
    {
        /**/
    }
    return 0;
}
/*END*/
