#ifndef _AMTRACK__MATERIAL_GUARD
#define _AMTRACK__MATERIAL_GUARD

#include "common.h"

namespace amtrack {
namespace material {

class phases {
	public:
		enum e {
			phase_undefined,
			phase_consensed,
			phase_gaseous
		};
};

class material {
	private:
		/** Phase */ /* TODO(robryk): Do we need phase_undefined at all? */
		phases::e phase_;
		/** Density [\frac{g}{cm^3}] */
		Real density_;
		/** I [eV] */
		Real I_;
	public:
		/** Returns material's phase */
		phases::e phase() const { return phase_; }
		/** Returns density [\frac{g}{cm^3}] */
		Real density() const { return density_; }
		/** Returns ionization potential [eV] */
		Real I() const { return I_; }
};

}
}
#endif
