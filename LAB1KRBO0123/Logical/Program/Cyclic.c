
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	/* Cyclic #4 and the model use dt = 2 ms.  This produces a repeating
	   4 s test signal: 1 s at zero, 2 s at 60 rpm, 1 s at zero. */
	if (!Enable) {
		counter=0;
		Speed=0.0;

		return;
	}
	counter++;
	if ((counter >= 400) && (counter < 800))
		Speed=60.0;
	else
		Speed=0.0;
	
	if (counter >= 800)
		counter=0;

	if (Enable) {
		fb_controller.e=Speed-fb_motor.w;
		FB_Regulator(&fb_controller);
		fb_motor.u=fb_controller.u;
	}
	else {
		fb_motor.u=0.0;
	}

	FB_Motor(&fb_motor);
	fb_motor_2.u=Speed * fb_motor_2.ke;
	FB_Motor(&fb_motor_2);
}
