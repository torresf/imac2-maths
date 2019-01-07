#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <algorithm>

double calcPI(double a) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::cout << "seed : " << seed << std::endl;
	std::default_random_engine generator(seed);
	// uniform real distribution
	std::uniform_real_distribution<double> uniformRealDistribution(0, a);
	double x, y;
	double count = 0;
	int nbPoints = 10000;
	double aSquare = a*a;
	for(int i=0; i < nbPoints; ++i) {
		x = uniformRealDistribution(generator);
		y = uniformRealDistribution(generator);
		if (x*x + y*y < aSquare) {
			count++;
		}
	}

	std::cout << "count : " << count << std::endl;
	std::cout << "nbPoints/count : " << nbPoints/count << std::endl;
	return 4*count/nbPoints;
}

double probaTriangle(float l, int iter) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::cout << "seed : " << seed << std::endl;
	std::default_random_engine generator(seed);

	// uniform real distribution
	double a, b; // Nombres aléatoires
	double l1, l2, l3; // l1 + l2 + l3 = longueur de la corde
	double count = 0;
	std::vector<double> v;
	std::uniform_real_distribution<double> uniformRealDistribution(0, l);

	for (int i = 0; i < iter; ++i) {
		a = uniformRealDistribution(generator);
		b = uniformRealDistribution(generator);
		if (a > b) {
			std::swap(a, b);
		}
		l1 = a;
		l2 = b - a;
		l3 = l - b;

		// On stocke les 3 longueurs dans un vecteur
		v.push_back(l1);
		v.push_back(l2);
		v.push_back(l3);

		// On tri le vecteur
		std::sort(v.begin(), v.end(), [](double a, double b) {
			return a > b;   
		});

		// Si la somme des deux plus petits segments 
		// est supérieure au plus grand segment, 
		// on peut créer un triangle
		if (v[0] + v[1] > v[2]) {
			count++;
		}
	}
	return 1 - (count / iter);
}

int main()
{
	double a = 1;
	double monPI = calcPI(a);

	std::cout << "monPI : " << monPI << std::endl;
	std::cout << "Vérification : " << M_PI - monPI << std::endl;
	std::cout << "Triangle Proba : " << probaTriangle(10, 50) << std::endl;
	return 0;
}