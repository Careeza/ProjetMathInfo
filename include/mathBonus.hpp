#ifndef MATHBONUS_HPP

# define MATHBONUS_HPP

# include <cmath>
# include <functional>
# include <tuple>
# include "point.hpp"

struct Case  {
	int		indice = 0;
	bool	colored = false;
	bool	onCurve = false;
};

double  					fact(int n);
double						comb(int k, int n);
double						derivate(std::function<double(double)> f, double t);
std::tuple<double, double>	normalize(double x, double y);
double						normalizeX(double x, double y);
double						normalizeY(double x, double y);
double						integrate(double a, double b, std::function<double(double)> f, int N);
double						polaireAngle(Point<double> p1);
int							radianToDegree(double radian);
std::tuple<std::function<double(double)>, std::function<double(double)>> lineFunction(Point<double> p1, Point<double> p2);
std::tuple<std::function<double(double)>, std::function<double(double)>> lineFunction(Point<double> p1, Point<double> p2);
std::function<double(double)>	derivateFunction(std::function<double(double)> f);
std::tuple<std::function<double(double)>, std::function<double(double)>>	shiftFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p);
std::tuple<std::function<double(double)>, std::function<double(double)>>	normalizeFunction(std::function<double(double)> xt, std::function<double(double)> yt);

#endif