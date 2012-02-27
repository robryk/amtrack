#ifndef _AMTRACK__KATZ_MODEL_GUARD
#define _AMTRACK__KATZ_MODEL_GUARD

#include "common.h"

namespace amtrack {
namespace katz_model {

template<typename rdd_model> AM_GPU_FUNCTION Real inactivation_probability<rdd_model>::operator()(Real r_m)
{
	double d_Gy = rdd_(r_m); // pass in E somehow also -- prepare() seems fine here
	return gamma_.response(d_Gy);
}

}
}

#endif
