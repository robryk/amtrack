#ifndef _AMTRACK__PHYSICAL_ROUTINES_INL_GUARD
#define _AMTRACK__PHYSICAL_ROUTINES_INL_GUARD

#include "PhysicalRoutines.h"
#include "common.h"

namespace amtrack {
namespace physical {

inline Real beta_from_E(Real E_MeV_u)
{
	assert(E_MeV_u >= 0.0);
	Real beta = sqrt(1.0 - 1.0/square(1.0 + E_MeV_u/atomic_mass_unit_MeV_c2));
	assert(beta < 1.0);
	return beta;
}

inline Real gamma_from_E(Real E_MeV_u)
{
	assert(E_MeV_u >= 0.0);
	return 1.0 / sqrt(1.0 - square(beta_from_E(E_MeV_u)));
}

inline Real mass_correction_terms(Real E_MeV_u)
{
	Real gamma = gamma_from_E(E_MeV_u);
	Real m_MeV_c2 = 1.0079 * proton_mass_MeV_c2; // TODO(original): what does it mean MeV_c2, are units correct ?
    return 1.0 + (2.0 * (electron_mass_MeV_c2 / m_MeV_c2) / gamma) + square(electron_mass_MeV_c2 / m_MeV_c2);
}

inline Real max_relativistic_energy_transfer(Real E_MeV_u)
{
	assert(E_MeV_u >= 0.0);
	Real beta = beta_from_E(E_MeV_u);
	Real mass_correction_terms = mass_correction_terms(E_MeV_u);
	return (2.0 * electron_mass_MeV_c2 * square(beta) / (1.0 - square(beta))) / mass_correction_terms;
}

}
}

#endif
