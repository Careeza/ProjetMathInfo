#ifndef POLYNOME_HPP

# define POLYNOME_HPP

# include "point.hpp"
# include <vector>
# include <iostream>
# include <tuple>
# include <string>

class Poly {
	/*
	**	Classe polynome
	**	Coefficient stocke dans ordre croissant de degree coefs_[0] = a * x^0
	*/
	public:
		Poly();
		Poly(std::string file, int c);
		Poly(size_t deg, double val);
		Poly(std::vector<double> coefs);
		~Poly();
		Poly	operator*(const double& a) const;
		Poly	operator*(const Poly& p) const;
		Poly	operator+(const double& a) const;
		Poly	operator+(const Poly& p) const;
		double	operator()(double x) const;
		void	savePoly(std::string name);
		friend std::ostream& operator<<(std::ostream &os, const Poly &p);

	private:
		std::vector<double>	coefs_;
};

Poly	puissance(const Poly& p, const int& a);
std::ostream& operator<<(std::ostream &os, const Poly &p);
std::tuple<Poly, Poly>	BezierPoly(std::vector<Point<double>> points);

#endif