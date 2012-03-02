#ifndef _AMTRACK__BOXED_REAL_GUARD
#define _AMTRACK__BOXED_REAL_GUARD

#include "common.h"

/*
 * If you get errors about undefined allow_something in this file while trying
 * to perform arithmetic on boxed reals, the boxed real in question does not
 * allow the operation you are trying to perform.
 * 
 * If you believe it should be otherwise, add the missing allow_something type
 * to the _t structure corresponding to the boxed real. For instance, if you
 * believed beta values should allow addition, you should add
 *   struct allow_sum_diff { };
 * to struct beta_t defined below.
 */

namespace amtrack {

namespace boxed_reals {

/*
 * Boxed real internals.
 */
class boxed_real_base {
	protected:
		Real v_;
		boxed_real_base(Real v) : v_(v) { }
		boxed_real_base() { }
};

/*
 * Main boxed real type.
 */
template<typename T> class boxed_real : public T::base_type {
	public:
		typedef typename T::base_type base_type;

		Real v() const { return this->v_; }
		boxed_real() : base_type() { }
		template<typename A1> explicit boxed_real(A1 v) : base_type(v) { }
		template<typename A1, typename A2> explicit boxed_real(A1 u, A2 v) : base_type(u, v) { }
		template<typename U> boxed_real& operator+=(U a) { return *this = *this + a; }
		template<typename U> boxed_real& operator-=(U a) { return *this = *this - a; }
		template<typename U> boxed_real& operator*=(U a) { return *this = *this * a; }
		template<typename U> boxed_real& operator/=(U a) { return *this = *this / a; }
};

/*
 * Binary operators on boxed reals.
 */
template<typename T> boxed_real<T> operator+(boxed_real<T> a, boxed_real<T> b)
{
	typename T::allow_sum_diff dummy;
	return boxed_real<T>(a.v() + b.v());
}

template<typename T> boxed_real<T> operator-(boxed_real<T> a, boxed_real<T> b)
{
	typename T::allow_sum_diff dummy;
	return boxed_real<T>(a.v() - b.v());
}

template<typename T> boxed_real<T> operator*(Real a, boxed_real<T> b)
{
	typename T::allow_mul_div_scalar dummy;
	return boxed_real<T>(a * b.v());
}

template<typename T> boxed_real<T> operator*(boxed_real<T> a, Real b)
{
	return b * a;
}

template<typename T> boxed_real<T> operator/(boxed_real<T> a, Real b)
{
	typename T::allow_mul_div_scalar dummy;
	return boxed_real<T>(a.v() / b);
}

/*
 * Structure that all tag structures should derive from
 */
struct tag {
	typedef boxed_real_base base_type;
};

}

using namespace boxed_reals;

/*
 * Boxed real types
 */

/* beta */
namespace boxed_reals {
struct beta_t : public tag {
};
}

typedef boxed_real<beta_t> beta_real;

/* length */
namespace units {
	struct m_tag {};
	m_tag m;
	struct cm_tag {};
	cm_tag cm;
}

namespace boxed_reals {
struct length_t : public tag {
	class base_type : public boxed_real_base {
		public:
			Real m() const { return 0.01*v_; }
			Real cm() const { return v_; }
			base_type(Real v, units::m_tag) : boxed_real_base(0.01*v) { }
			base_type(Real v, units::cm_tag) : boxed_real_base(v) { }
			// TODO(robryk): This is necessary for arith. Find a way to hide it.
			base_type(Real v) : boxed_real_base(v) { }
	};

	struct allow_sum_diff { };
	struct allow_mul_div_scalar { };
};
}

typedef boxed_real<length_t> length;
		

}

#endif
