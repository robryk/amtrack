#ifndef _AMTRACK__PHYSICAL_ROUTINES_GUARD
#define _AMTRACK__PHYSICAL_ROUTINES_GUARD

#include "common.h"

namespace amtrack {
namespace physical {

	/* 
	 * Atomic mass.
	 * 
	 * P.J. Mohr and D.B. Newell,
	 * "Resource Letter FC-1: The Physics of Fundamental Constants,"
	 * Am. J. Phys, 78 (2010) 338
	 */
const double atomic_mass_unit_MeV_c2 = 931.494028;
	/*
	 * Proton mass.
	 * 
	 * http://physics.nist.gov/constants
	 */
const double proton_mass_MeV_c2 = 938.272013;

const double Avogadro_constant = 6.02214179e23;

inline Real beta_from_E(Real E_MeV_u);
inline Real gamma_from_E(Real E_MeV_u);
// TODO(robryk): Description
inline Real mass_correction_terms(Real E_MeV_u);
// TODO(robryk): Description
inline Real max_relativistic_energy_transfer(Real E_MeV_u);

}
}

#endif
