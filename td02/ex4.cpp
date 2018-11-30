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

Eigen::MatrixXf multMatrix(const Eigen::MatrixXf &m1, const Eigen::MatrixXf &m2) {
	assert(m1.rows() == m2.cols() && "Error: Wrong size.");
	Eigen::MatrixXf res = Eigen::MatrixXf::Zero(m1.rows(), m2.cols());
	for (unsigned int i = 0; i < res.rows(); ++i)
	{
		for (unsigned int j = 0; j < res.cols(); ++j)
		{
			// - Méthode 1 - 
			res(i, j) = dot(m1.row(i), m2.col(j));
			// - Méthode 2 - 
			/* for (unsigned int k = 0; k < m2.rows(); ++k)
			{
				res(i, j) += m1(i, k) * m2(k, j); 
			} */
		}
	}
	return res;
}

int main()
{
	unsigned int dimension = 1500;

	Eigen::MatrixXf m1 = Eigen::MatrixXf::Random(dimension, dimension);
	Eigen::MatrixXf m2 = Eigen::MatrixXf::Random(dimension, dimension);
	Eigen::MatrixXf res1(dimension, dimension);
	Eigen::MatrixXf res2(dimension, dimension);

	clock_t begin = clock();
	res1 = multMatrix(m1, m2);
	clock_t end = clock();
	double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "temps calcul du produit matriciel IMAC : " << tempsCalc / 4 <<"s " << std::endl;

	begin = clock();
	res2 = m1 * m2;
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "temps calcul du produit matriciel Eigen : " << tempsCalc / 4 <<"s " << std::endl;

	std::cout << "numerical check: " << (res1 - res2).norm() << std::endl;

	return 0;
}