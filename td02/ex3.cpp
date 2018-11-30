#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <cassert>


float dot(const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) {
	assert(v1.size() == v2.size() && "error: not the same size.");
	double sum = 0;
	for (int i = 0; i < v1.size(); ++i)
	{
		sum += v1[i] * v2[i];
	}
	return sum;
}

int main()
{
	unsigned int dimension = 500000;
	Eigen::VectorXf v1 = Eigen::VectorXf::Random(dimension);
	Eigen::VectorXf v2 = Eigen::VectorXf::Random(dimension);
	std::cout << "dot imac: " << dot(v1, v2) << std::endl;
	std::cout << "dot eigen: " << v1.dot(v2) << std::endl;
	std::cout << "numerical check: " << dot(v1, v2) - v1.dot(v2) << std::endl;
	return 0;
}