#include "mathBonus.hpp"
#include "point.hpp"
#include <iostream>

double  fact(int n) {
	/* Compute the factorial of a number */
    double  res = 1;

    while (n > 1) {
        res *= n;
        n--;
    }
    return (res);
}

double  comb(int k, int n) {
	/* Compute the combination of a number */
    return (fact(n) / (fact(k) * fact(n - k)));
}

double	derivate(std::function<double(double)> f, double t) {
	/* Compute the derivate of a function */
	double h = 0.000001;

    return ((f(t + h) - f(t))/(h));
}

std::tuple<double, double>	normalize(double x, double y) {
	/* Normalize a vector */
	double norm = sqrt(x * x + y * y);

    if (norm != 0) {
        return(std::make_tuple(x / norm, y / norm));
    } else {
        return(std::make_tuple(0, 0));
    }
}

double	normalizeX(double x, double y) {
	/* Normalize a vector */
	double norm = sqrt(x * x + y * y);

    if (norm != 0) {
		return (x / norm);
    } else {
		return (0);
    }
}

double	normalizeY(double x, double y) {
	/* Normalize a vector */
	double norm = sqrt(x * x + y * y);

    if (norm != 0) {
		return (y / norm);
    } else {
		return (0);
    }
}

double	integrate(double a, double b, std::function<double(double)> f, int N)
{
	/* Compute the integral of a function between a and b*/
    double	pas = (b - a) / static_cast<double>(N);
    double	sum = 0;
    for (int i = 0 ; i < N ; i++) {
        sum +=  (f(a + i * pas) + 4 * f(a + (i + 0.5) * pas) + f(a + (i + 1) * pas));
	}
    return (sum * pas / 6);
}

double		polaireAngle(Point<double> p1)
{
	/* Compute the angle of a vector */
	return (atan2(p1.getY(), p1.getX()));
}

int			radianToDegree(double radian)
{
	/* Convert radian to degree */
	return (static_cast<int>(radian * 180 / M_PI));
}

std::tuple<std::function<double(double)>, std::function<double(double)>> lineFunction(Point<double> p1, Point<double> p2) {
	/* return the function used in the line */
	std::function<double(double)> xt = {[p1, p2](double t) {return (p1.getX() + (p2.getX() - p1.getX()) * t);}};
	std::function<double(double)> yt = {[p1, p2](double t) {return (p1.getY() + (p2.getY() - p1.getY()) * t);}};
	return (std::make_tuple(xt, yt));
}

std::function<double(double)>	derivateFunction(std::function<double(double)> f) {
	/* Return the derivate of the function f */
	return [f](double t) {
		return (derivate(f, t));
	};
}

std::tuple<std::function<double(double)>, std::function<double(double)>>	shiftFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	/* Shift the function to the point p */
	double	x = p.getX();
	double	y = p.getY();

	std::function<double(double)> xt_ = {[x, xt](double t) {return (xt(t) - x);}};
	std::function<double(double)> yt_ = {[y, yt](double t) {return (yt(t) - y);}};
	return (std::make_tuple(xt_, yt_));
}

std::tuple<std::function<double(double)>, std::function<double(double)>>	normalizeFunction(std::function<double(double)> xt, std::function<double(double)> yt) {
	/* Normalize the function */
	std::function<double(double)> at = {[xt, yt](double t) {return (normalizeX(xt(t), yt(t)));}};
	std::function<double(double)> bt = {[xt, yt](double t) {return (normalizeY(xt(t), yt(t)));}};
	return (std::make_tuple(at, bt));
}