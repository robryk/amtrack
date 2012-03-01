#ifndef _AMTRACK__MATERIAL_GUARD
#define _AMTRACK__MATERIAL_GUARD

#include "common.h"
#include <string>

namespace amtrack {
namespace material {

class phases {
	public:
		enum e {
			undefined,
			condensed,
			gaseous
		};
};

class material_data {
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
		material_data(phases::e phase, Real density, Real I, Real average_Z,
		         Real average_A)
			: phase_(phase), density_(density), I_(I), average_Z_(average_Z),
			  average_A_(average_A)
		{
			assert(phase_ == phases::undefined ||
			       phase_ == phases::condensed ||
			       phase_ == phases::gaseous);
			assert(density_ > 0.0);
			// TODO(robryk): Asserts on I
			assert(average_Z_ > 0.0);
			assert(average_A_ > 0.0);
		}
};

class material {
	private:
		material_data material_data_;
		std::string name;
	public:
		operator const material_data&() const { return material_data_; }
};

}
}
#endif
