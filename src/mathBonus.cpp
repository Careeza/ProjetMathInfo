#include "mathBonus.hpp"
#include <iostream>

double  fact(int n) {
    double  res = 1;

    while (n > 1) {
        res *= n;
        n--;
    }
    return (res);
}

double  comb(int k, int n) {
    return (fact(n) / (fact(k) * fact(n - k)));
}

double	derivate(std::function<double(double)> f, double t) {
    double h = 0.00001;

    return ((f(t + h) - f(t))/(h));
}

std::tuple<double, double>	normalize(double x, double y) {
    double norm = sqrt(x * x + y * y);

    if (norm != 0) {
        return(std::make_tuple(x / norm, y / norm));
    } else {
        return(std::make_tuple(0, 0));
    }
}

double	normalizeX(double x, double y) {
    double norm = sqrt(x * x + y * y);

    if (norm != 0) {
		return (x / norm);
    } else {
		return (0);
    }
}

double	normalizeY(double x, double y) {
    double norm = sqrt(x * x + y * y);

    if (norm != 0) {
		return (y / norm);
    } else {
		return (0);
    }
}

double	integrate(double a, double b, std::function<double(double)> f, int N)
{
    double	pas = (b - a) / static_cast<double>(N);
    double	sum = 0;
    for (int i = 0 ; i < N ; i++) {
        sum +=  (f(a + i * pas) + 4 * f(a + (i + 0.5) * pas) + f(a + (i + 1) * pas));
	}
    return (sum * pas / 6);
}