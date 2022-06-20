#ifndef MATHBONUS_HPP

# define MATHBONUS_HPP

# include <cmath>
# include <functional>
# include <tuple>

double  				fact(int n);
double					comb(int k, int n);
double					derivate(std::function<double(double)> f, double t);
std::tuple<double, double>	normalize(double x, double y);

#endif