namespace amtrack {
namespace radial_dose_distribution {

/*
 * Parameters common to all RDDs.
 */
struct common_parameters {
	Real max_electron_range_; // [m]
	Real LET_; // [MeV?cm2?g] TODO(robryk): /cm2/g or /cm2*g?
	Real E_; // [MeV/u]
	particle particle_;
	material material_;
	// er_model?
};

/*
 * Simple step test function
 */
class test {
	public:
		// TODO(robryk): Original code for some reason passes in upper bounds on results.
		Real AM_GPU_FUNCTION r_min_m() const { return 0.0; }
		Real AM_GPU_FUNCTION a0_m() const { return 0.0; }

};

/*
 * Katz's point target RDD
 * Parameters:
 *  r_min_m
 *  d_min_Gy
 */
class katz_point {
	private:
		Real r_min_m_, d_min_Gy_;
	public:
		AM_GPU_FUNCTION katz_point(Real r_min_m, Real d_min_Gy) :
			r_min_m_(r_min_m), d_min_Gy_(d_min_Gy)
		{
		}
		Real AM_GPU_FUNCTION r_min_m() const;
		Real AM_GPU_FUNCTION a0_m() const;
};

/*
 * Geiss' RDD
 * [Geiss et al, 1998]
 * Parameters:
 *  a0_m
 */
class geiss {
	private:
		Real a0_m_;
};

/*
 * Site RDD
 * [Edmund et al., 2007]
 */
class katz_site {
	private:
		Real a0_m_, d_min_Gy_;
};

/*
 * Cucinotta's RDD
 * [Cucinotta et al., 1997]
 */
class cucinotta_point {
	private:
		double r_min_m_, d_min_Gy_;
};

/*
 * Katz Extended Target
 */
class katz_extended_target {
	private:
		Real katz_point_r_min_m_, a0_m_, d_min_Gy_;
};

/*
 * Cucinotta Extneded Target
 */
class cucinotta_extended_target {
	private:
		Real cucinotta_point_r_min_m_, a0_m_, d_min_Gy_;
};

