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