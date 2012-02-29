#include "Material.h"
#include "PhysicalRoutines.h"

#include "common.h"

namespace amtrack {
namespace material {

Real material::electron_density() const
{
	// TODO(original): ``Again, number of nucleon rather than atomic mass is used''
	Real molar_mass_g_mol = average_A();
	Real number_of_atoms_per_g = physical::Avogadro_constant / molar_mass_g_mol;
	Real number_of_electrons_per_g = number_of_atoms_per_g * average_Z();
	return number_of_electrons_per_g * density_g_cm3;
}


}
}

