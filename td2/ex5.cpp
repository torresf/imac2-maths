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

Eigen::MatrixXf multStrassen(const Eigen::MatrixXf &m1, const Eigen::MatrixXf &m2) {
	if (m1.rows() <= 128)
	{
		return m1 * m2;
	}
	unsigned int rows = m1.rows() / 2;
	unsigned int cols = m1.cols() / 2;

	Eigen::MatrixXf a = m1.topLeftCorner(rows, cols);
	Eigen::MatrixXf b = m1.topRightCorner(rows, cols);
	Eigen::MatrixXf c = m1.bottomLeftCorner(rows, cols);
	Eigen::MatrixXf d = m1.bottomRightCorner(rows, cols);

	Eigen::MatrixXf e = m2.topLeftCorner(rows, cols);
	Eigen::MatrixXf f = m2.topRightCorner(rows, cols);
	Eigen::MatrixXf g = m2.bottomLeftCorner(rows, cols);
	Eigen::MatrixXf h = m2.bottomRightCorner(rows, cols);

	Eigen::MatrixXf P1 = multStrassen(a, f-h);
	Eigen::MatrixXf P2 = multStrassen(a+b, h);
	Eigen::MatrixXf P3 = multStrassen(c+d, e);
	Eigen::MatrixXf P4 = multStrassen(d, g-e);
	Eigen::MatrixXf P5 = multStrassen(a+d, e+h);
	Eigen::MatrixXf P6 = multStrassen(b-d, g+h);
	Eigen::MatrixXf P7 = multStrassen(a-c, e+f);

	Eigen::MatrixXf m3(m1.rows(), m1.cols());
	m3.topLeftCorner(rows, cols) = P5 + P4 - P2 + P6;
	m3.topRightCorner(rows, cols) = P1 + P2;
	m3.bottomLeftCorner(rows, cols) = P3 + P4;
	m3.bottomRightCorner(rows, cols) = P1 + P5 - P3 - P7;

	return m3;
}

int main()
{
	unsigned int dimension = 1024;

	Eigen::MatrixXf m1 = Eigen::MatrixXf::Random(dimension, dimension);
	Eigen::MatrixXf m2 = Eigen::MatrixXf::Random(dimension, dimension);
	Eigen::MatrixXf res1(dimension, dimension);
	Eigen::MatrixXf res2(dimension, dimension);
	Eigen::MatrixXf res3(dimension, dimension);
	Eigen::MatrixXf res4(dimension, dimension);

	clock_t begin = clock();
	res1 = multMatrix(m1, m2);
	clock_t end = clock();
	double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Temps calcul du produit matriciel IMAC : " << tempsCalc <<"s " << std::endl;

	begin = clock();
	res2 = m1 * m2;
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Temps calcul du produit matriciel Eigen : " << tempsCalc <<"s " << std::endl;

	std::cout << "numerical check: " << (res1 - res2).norm() << std::endl;

	Eigen::setNbThreads(4);
	begin = clock();
	res3 = m1 * m2;
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Temps calcul du produit matriciel Eigen multithreadé : " << tempsCalc / 4 <<"s " << std::endl;
	Eigen::setNbThreads(1);

	std::cout << "numerical check: " << (res3 - res2).norm() << std::endl;

	begin = clock();
	res4 = multStrassen(m1, m2);
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Temps calcul du produit matriciel Strassen : " << tempsCalc <<"s " << std::endl;

	std::cout << "numerical check: " << (res4 - res2).norm() << std::endl;

	return 0;
}