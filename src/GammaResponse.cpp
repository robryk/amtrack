#include "GammaResponse.h"
#include "common.h"

namespace amtrack {
namespace gamma_response {

AM_GPU_FUNCTION Real test::response(Real d_Gy)
{
	return m_ * d_Gy + c_;
}

Real AM_GPU_FUNCTION general_target::response(Real d_Gy)
{
	// TODO(robryk): gamma function
	//double tmp = gsl_sf_gamma_inc_P(c, d_Gy/D1);
	double tmp = 0.0;
	tmp = pow(tmp, m_) * k;
	return tmp;
}

Real AM_GPU_FUNCTION general_target::lethal_events_response(Real d_Gy)
{
	Real resp = respose(d_Gy);
	assert(resp < 1.0);
	return -1.0 * log(1.0 - resp);
}

AM_GPU_FUNCTION radioluminescence::radioluminescence(Real Smax,
													 Real chi,
													 Real D1) :
	Smax_(Smax), chi_(chi), D1_(D1), c0_(Smax_ / chi_), B_((Smax_ - c0_) / D1_)
{
	// TODO(robryk): Shouldn't Smax be positive, too?
	assert(Smax_ > 0);
	assert(chi_ > 0);
	assert(D1_ > 0);
}

Real AM_GPU_FUNCTION radioluminescence::response(Real d_Gy)
{
	Real d_clipped_Gy = min(d_Gy, D1_);
	return c0_ * d_clipped_Gy + 0.5 * B_ * square(d_clipped_Gy) + Smax_ * max(0, d_Gy - D1_);
}

Real AM_GPU_FUNCTION radioluminescence::lethal_events_response(Real d_Gy)
{
	Real resp = response(d_Gy);
	assert(resp < 1.0); // TODO(robryk): Should this be true in general in response()?
	return -1.0 * log(1.0 - resp);
}

Real AM_GPU_FUNCTION linear_quadratic::lethal_events_response(Real d_Gy)
{
	Real d_clipped_Gy = min(d_Gy, D0_);
	return alpha_ * d_clipped_Gy + beta_ * square(d_clipped_Gy) + cached_lin_coeff_ * max(0, d_Gy - D0_);
}

Real AM_GPU_FUNCTION linear_quadratic::response(Real d_Gy)
{
	Real lethal_resp = lethal_events_response(d_Gy);
	return exp(-lethal_resp);
}

Real AM_GPU_FUNCTION geiss::raw_response(Real d_Gy)
{
	// TODO(original): Use more efficient formula
	return k1_ * (1.0 - exp(-a1_ * d_Gy)) +
		   k2_ * (1.0 - exp(-a2_ * square(d_Gy)));
}

Real AM_GPU_FUNCTION geiss::response(Real d_Gy)
{
	return c_ * raw_response(d_Gy);
}

Real AM_GPU_FUNCTION geiss::lethal_events_response(Real d_Gy)
{
	Real raw_resp = raw_response(d_Gy);
	assert(raw_resp < 1.0); // TODO(robryk): Should this be an assert?
	return -log(1.0 - raw_resp);
}

}
}

	



