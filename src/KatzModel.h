#include "KatzModel.h"
#include "common.h"

namespace amtrack {
namespace katz_model {

template<typaname rdd_model>
class inactivation_probability {
	private:
		rdd_model rdd_;
		gamma_model gamma_;
	public:
		typedef amtrack::gamma_response::general_target gamma_model;
		AM_GPU_FUNCTION Real operator()(Real r_m);
		AM_GPU_FUNCTION inactivation_probability
			(const rdd_model& rdd,
			 const gamma_model& gamma)
			: rdd_(rdd), gamma_(gamma)
		{
		}
};

}
}
