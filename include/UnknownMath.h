#ifndef UNKNOWN_MATH_H
#define UNKNOWN_MATH_H

#include "UnknownMathVec4.h"
#include "UnknownMathVec3.h"
#include "UnknownMathMat4.h"

namespace UnknownMath {
	inline Mat4 Mat4::LookAtLH(const Vec3& pos, const Vec3& lookAt, const Vec3& up) {
		Vec3 z = (lookAt - pos).Normalize();
		Vec3 x = up.Cross(z);
		Vec3 y = z.Cross(x);
		return Mat4(
			{ x.x(), y.x(), z.x(), 0 }, // col0
			{ x.y(), y.y(), z.y(), 0 }, // col1
			{ x.z(), y.z(), z.z(), 0 }, // col2
			{ -x.Dot(pos), -y.Dot(pos), -z.Dot(pos), 1  } // col3
		);
	}

	inline Vec4 Vec4::operator*(const Mat4& rhs) const {
		__m128 res;
		std::array<float, 4> tempRes;
		Vec4 ret;
		for (int i = 0; i < 4; ++i) {
			res = _mm_mul_ps(m_simd4f, rhs.m_simd4f[i]);
			_mm_storeu_ps(tempRes.data(), res);
			ret[i] = tempRes[0] + tempRes[1] + tempRes[2] + tempRes[3];
		}
		return ret;
	}
}

#endif // UNKNOWN_MATH_H
