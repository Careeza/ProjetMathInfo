#include "polynome.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Poly::Poly() {
	coefs_.push_back(0);
}

Poly::Poly(std::vector<double> coefs) : coefs_(coefs) {
	std::reverse(coefs_.begin(), coefs_.end());
}

Poly::Poly(size_t deg, double val) : coefs_(deg, val)
{}

Poly::~Poly() {

}

Poly	Poly::operator*(const double& a) const 
{
	Poly	p;
	
	p.coefs_ = this->coefs_;
	for (double& coef : p.coefs_) {
		coef *= a;
	}
	return (p);
}

Poly	Poly::operator*(const Poly& p) const {
	Poly	p2(p.coefs_.size() + this->coefs_.size(), 0.0);

	for (size_t i = 0; i < this->coefs_.size(); i++) {
		for (size_t j = 0; j < p.coefs_.size(); j++) {
			p2.coefs_[i + j] += this->coefs_[i] * p.coefs_[j];
		}
	}
	return (p2);
}

Poly	Poly::operator+(const double& a) const 
{
	Poly	p;
	
	p.coefs_ = this->coefs_;
	p.coefs_[0] += a;
	return (p);
}

Poly	Poly::operator+(const Poly& p) const {
	Poly	p2;
	size_t	i;

	for (i = 0; i < this->coefs_.size() && i < p.coefs_.size(); i++) {
		p2.coefs_[i] = this->coefs_[i] + p.coefs_[i];
	}
	for (; i < this->coefs_.size(); i++) {
		p2.coefs_[i] = this->coefs_[i];
	}
	for (; i < p.coefs_.size(); i++) {
		p2.coefs_[i] = p.coefs_[i];
	}
	return (p2);
}

double	Poly::operator()(double x) const {
	double res = 0;

	for (size_t i = 0; i < coefs_.size(); i++) {
		res += pow(x, i) * coefs_[i];
		std::cout << pow(x, i) * coefs_[i] << std::endl;
	}
	return (res);
}

std::ostream& operator<<(std::ostream &os, const Poly &p) 
{
	for (size_t i = 0; i < p.coefs_.size(); i++) {
		if (p.coefs_[i] != 0) {
			os << p.coefs_[i] << " * X^" << i << " + ";
		}
	}
	std::cout << std::endl;
	return (os);
}