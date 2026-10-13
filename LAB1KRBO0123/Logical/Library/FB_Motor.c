
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Motor(struct FB_Motor* inst)
{
	REAL e;

	e=inst->u/inst->ke-inst->w;
	inst->integrator.in=e/inst->Tm;
	inst->integrator.dt=inst->dt;
	FB_Integrator(&inst->integrator);
	
	inst->w= inst->integrator.out;
	/* w is measured in rpm, while phi is measured in radians. */
	inst->phi=inst->phi + inst->w * 0.1047197551 * inst->dt;
}
