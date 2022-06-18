#include "mathBonus.hpp"

int fact(int n) {
    int res = 1;

    while (n > 1) {
        res *= n;
        n--;
    }
    return (res);
}

int	comb(int k, int n) {
    return (fact(n) / (fact(k) * fact(n - k)));
}