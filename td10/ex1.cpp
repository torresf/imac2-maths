#include <iostream>
#include <Eigen/Dense>

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

int main()
{
	// Eigen::VectorXd p1(3);
	// p1 << 1, 2, 3;
	// std::cout << evalPolynomial(p1, 2) << std::endl;

	Eigen::VectorXd r(3);
	r << 2, 3, 4;
	Eigen::VectorXd p2 = polynomialFromRoots(r);
	std::cout << p2 << std::endl;

	return 0;
}