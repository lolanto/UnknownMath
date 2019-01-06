#include <iostream>
#include "../include/UnknownMath.h"
using namespace UnknownMath;

int main() {
	Vec4Vector v(2);
	v[0] = Vec4({ 0, 1, 2, 3 });
	v[1] = Vec4({ 2, 3, 4, 5 });
	std::cout << (v[0] + v[1]).x() << std::endl;
	system("pause");
	return 0;
}
