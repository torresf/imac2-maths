#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>

double evalPolynomial(const Eigen::VectorXd &p, const double &x) {
	double res = 0;
	double myX = 1;
	for (int i = 0; i < p.size(); ++i) {
		res += p[i] * myX;
		myX*=x;
	}
	return res;
}

Eigen::VectorXd polynomialFromRoots(const Eigen::VectorXd &roots) {
	Eigen::VectorXd p = Eigen::VectorXd::Ones(roots.size() + 1);
	// For the first root
	p(0) = -roots(0);
	for (int i = 1; i < roots.size(); ++i) {
		for (int j = i; j > 0; --j)
			p(j) = p(j-1) - roots(i) * p(j);
		p(0) *= - roots(i);
	}
	return p;
}

Eigen::VectorXd solvePolynomialRoots(const Eigen::VectorXd &p, const unsigned int nbIter) {
	// Construction de la matrice compagnon
	Eigen::MatrixXd c = Eigen::MatrixXd::Zero(p.rows()-1, p.rows()-1);
	for (int i = 0; i < c.rows(); ++i)
	{
		for (int j = 0; j < c.cols(); ++j)
		{
			if (j == i-1) 
				c(i,j) = 1;
			if (j == c.rows()-1) 
				c(i,j) = -p(i);
		}
	}

	std::cout << "Compagnon : " << std::endl << c << std::endl;

	for (unsigned int i = 0; i < nbIter; ++i)
	{
		Eigen::HouseholderQR<Eigen::MatrixXd> qr(c);
		Eigen::MatrixXd Q = qr.householderQ();
		Eigen::MatrixXd R = qr.matrixQR().triangularView<Eigen::Upper>();

		c = R * Q;
	}

	return c.diagonal();
}

int main()
{
	Eigen::VectorXd p1(3);
	p1 << 1, 2, 3;
	std::cout << evalPolynomial(p1, 2) << std::endl;

	Eigen::VectorXd r(10);
	r << 1, 1, 3000, 4, 5, 6, 7, 8, 1000, 10;
	Eigen::VectorXd p2 = polynomialFromRoots(r);
	std::cout << p2 << std::endl;

	std::cout << solvePolynomialRoots(p2, 150) << std::endl;

	return 0;
}