#include <ucos_ii.h>
#include <ucos_device.h>
#include "board.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
/*Git HUB*/
/*********threads**********/
OS_STK	STK_Entry[128];
OS_STK	STK_Tracker[128];

void ThreadEntry(void *Par);
void ThreadTracker(void *Par);
/**
 * app entry
 */
void ThreadEntry(void *Par)
{
    BoardInit();
    eMBInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);/*建立一个MODBUS RTU设备*/
    eMBEnable();

    while(1)
    {
        eMBPoll();
        OSTimeDly(50);
    }
}

void ThreadTracker(void *Par)
{
    while(1)
    {
        OSHwLedON(0);
        OSTimeDly(50);
        OSHwLedOFF(0);
        OSTimeDly(50);
    }
}
/**
 * Main Function Port
 */

int main(char arg,char *arv)
{
    BoardInit();
    eMBInit(MB_RTU, 0x01, 0, 9600, MB_PAR_NONE);/*建立一个MODBUS RTU设备*/
    eMBEnable();
    while(1)
    {

        eMBPoll();
    }
    OSInit();
    OSTaskCreate( ThreadEntry,(void*)0,&STK_Entry[128-1],1);
    OSTaskCreate( ThreadTracker,(void*)0,&STK_Tracker[128-1],2);
    OSStart();
    for(;;)
    {
        /**/
    }
    return 0;
}
