#include "mathBonus.hpp"

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
    double h = t / 1000.0;

    return ((f(t + h) - f(t - h))/(2 * h));
}

std::tuple<double, double>	normalize(double x, double y) {
    double norm = sqrt(x * x + y * y);

    if (norm != 0) {
        return(std::make_tuple(x / norm, y / norm));
    } else {
        return(std::make_tuple(0, 0));
    }
}
