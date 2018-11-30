#include <iostream>
#include <cstdlib>

void printUchar(const unsigned char x)
{
	int n = (int) x;
	std::cout << n << " : ";
	for (int i = 7; i >=0 ; --i)
	{
		std::cout << ((n >> i) & 1);
	}
	std::cout << std::endl;
}


int main(int argc, char **argv)
{
	if(argc != 2){
		std::cerr << "usage: " << argv[0] << " nb" << std::endl;
		return 0;
	}
	printUchar(atoi(argv[1]));

	return 1;
}
