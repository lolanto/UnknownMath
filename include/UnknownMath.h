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
			{ x.x(), x.y(), x.z(), x.Dot(pos)}, // col0
			{ y.x(), y.y(), y.z(), y.Dot(pos)}, // col1
			{ z.x(), z.y(), z.z(), z.Dot(pos)}, // col2
			{ 0, 0, 0, 1 }
		);
	}
}

#endif // UNKNOWN_MATH_H
