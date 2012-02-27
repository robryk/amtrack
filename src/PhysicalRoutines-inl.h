#ifndef _AMTRACK__PHYSICAL_ROUTINES_INL_GUARD
#define _AMTRACK__PHYSICAL_ROUTINES_INL_GUARD

#include "PhysicalRoutines.h"
#include "common.h"

namespace amtrack {
namespace physical {

inline Real beta_from_E(Real E_MeV_u)
{
	assert(E_MeV_u >= 0.0);
	return sqrt(1.0 - 1.0/square(1.0 + E_MeV_u/atomic_mass_unit_MeV_c2));
}

}
}

#endif
