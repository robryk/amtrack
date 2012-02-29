#include "ElectronRange.h"
#include "common.h"
#include "PhysicalRoutines-inl.h"

namespace amtrack {
namespace electron_range {

namespace internal {

Real AM_GPU_FUNCTION butts_katz_range_g_cm2(Real E_MeV_u, material mat)
{
	Real wmax_MeV = max_relativistic_energy_transfer(E_MeV_u);
	assert(wmax_MeV > 0.0);
	assert(wmax_MeV < 1.0e3);
	return 1.0e-7 * wmax_MeV;
}

Real AM_GPU_FUNCTION waligorski_range_g_cm2(Real E_MeV_u, material mat)
{
	Real wmax_MeV = max_relativistic_energy_transfer(E_MeV_u);
	assert(wmax_MeV > 0.0);
	assert(wmax_MeV < 1.0e3);
	Real alpha = (wmax_MeV < 1.0e-3) ? 1.079 : 1.667;
	return 6.0e-6 * pow(wmax_MeV * 1e-3, alpha);
}

Real AM_GPU_FUNCTION edmund_range_g_cm2(Real E_MeV_u, material mat)
{
	Real wmax_MeV = max_relativistic_energy_transfer(E_MeV_u);
	assert(wmax_MeV > 0.0);
	assert(wmax_MeV < 1.0e3);
	Real alpha = (wmax_MeV < 1.0e-3) ? 1.079 : 1.667;
	return 6.13e-6 * pow(wmax_MeV * 1e-3, alpha);
}

Real AM_GPU_FUNCTION geiss_range_g_cm2(Real E_MeV_u, material mat)
{
	assert(E_MeV_u > 0.0);
	assert(E_MeV_u < 1.0e6);
	return 4.0e-5 * pow(E_MeV_u, 1.5);
}

Real AM_GPU_FUNCTION scholz_range_g_cm2(Real E_MeV_u, material mat)
{
	assert(E_MeV_u > 0.0);
	assert(E_MeV_u < 1.0e6);
	return 5.0e-6 * pow(E_MeV_u, 1.7);
}

Real AM_GPU_FUNCTION tabata_range_g_cm2(Real E_MeV_u, material mat)
{
	const double k_b1_g_cm2 = 0.2335;
	const double k_b2 = 1.209;
	const double k_b3 = 1.78e-4;
	const double k_b4 = 0.9891;
	const double k_b5 = 3.01e-4;
	const double k_b6 = 1.468;
	const double k_b7 = 1.18e-2;
	const double k_b8 = 1.232;
	const double k_b9 = 0.109;

	Real a1_g_cm2 = k_b1_g_cm2 * mat.average_A() / pow(mat.average_Z(), k_b2);
	Real a2 = k_b3 * mat.average_A();
	Real a3 = k_b4 - k_b5*mat.average_Z();
	Real a4 = k_b6 - k_b7*mat.average_Z();
	Real a5 = k_b8 / pow(mat.average_Z(), k_b9);
	Real beta = amtrack::physical::beta_from_E(E_MeV_u);
	Real tau = 2.0 * square(beta_) / (1.0 - square(beta_));
	return (a1_g_cm2_)*(((log(1.0 + a2_ * tau))/a2_) - ((a3_*tau)/(1.0 + a4_*pow(tau,a5_))));
}

}

}
}
