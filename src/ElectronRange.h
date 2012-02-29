#ifndef _AMTRACK__ELECTRON_RANGE_GUARD
#define _AMTRACK__ELECTRON_RANGE_GUARD

#include "common.h"

namespace amtrack {
namespace electron_range {

namespace internal {

Real AM_GPU_FUNCTION butts_katz_range_g_cm2(Real E_MeV_u, material mat);
Real AM_GPU_FUNCTION waligorski_range_g_cm2(Real E_MeV_u, material mat);
Real AM_GPU_FUNCTION edmund_range_g_cm2(Real E_MeV_u, material mat);
Real AM_GPU_FUNCTION geiss_range_g_cm2(Real E_MeV_u, material mat);
Real AM_GPU_FUNCTION scholz_range_g_cm2(Real E_MeV_u, material mat);
Real AM_GPU_FUNCTION tabata_range_g_cm2(Real E_MeV_u, material mat);

template<Real (*Range_g_cm2)(Real, material)> model {
	private:
		Real max_electron_range_m_;
	public:
		AM_GPU_FUNCTION model(Real E_MeV_u, material mat)
			: max_electron_range_m_(Range_g_cm2(E_MeV_u, mat) / mat.density())
		{
		}
};

}

using namespace internal;

class butts_katz : public model<butts_katz_range_g_cm2> {
};

class waligorski : public model<waligorski_range_g_cm2> {
};

class edmund : public model<edmund_range_g_cm2> {
};

class geiss : public model<geiss_range_g_cm2> {
};

class scholz : public model<scholz_range_g_cm2> {
};

class tabata : public model<tabata_range_g_cm2> {
};

template<typename er_model> Real single_impact_fluence_cm2(Real E_MeV_u, material mat)
{
	Real max_electron_range_m = er_model(E_MeV_u, mat).max_electron_range_m();
	return M_1_PI / square(max_electron_range_m * m_to_cm);
}
                 
}
}

#endif
