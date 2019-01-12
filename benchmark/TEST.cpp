#include <gtest/gtest.h>
#include "../include/UnknownMath.h"

using namespace UnknownMath;

// 矩阵相关测试
TEST(Mat4_Test, Mat4xfloat) {
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

int main(int ac, char* av[]) {
	testing::InitGoogleTest(&ac, av);
	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}