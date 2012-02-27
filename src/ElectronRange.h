#ifndef _AMTRACK__ELECTRON_RANGE_GUARD
#define _AMTRACK__ELECTRON_RANGE_GUARD

#include "common.h"

namespace amtrack {
namespace electron_range {

/*
 * class er_model {
 *   public:
 *     max_electron_range()
 *     average(r_min, r_max)
 *     er_model(E_MeV_u, material)
 * };
 */

class tabata {
	private:
		Real a1_g_cm2_, a2_, a3_, a4_, a5_;
		Real beta_;
		Real max_electron_range_m_;
		static const double k_b1_g_cm2 = 0.2335;
		static const double k_b2 = 1.209;
		static const double k_b3 = 1.78e-4;
		static const double k_b4 = 0.9891;
		static const double k_b5 = 3.01e-4;
		static const double k_b6 = 1.468;
		static const double k_b7 = 1.18e-2;
		static const double k_b8 = 1.232;
		static const double k_b9 = 0.109;
	public:
		AM_GPU_FUNCTION tabata(Real E_MeV_u, material mat);
		AM_GPU_FUNCTION Real max_electron_range_m()
		{
			return max_electron_range_m_;
		}
};

class butts_katz {
};

template<typename er_model> Real single_impact_fluence_cm2(Real E_MeV_u, material mat)
{
	Real max_electron_range_m = er_model(E_MeV_u, mat).max_electron_range_m();
	return M_1_PI / square(max_electron_range_m * m_to_cm);
}
                 
}
}

#endif
