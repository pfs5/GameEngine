#pragma once
#include <cmath>

namespace FloatOperations {
	const float PRECISION = 1e-5f;

	inline int compare(const float &_f1, const float &_f2) {
		float difference = fabsf(_f1 - _f2);
		if (difference < PRECISION) {
			return 0;
		}

		return _f1 > _f2 ? 1 : -1;
	}
}