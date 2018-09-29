#include <iostream>
#include <iomanip>

int main()
{
	std::cout << "0.1 - 0.1f = " << 0.1 - 0.1f << std::endl;
	std::cout << std::setprecision(20) << "0.1f + 0.2f = " << 0.1f + 0.2f << std::endl;
	std::cout << std::setprecision(20) << "0.1 + 0.2 = " << 0.1 + 0.2 << std::endl;
	return 0;
}