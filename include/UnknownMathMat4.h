#ifndef UNKNOWN_MATH_MAT4_H
#define UNKNOWN_MATH_MAT4_H

#include "UnknownMathConfig.h"

namespace UnknownMath {
	class Vec3;
	class Vec4;
	// column major matrix!
	class Mat4 {
		friend Mat4 operator*(float rhs, const Mat4& lhs);
		friend Vec4 Vec4::operator*(const Mat4& rhs) const;
	private:
		// private helper functions
		static inline std::array<float, 4> matrix_vector4_mul(const Mat4& mat, __m128 vec4) {
			__m128 vx = _mm_shuffle_ps(vec4, vec4, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 vy = _mm_shuffle_ps(vec4, vec4, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 vz = _mm_shuffle_ps(vec4, vec4, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 vw = _mm_shuffle_ps(vec4, vec4, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 vSum = _mm_add_ps(_mm_mul_ps(mat.m_simd4f[0], vx),
				_mm_add_ps(_mm_mul_ps(mat.m_simd4f[1], vy),
					_mm_add_ps(_mm_mul_ps(mat.m_simd4f[2], vz),
						_mm_mul_ps(mat.m_simd4f[3], vw))));
			std::array<float, 4> ret;
			_mm_storeu_ps(ret.data(), vSum);
			return ret;
		}
	public:
		/** 左手坐标系下的投影矩阵
		 * @param fovv(field of view vertical) 垂直方向上的视场角，单位是弧度制 
		 * @param aspect 窗口的宽高比，推荐单位是像素
		 * @param nearZ 近平面空间位置
		 * @param farZ 远平面空间位置 
		 * @return 返回左手坐标系的投影变换矩阵 */
		static inline Mat4 PerspectiveLH(float fovv, float aspect, float nearZ, float farZ);
		/** 求左手坐标系下的摄像机变换矩阵
		 * @param pos 摄像机在空间中的坐标
		 * @param lookAt 摄像机观察方向上的一点
		 * @param up 摄像机大致的上方向(默认与Y轴同向，Y轴作为空间的正上方向)
		 * @return 返回左手坐标系下的摄像机变换矩阵 */
		static inline Mat4 LookAtLH(const Vec3& pos, const Vec3& lookAt, const Vec3& up = { 0, 1, 0 });
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
			memcpy(&m_values[4], col1.data(), sizeof(float) * 4);
			memcpy(&m_values[8], col2.data(), sizeof(float) * 4);
			memcpy(&m_values[12], col3.data(), sizeof(float) * 4);
		}
	public:
		inline Mat4 operator-() const;
		inline Mat4 operator*(float rhs) const;
		inline Mat4 operator+(const Mat4& rhs) const;
		inline Mat4 operator-(const Mat4& rhs) const;
		inline Mat4 operator*(const Mat4& rhs) const;
		inline Mat4 operator/(float rhs) const;
		inline const float operator[](unsigned int index) const { assert(index < 16); return m_values[index]; }
		inline bool operator==(const Mat4& rhs) const { return 0 == memcmp(this, &rhs, sizeof(m_values)); }
		inline bool operator!=(const Mat4& rhs) const { return 0 != memcmp(this, &rhs, sizeof(m_values)); }
		// 警告，除了相同比较以外，其余比较都没有意义
		bool operator>(const Mat4&rhs) const { return false; }
		bool operator>=(const Mat4&rhs) const { return false; }
		bool operator<(const Mat4&rhs) const { return false; }
		bool operator<=(const Mat4&rhs) const { return false; }
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

	Mat4 Mat4::operator*(const Mat4& rhs) const {
		std::array<float, 4>&& col0 = matrix_vector4_mul(*this, rhs.m_simd4f[0]);
		std::array<float, 4>&& col1 = matrix_vector4_mul(*this, rhs.m_simd4f[1]);
		std::array<float, 4>&& col2 = matrix_vector4_mul(*this, rhs.m_simd4f[2]);
		std::array<float, 4>&& col3 = matrix_vector4_mul(*this, rhs.m_simd4f[3]);
		return Mat4(col0, col1, col2, col3);
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
	inline Mat4 Mat4::PerspectiveLH(float fov, float aspect, float nearZ, float farZ) {
		float cot = atanf(fov / 2.0f);
		return Mat4({ cot / aspect, 0, 0, 0 }, // col0
			{ 0, cot, 0, 0 }, // col1
			{ 0, 0, farZ / (farZ - nearZ), 1 }, // col2
			{ 0, 0,  (nearZ * farZ) / (nearZ - farZ), 0 }); // col3
	}
}

#endif // UNKNOWN_MATH_MAT4_H
