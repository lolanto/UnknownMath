#ifndef UNKNOWN_MATH_VEC4_H
#define UNKNOWN_MATH_VEC4_H

#include "UnknownMathConfig.h"
namespace UnknownMath {
	class Vec4 {
	public:
		Vec4(float xyzw = 0.0f) {
			int* tempValue = reinterpret_cast<int*>(&xyzw);
			memset(m_values, *tempValue, 4 * sizeof(float));
		}
		Vec4(float x, float y, float z, float w) {
			m_values[0] = x; m_values[1] = y; m_values[2] = z; m_values[3] = w;
		}
		Vec4(const std::array<float, 4>& xyzw) {
			memcpy(m_values, xyzw.data(), 4 * sizeof(float));
		}
		Vec4(const float* data) {
			memcpy(m_values, data, 4 * sizeof(float));
		}
		~Vec4() = default;
	public:
		inline Vec4 operator-() const; // return the negative vector
		inline Vec4 operator+(const Vec4& rhs) const;
		inline Vec4 operator-(const Vec4& rhs) const;
		inline Vec4 operator* (float rhs) const;
		inline Vec4 operator/ (float rhs) const;
		inline float Dot(const Vec4& rhs) const;
		inline float Length() const;
		inline float LengthSquare() const;
		inline Vec4 Normalize() const;
	public:
		inline float x() const { return m_values[0]; }
		inline float y() const { return m_values[1]; }
		inline float z() const { return m_values[2]; }
		inline float w() const { return m_values[3]; }
	public:
		UNKNOWN_MATH_STATIC_ALIGNMENT_NEW
	private:
		union {
			__m128 m_simd4f;
			float m_values[4];
		};
	};
	typedef std::vector<Vec4, AlignedAllocator<Vec4>> Vec4Vector;

	Vec4 Vec4::operator-() const {
		return Vec4(-m_values[0], -m_values[1],
			-m_values[2], -m_values[3]);
	}

	Vec4 Vec4::operator+(const Vec4& rhs) const {
		__m128 v = _mm_add_ps(m_simd4f, rhs.m_simd4f);
		std::array<float, 4> ret;
		_mm_store_ps(ret.data(), v);
		return Vec4(ret);
	}
	 
	Vec4 Vec4::operator-(const Vec4& rhs) const {
		__m128 v = _mm_sub_ps(m_simd4f, rhs.m_simd4f);
		std::array<float, 4> ret;
		_mm_store_ps(ret.data(), v);
		return Vec4(ret);
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

	float Vec4::Dot(const Vec4& rhs) const {
		__m128 v = _mm_mul_ps(m_simd4f, rhs.m_simd4f);
		std::array<float, 4> ret;
		_mm_store_ps(ret.data(), v);
		return ret[0] + ret[1] + ret[2] + ret[3];
	}

	float Vec4::LengthSquare() const {
		return this->Dot(*this);
	}

	float Vec4::Length() const {
		return sqrt(this->LengthSquare());
	}

	Vec4 Vec4::Normalize() const {
		return this->operator/(this->Length());
	}

}

#endif // UNKNOWN_MATH_VEC4_H
