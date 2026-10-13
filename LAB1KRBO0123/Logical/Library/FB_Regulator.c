#include <bur/plctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include "Library.h"
#ifdef __cplusplus
};
#endif

void FB_Regulator(struct FB_Regulator* inst)
{
	REAL p_term;
	REAL sum_before_sat;
	REAL u_sat;

	/* Пропорциональная составляющая */
	p_term=inst->e * inst->k_p;

	/* Ограничитель после П-звена */
	if (p_term > inst->max_abs_value)
		p_term=inst->max_abs_value;
	else if (p_term < -inst->max_abs_value)
		p_term=-inst->max_abs_value;

	/* Интегратор с предыдущей поправкой противонакопления */
	inst->integrator.in=
		inst->e * inst->k_i + inst->iyOld;

	inst->integrator.dt=inst->dt;
	FB_Integrator(&inst->integrator);

	/* Неограниченный выход ПИ-регулятора */
	sum_before_sat=p_term + inst->integrator.out;

	/* Ограничитель выходного напряжения */
	if (sum_before_sat > inst->max_abs_value)
		u_sat=inst->max_abs_value;
	else if (sum_before_sat < -inst->max_abs_value)
		u_sat=-inst->max_abs_value;
	else
		u_sat=sum_before_sat;

	/* Сохраняем именно поправку противонакопления */
	inst->iyOld=u_sat-sum_before_sat;
	inst->u=u_sat;
}