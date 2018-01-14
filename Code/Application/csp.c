/********************************************************************************
 *					csp.c
 *******************************************************************************/
#include "csp.h"
#include "modbus_app.h"
struct csp_class CSP;

/**
 * Init CSP 
 */
INT8U CSPInit(struct csp_class *Csp)
{
	Csp->IO = (IO_Type *)ucRegCoilsBuf;
	Csp->IO->Reg = 0x00;
	return 0;
}

struct csp_class *GetCSPDevice(void *par)
{
	return &CSP;
}
