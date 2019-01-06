#ifndef UNKNWON_MATH_VEC3_H
#define UNKNOWN_MATH_VEC3_H

#include "UnknownMathConfig.h"
namespace UnknownMath {
	class Vec3 {
	public:
		Vec3(float xyz = 0.0f) : m_values({xyz}) {}
		Vec3(float x, float y, float z) : m_values({ x, y, z }) {}
		Vec3(const std::array<float, 3>& xyz) : m_values(xyz) {}
		~Vec3() = default;
	public:
		inline Vec3 operator-() const; // return the negative vector
		inline Vec3 operator+ (const Vec3& rhs) const;
		inline Vec3 operator- (const Vec3& rhs) const;
		inline Vec3 operator* (float rhs) const;
		inline Vec3 operator/ (float rhs) const;
		inline float Dot(const Vec3& rhs) const;
		inline Vec3 Cross(const Vec3& rhs) const;
		inline float Length() const;
		inline float LengthSquared() const;
		inline Vec3 Normalize() const;
	public:
		inline float x() const { return m_values[0]; }
		inline float y() const { return m_values[1]; }
		inline float z() const { return m_values[2]; }
	private:
		std::array<float, 3> m_values;
	};

	Vec3 Vec3::operator-() const {
		return Vec3(m_values[0], m_values[1], m_values[2]);
	}

	Vec3 Vec3::operator+(const Vec3& rhs) const {
		return Vec3(m_values[0] + rhs.m_values[0],
			m_values[1] + rhs.m_values[1],
			m_values[2] + rhs.m_values[2]);
	}

	Vec3 Vec3::operator-(const Vec3& rhs) const {
		return Vec3(m_values[0] - rhs.m_values[0],
			m_values[1] - rhs.m_values[1],
			m_values[2] - rhs.m_values[2]);
	}

	// for vec3 * float
	Vec3 Vec3::operator*(float rhs) const {
		return Vec3(m_values[0] * rhs,
			m_values[1] * rhs,
			m_values[2] * rhs);
	}

	// global operator- overload for float * vec3
	Vec3 operator*(float lhs, const Vec3& rhs) {
		return rhs * lhs;
	}

	// for Vec3 / float
	Vec3 Vec3::operator/(float rhs) const {
		assert(rhs != 0.0f);
		return Vec3(m_values[0] / rhs,
			m_values[1] / rhs,
			m_values[2] / rhs);
	}

	float Vec3::Dot(const Vec3& rhs) const {
		__m128 l = _mm_loadu_ps(m_values.data());
		__m128 r = _mm_loadu_ps(rhs.m_values.data());
		l = _mm_mul_ps(l, r);
		std::array<float, 4> ret;
		_mm_store_ps(ret.data(), l);
		return ret[0] + ret[1] + ret[2];
	}

	Vec3 Vec3::Cross(const Vec3& rhs) const {
		return Vec3({
			m_values[1] * rhs.m_values[2] - m_values[2] * rhs.m_values[1],
			m_values[2] * rhs.m_values[0] - m_values[0] * rhs.m_values[2],
			m_values[0] * rhs.m_values[1] - m_values[1] * rhs.m_values[0]
			});
	}

	float Vec3::LengthSquared() const {
		return this->Dot(*this);
	}

	float Vec3::Length() const {
		return sqrt(this->LengthSquared());
	}

	Vec3 Vec3::Normalize() const {
		return this->operator/(this->Length());
	}
}

#endif // UNKNOWN_MATH_VEC3_H
