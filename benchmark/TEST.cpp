#include "MatTestSet.hpp"

int main(int ac, char* av[]) {
	testing::InitGoogleTest(&ac, av);
	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}