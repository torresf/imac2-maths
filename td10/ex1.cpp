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


Eigen::VectorXd rootsRafinement(const Eigen::VectorXd &p, Eigen::VectorXd &roots, const unsigned int nbIter) {
	// Derivate of a polynomial
	Eigen::VectorXd pDerivative = p.tail(p.size()-1);
	for (int i = 0; i < pDerivative.size(); ++i)
	{
		pDerivative(i) *= i+1;
	}

	// Newton
	for (int r = 0; r < roots.size(); ++r)
	{
		for (unsigned int i = 0; i < nbIter; ++i)
		{
			roots(r) = roots(r) - (evalPolynomial(p, roots(r)) / evalPolynomial(pDerivative, roots(r)));
		}
	}
	

	return roots;
}

int main()
{
	// Eigen::VectorXd p1(3);
	// p1 << 1, 2, 3;
	// std::cout << evalPolynomial(p1, 2) << std::endl;

	// Eigen::VectorXd r(3);
	// r << 1, 2, 3;
	// Eigen::VectorXd p2 = polynomialFromRoots(r);
	// std::cout << p2 << std::endl;

	// std::cout << solvePolynomialRoots(p2, 150) << std::endl;


	Eigen::VectorXd roots(5);
	roots << 1, 2, 3, 4, 5;
	Eigen::VectorXd p = polynomialFromRoots(roots);
	roots = solvePolynomialRoots(p, 20);
	std::cout << "ROOTS 1" << std::endl << roots << std::endl;
	roots = rootsRafinement(p, roots, 20);
	std::cout << "ROOTS 2" << std::endl << roots << std::endl;
 
	return 0;
}