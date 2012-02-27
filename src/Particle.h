#ifndef _AMTRACK__PARTICLE_GUARD
#define _AMTRACK__PARTICLE_GUARD

namespace amtrack {
namespace particle {

class particle {
	private:
		/** Atomic number */
		int Z_;
		/** Mass number */
		int A_;
		/** Atomic weight [u] */
		Real atomic_weight_;
		/** Density [\frac{g}{cm^2}] */ /* TODO(robryk): Density of what? And what for? */
		Real density_;
		/** I [eV per proton] */
		Real I_;
	public:
		/** Atomic number */
		int Z() const { return Z_; }
		/** Mass number */
		int A() const { return A_; }
		/** Atomic weight [u] */
		Real atomic_weight() const { return atomic_weight_; }
		/** Density [\frac{g}{cm^2}] */
		Real density() const { return density_; }
		/** I [eV per proton] */
		Real I() const { return I_; }
		Real nuclear_spin() const
		{
			if (A() % 2)
				return 0.5; // odd number of nucleons
			if (Z() % 2)
				return 1.0; // even number of nucleons, but odd of protons
			return 0.0; // even number of both protons and neutrons
		}
		particle(int Z, int A, Real atomic_weight, Real density, Real I)
			: Z_(Z), A_(A), atomic_weight_(atomic_weight), density_(density), I_(I)
		{
			assert(Z > 0);
			assert(A > Z);
			assert(atomic_weight > 0.0);
		}
		
};

}
}

#endif
