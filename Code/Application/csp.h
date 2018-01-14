#ifndef __CSP_H_
#define __CSP_H_

#include <board.h>
#include <ucos_ii.h>
#include <ucos_device.h>

#ifndef ON
#define ON	1
#endif
#ifndef OFF
#define OFF	0
#endif

typedef union{
	struct{
		INT8U 	Lift:1;
		INT8U 	Right:1;
		INT8U	Up:1;
		INT8U	Down:1;
		INT8U	Auto:1;
		INT8U	Rev:1;
		INT8U	LiftLimit:1;
		INT8U	UpLimit:1;
	};
	INT8U Reg;
}IO_Type;

/*CSP device*/
struct csp_class{
	char *Version;
	IO_Type *IO;  /*Ctrl IO Port*/
};

INT8U CSPInit(struct csp_class *Csp);
/*Get the csp device.point to CSP*/
struct csp_class *GetCSPDevice(void *par);
#endif

/*end*/