#ifndef MATHBONUS_HPP

# define MATHBONUS_HPP

# include <cmath>
# include <functional>
# include <tuple>

double  					fact(int n);
double						comb(int k, int n);
double						derivate(std::function<double(double)> f, double t);
std::tuple<double, double>	normalize(double x, double y);
double						normalizeX(double x, double y);
double						normalizeY(double x, double y);
double						integrate(double a, double b, std::function<double(double)> f, int N);

#endif