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
		Real average_Z_, average_A_;
	public:
		/** Returns material's phase */
		phases::e phase() const { return phase_; }
		/** Returns density [\frac{g}{cm^3}] */
		Real density() const { return density_; }
		/** Returns electron density [\frac{1}{cm^3}] */
		Real electron_density() const;
		/** Returns ionization potential [eV] */
		Real I() const { return I_; }
		/** Returns average atomic number weighted with mass */
		Real average_Z() const { return average_Z_; }
		/** Returns average mass number weighted with mass TODO(robryk): Mass number or atomic mass? */
		Real average_A() const { return average_A_; }
};

}
}
#endif
