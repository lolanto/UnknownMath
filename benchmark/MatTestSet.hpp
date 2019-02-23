#ifndef MAT_TEST_SET_HPP
#define MAT_TEST_SET_HPP
#include <gtest/gtest.h>
#include "../include/UnknownMath.h"

using namespace UnknownMath;
#define TEST_CASE_NAME Matrix4_Test
// 矩阵相关测试
TEST(TEST_CASE_NAME, Mat4xfloat) {
	Mat4 a(
		{ 1, 2, 3, 4 },
		{ 2, 3, 4, 5 },
		{ 3, 4, 5, 6 },
		{ 4, 5, 6, 7 });
	Mat4 b(
		{ 2, 4, 6, 8 },
		{ 4, 6, 8, 10 },
		{ 6, 8, 10, 12 },
		{ 8, 10, 12, 14 }
	);
	EXPECT_EQ(b, a * 2.0f);
}

TEST(TEST_CASE_NAME, Mat4xMat4) {
	Mat4 a(
		{ 1, 2, 3, 4 },
		{ 2, 3, 4, 5 },
		{ 3, 4, 5, 6 },
		{ 4, 5, 6, 7 }
	);
	Mat4 b(
		{ 1, 0, 0, 0 },
		{ 0, 2, 0, 0 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 4 }
	);
	Mat4 res(
		{ 1, 2, 3, 4 },
		{ 4, 6, 8 ,10 },
		{ 9, 12, 15, 18 },
		{ 16, 20, 24, 28 }
	);
	EXPECT_EQ(res, a * b);
}

TEST(TEST_CASE_NAME, Mat4_LookAtMatLH) {
	Mat4 lookAt = Mat4::LookAtLH({ 0, 0, 5 }, { 1, 0, 0 });
	Vec4 vPos(0, 0, 0, 1);
	Vec4 cvPos = vPos * lookAt;
	Vec4 ref(0.98f, 0, 4.9f, 1);
	EXPECT_FLOAT_EQ(ref.x(), cvPos.x());
	EXPECT_FLOAT_EQ(ref.z(), cvPos.z());
}
#endif // MAT_TEST_SET_HPP
