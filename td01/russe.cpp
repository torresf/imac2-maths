#include <iostream>

int multRusse(int a, int b) {
	if (a == 0) 
		return 0;
	int signe = 1;
	if (a < 0)
	{
		signe = -signe;
		a = -a;
	}
	if (b < 0)
	{
		signe = -signe;
		b = -b;
	}

	if (a > b)
		std::swap(a, b);
	
	int residu = 0;
	while (a != 1) {
		if (a & 1) {
			residu += b;
		}
		a = a >> 1;
		b = b << 1;
	}
	return signe < 0 ? -(b + residu) : b + residu;
}

int main(int argc, char const *argv[])
{
	std::cout << multRusse(5, -2) << std::endl;
	return 0;
}
