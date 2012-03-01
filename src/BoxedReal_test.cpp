#include "BoxedReal.h"

namespace u = amtrack::units;

int main()
{
	amtrack::beta_real b;
//	b = b + b;
//	b *= b;
	amtrack::length l(10, u::m);
	l = 10 * l;
	l /= 10;
	Real v = l.cm();
	return 0;
}

