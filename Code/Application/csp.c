#include "csp.h"
struct csp_class CSP;

INT8U CSPInit(struct csp_class *Csp)
{
	Csp->IO.Reg = 0;
	return 0;
}

struct csp_class *GetCSPDevice(void *par)
{
	return &CSP;
}
