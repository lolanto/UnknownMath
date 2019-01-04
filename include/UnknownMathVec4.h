#ifndef UNKNOWN_MATH_VEC4_H
#define UNKNOWN_MATH_VEC4_H

#include "UnknownMathConfig.h"
namespace UnknownMath {
	class Vec4 {
	public:
		Vec4(float xyzw = 0.0f) : m_values({xyzw, xyzw, xyzw, xyzw}) {}
		Vec4(float x, float y, float z, float w) : m_values({x, y, z, w}) {}
		~Vec4() = default;
	public:
		inline Vec4 operator-() const; // return the negative vector
		inline Vec4 operator+(const Vec4& rhs) const;
		inline Vec4 operator-(const Vec4& rhs) const;
		inline Vec4 operator* (float rhs) const;
		inline Vec4 operator/ (float rhs) const;
	public:
		inline float x() const { return m_values[0]; }
		inline float y() const { return m_values[1]; }
		inline float z() const { return m_values[2]; }
		inline float w() const { return m_values[3]; }
	private:
		std::array<float, 4> m_values;
	};

	Vec4 Vec4::operator-() const {
		return Vec4(-m_values[0], -m_values[1],
			-m_values[2], -m_values[3]);
	}

	Vec4 Vec4::operator+(const Vec4& rhs) const {
		return Vec4(m_values[0] + rhs.m_values[0],
			m_values[1] + rhs.m_values[1],
			m_values[2] + rhs.m_values[2],
			m_values[3] + rhs.m_values[3]);
	}
	 
	Vec4 Vec4::operator-(const Vec4& rhs) const {
		return Vec4(m_values[0] - rhs.m_values[0],
			m_values[1] - rhs.m_values[1],
			m_values[2] - rhs.m_values[2],
			m_values[3] - rhs.m_values[3]);
	}

	// for vec4 * float
	Vec4 Vec4::operator*(float rhs) const {
		return Vec4(m_values[0] * rhs,
			m_values[1] * rhs,
			m_values[2] * rhs,
			m_values[3] * rhs);
	}

	// global operator overload for float * vec4
	Vec4 operator*(float lhs, const Vec4& rhs) {
		return rhs * lhs;
	}

	// for Vec4 / float
	Vec4 Vec4::operator/(float rhs) const {
		assert(rhs != 0.0f);
		return Vec4(m_values[0] / rhs,
			m_values[1] / rhs,
			m_values[2] / rhs,
			m_values[3] / rhs);
	}
}

#endif // UNKNOWN_MATH_VEC4_H
