#ifndef UNKNOWN_MATH_MAT4_H
#define UNKNOWN_MATH_MAT4_H

#include "UnknownMathConfig.h"

#define UNKNOWN_MATH_GET_MATRIX_VALUE(name, id) inline float name() const { \
return m_values[id]; \
} \

namespace UnknownMath {
	class Mat4 {
	public:
		Mat4(float value = 0.0f) :
			m_values({ value }) {}
		Mat4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: m_values({ m00, m01, m02, m03, m10, m11, m12, m13,
				m20, m21, m22, m23, m30, m31, m32, m33 }) {}
	public:
		Mat4 operator-() const;
		Mat4 operator*(float rhs) const;
		Mat4 operator+(const Mat4& rhs) const;
		Mat4 operator-(const Mat4& rhs) const;
		Mat4 operator/(float rhs) const;
	public:
		UNKNOWN_MATH_GET_MATRIX_VALUE(m00, 0);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m01, 1);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m02, 2);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m03, 3);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m10, 4);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m11, 5);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m12, 6);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m13, 7);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m20, 8);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m21, 9);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m22, 10);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m23, 11);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m30, 12);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m31, 13);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m32, 14);
		UNKNOWN_MATH_GET_MATRIX_VALUE(m33, 15);
	private:
		std::array<float, 16> m_values;
	};

	Mat4 Mat4::operator-() const {
		return Mat4(-m_values[0], -m_values[1], -m_values[2], -m_values[3],
			-m_values[4], -m_values[5], -m_values[6], -m_values[7],
			-m_values[8], -m_values[9], -m_values[10], -m_values[11],
			-m_values[12], -m_values[13], -m_values[14], -m_values[15]);
	}

	Mat4 Mat4::operator+(const Mat4& rhs) const {
		return Mat4(m_values[0] + rhs.m_values[0], m_values[1] + rhs.m_values[1], m_values[2] + rhs.m_values[2], m_values[3] + rhs.m_values[3],
			m_values[4] + rhs.m_values[4], m_values[5] + rhs.m_values[5], m_values[6] + rhs.m_values[6], m_values[7] + rhs.m_values[7],
			m_values[8] + rhs.m_values[8], m_values[9] + rhs.m_values[9], m_values[10] + rhs.m_values[10], m_values[11] + rhs.m_values[11],
			m_values[12] + rhs.m_values[12], m_values[13] + rhs.m_values[13], m_values[14] + rhs.m_values[14], m_values[15] + rhs.m_values[15]);
	}

	Mat4 Mat4::operator-(const Mat4& rhs) const {
		return Mat4(m_values[0] - rhs.m_values[0], m_values[1] - rhs.m_values[1], m_values[2] - rhs.m_values[2], m_values[3] - rhs.m_values[3],
			m_values[4] - rhs.m_values[4], m_values[5] - rhs.m_values[5], m_values[6] - rhs.m_values[6], m_values[7] - rhs.m_values[7],
			m_values[8] - rhs.m_values[8], m_values[9] - rhs.m_values[9], m_values[10] - rhs.m_values[10], m_values[11] - rhs.m_values[11],
			m_values[12] - rhs.m_values[12], m_values[13] - rhs.m_values[13], m_values[14] - rhs.m_values[14], m_values[15] - rhs.m_values[15]);
	}

	Mat4 Mat4::operator*(float rhs) const {
		return Mat4(m_values[0] * rhs, m_values[1] * rhs, m_values[2] * rhs, m_values[3] * rhs,
			m_values[4] * rhs, m_values[5] * rhs, m_values[6] * rhs, m_values[7] * rhs,
			m_values[8] * rhs, m_values[9] * rhs, m_values[10] * rhs, m_values[11] * rhs,
			m_values[12] * rhs, m_values[13] * rhs, m_values[14] * rhs, m_values[15] * rhs);
	}
}

#endif // UNKNOWN_MATH_MAT4_H
