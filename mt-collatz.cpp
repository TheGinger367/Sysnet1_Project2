#include "mt-collatz.hpp"

extern void addToVector(int steps);
extern bool nolock;

long long collatz_f(long long n) {
    return (n % 2 == 0) ? n / 2 : 3LL * n + 1LL;
}

void collatz_a(int n) {
    int steps = 0;
    long long value = n;
    while (value != 1) {
        value = collatz_f(value);
        steps++;
    }

    addToVector(steps);
}
