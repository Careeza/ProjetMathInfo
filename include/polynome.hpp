#ifndef POLYNOME_HPP

# define POINT_HPP

#include <vector>
#include <iostream>

class Poly {
	/*
	**	Classe polynome
	**	Coefficient stocke dans ordre croissant de degree coefs_[0] = a * x^0
	*/
	public:
		Poly();
		Poly(size_t deg, double val);
		Poly(std::vector<double> coefs);
		~Poly();
		Poly	operator*(const double& a) const;
		Poly	operator*(const Poly& p) const;
		Poly	operator+(const double& a) const;
		Poly	operator+(const Poly& p) const;
		double	operator()(double x) const;
		friend std::ostream& operator<<(std::ostream &os, const Poly &p);

	private:
		std::vector<double>	coefs_;
};

std::ostream& operator<<(std::ostream &os, const Poly &p);

#endif