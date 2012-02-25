#ifndef _AMTRACK__GAMMA_RESPONSE_GUARD
#define _AMTRACK__GAMMA_RESPONSE_GUARD

#include "common.h"

namespace amtrack {
namespace gamma_response {

/*
 * Test model, response m*x + c
 */
class test {
	private:
		Real m_, c_;
	public:
		AM_GPU_FUNCTION test(Real m, Real c) : m_(m), c_(c) {}
		Real AM_GPU_FUNCTION response(Real d_Gy);
};

/*
 * General multi-hit, multi-target model
 * TODO(robryk): When a way to pass arrays to GPU is settled
 */

/*
 * Radioluminescence accumulated counts model
 * Parameters:
 *  Smax - maximum RATE signal
 *  chi  - dynamics, ration between Smax and start count rate c0
 *  D1   - characteristic dose at which rate signal reaches saturation
 * Transformed parameters:
 *  c0 - RATE signal at D=0
 *  B  - linear slope of RATE signal below D1
 *  D1 - see above
 */
class radioluminescence {
	private:
		Real Smax_, chi_, D1_;
		Real c0_, B_;
	public:
		AM_GPU_FUNCTION radioluminescence(Real Smax, Real chi, Real D1);
		Real AM_GPU_FUNCTION response(Real d_Gy);
		Real AM_GPU_FUNCTION lethal_events_response(Real d_Gy);
};

/*
 * Linear-quadratic model
 * Parameters:
 *  alpha - first parameter in LQ equation
 *  beta  - second parameter in LQ equation
 *  D0    - third parameter - transition dose
 */
class linear_quadratic {
	private:
		Real alpha_, beta_, D0_;
	public:
		AM_GPU_FUNCTION linear_quadratic(Real alpha, Real beta, Real D0) :
			alpha_(alpha), beta_(beta), D0_(D0)
		{
			assert(alpha > 0.0);
			assert(beta >= 0.0);
			assert(D0 > 0.0);
		}
		Real AM_GPU_FUNCTION response(Real d_Gy);
		Real AM_GPU_FUNCTION lethal_events_response(Real d_Gy);
};

/*
 * Multi-component model as given in Geiss, 1997 (PhD thesis)
 * Parameters:
 *  c  - constant, arbitrary for efficiency prediction
 *  k1 - contribution from linear component (0.8 for Geiss, 1997)
 *  a1 - dose prefactor for linear component (3e-4 for Geiss, 1997)
 *  k2 - contribution from quadratic component (0.2 for Geiss, 1997)
 *  a2 - dose prefactor for quadratic component (1e-6 for Geiss, 1997)
 */
class geiss {
	private:
		Real c_, k1_, a1_, k2_, a2_;
		Real AM_GPU_FUNCTION raw_response(Real d_Gy);
	public:
		AM_GPU_FUNCTION geiss(Real c, Real k1, Real a1, Real k2, Real a2) :
			c_(c), k1_(k1), a1_(a1), k2_(k2), a2_(a2)
		{
		}
		Real AM_GPU_FUNCTION response(Real d_Gy);
		Real AM_GPU_FUNCTION lethal_events_response(Real d_Gy);
};

		

}
}

#endif
