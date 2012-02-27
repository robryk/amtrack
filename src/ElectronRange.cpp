#include "ElectronRange.h"
#include "common.h"
#include "PhysicalRoutines-inl.h"

namespace amtrack {
namespace electron_range {

AM_GPU_FUNCTION tabata::tabata(Real E_MeV_u, material mat)
	: a1_g_cm2_(k_b1_g_cm2 * mat.average_A() / pow(mat.average_Z(), k_b2)),
	  a2_(k_b3 * mat.average_A()),
	  a3_(k_b4 - k_b5*mat.average_Z()),
	  a4_(k_b6 - k_b7*mat.average_Z()),
	  a5_(k_b8 / pow(mat.average_Z(), k_b9)),
	  beta_(amtrack::physical::beta_from_E(E_MeV_u)),
	  max_electron_range_m_()
{
	assert(beta_ > 0.0);
	assert(beta_ < 1.0);
	double tau = 2.0 * square(beta_) / (1.0 - square(beta_));
	max_electron_range_m_ = (a1_g_cm2_)*(((log(1.0 + a2_ * tau))/a2_) - ((a3_*tau)/(1.0 + a4_*pow(tau,a5_))) );
}


}
}
