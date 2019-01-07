#ifndef UNKNOWN_MATH_MAT4_H
#define UNKNOWN_MATH_MAT4_H

#include "UnknownMathConfig.h"

namespace UnknownMath {
	// column major matrix!
	class Mat4 {
		friend Mat4 operator*(float rhs, const Mat4& lhs);
	public:
		static Mat4 Perspective(float fov, float aspect, float nearZ, float farZ, float LRH = 1.0f);
	public:
		Mat4(float value = 0.0f) {
			int* tempValue = reinterpret_cast<int*>(&value);
			memset(m_values, *tempValue, 16 * sizeof(float));
		}
		Mat4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: m00(m00), m01(m01), m02(m02), m03(m03),
			m10(m10), m11(m11), m12(m12), m13(m13),
			m20(m20), m21(m21), m22(m22), m23(m23),
			m30(m30), m31(m31), m32(m32), m33(m33) {}
		Mat4(const std::array<float, 4>& col0,
			const std::array<float, 4>& col1,
			const std::array<float, 4>& col2,
			const std::array<float, 4>& col3) {
			memcpy(&m_values[0], col0.data(), sizeof(float) * 4);
			memcpy(&m_values[1], col1.data(), sizeof(float) * 4);
			memcpy(&m_values[2], col2.data(), sizeof(float) * 4);
			memcpy(&m_values[3], col3.data(), sizeof(float) * 4);
		}
	public:
		Mat4 operator-() const;
		Mat4 operator*(float rhs) const;
		Mat4 operator+(const Mat4& rhs) const;
		Mat4 operator-(const Mat4& rhs) const;
		Mat4 operator/(float rhs) const;
		float operator[](unsigned int index) const { assert(index < 16); return m_values[index]; }
	public:
		float Value(unsigned int row, unsigned int column) {
			assert(row < 4 && column < 4);
			return m_values[column + row * 4];
		}
		const float* Data() const { return m_values; }
	public:
		UNKNOWN_MATH_STATIC_ALIGNMENT_NEW
	private:
		union {
			__m128 m_simd4f[4];
			float m_values[16];
			struct {
				float m00, m10, m20, m30;
				float m01, m11, m21, m31;
				float m02, m12, m22, m32;
				float m03, m13, m23, m33;
			};
		};
	};

	Mat4 Mat4::operator-() const {
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret.m_values[i] = -ret.m_values[i]);
		return ret;
	}

	Mat4 Mat4::operator+(const Mat4& rhs) const {
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret.m_values[i] = m_values[i] + rhs.m_values[i]);
		return ret;
	}

	Mat4 Mat4::operator-(const Mat4& rhs) const {
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret.m_values[i] = m_values[i] - rhs.m_values[i]);
		return ret;
	}

	Mat4 Mat4::operator*(float rhs) const {
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret.m_values[i] = m_values[i] * rhs);
		return ret;
	}

	Mat4 Mat4::operator/(float rhs) const {
		assert(rhs != 0.0f);
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret.m_values[i] = m_values[i] / rhs);
		return ret;
	}

	inline Mat4 operator*(float lhs, const Mat4& rhs) {
		Mat4 ret;
		UNKNOWN_MATH_OPERATION_LOOP(16, ret = rhs.m_values[i] * lhs);
		return ret;
	}

	// Static Function
	inline Mat4 Mat4::Perspective(float fov, float aspect, float nearZ, float farZ, float LRH) {

	}
}

#endif // UNKNOWN_MATH_MAT4_H
