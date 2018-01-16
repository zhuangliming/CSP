/*---------------------------------------------------------------------------------------------
 *                                          csp.c
 --------------------------------------------------------------------------------------------*/
#include "csp.h"
#include "modbus_app.h"
struct csp_class CSP;

/**
* Init CSP
* -----------------------------------------MODBUS---------------------------------------------
* Tackstation			   0x30001
* LocalGeography           0x40001
* IO                       0x10001
* --------------------------------------------------------------------------------------------
*/
INT8U CSPInit(struct csp_class *Csp)
{
    Csp->IO = (IO_Type *)ucRegCoilsBuf;
    Csp->IO->Reg = 0x00;
    Csp->LocalGeography = (struct Geography *)usRegHoldingBuf;
	Csp->track = (struct Station *)usRegInputBuf;
    SunSetLocalGeography(12.12,32.1);/*set local geography*/
    return 0;
}

/**
* Get a csp device
* return:   point to csp
*/
struct csp_class *GetCSPDevice(void *par)
{
    return &CSP;
}

/**END*<*/