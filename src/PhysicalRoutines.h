#ifndef _AMTRACK__PHYSICAL_ROUTINES_GUARD
#define _AMTRACK__PHYSICAL_ROUTINES_GUARD

#include "common.h"

namespace amtrack {
namespace physical {

	/* P.J. Mohr and D.B. Newell,
	 * "Resource Letter FC-1: The Physics of Fundamental Constants,"
	 * Am. J. Phys, 78 (2010) 338
	 */
const double atomic_mass_unit_MeV_c2 = 931.494028;

inline Real beta_from_E(Real E_MeV_u);

}
}

#endif
