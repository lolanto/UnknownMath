#include <iostream>
#include "../include/UnknownMath.h"
using namespace UnknownMath;

int main() {
	Mat4 pp = Mat4::LookAtLH({ 0, 0, 2 }, { 0, 0, 0 });
	const float* data = pp.Data();
	for (int i = 0; i < 16; ++i, ++data) {
		std::cout << (*data) << '\n';
	}
	system("pause");
	return 0;
}
