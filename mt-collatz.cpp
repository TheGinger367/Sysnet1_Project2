#include <iostream>
#include <thread>
#include "mt-collatz.hpp"

// ./mt-collatz Numbers Threads
// ./mt-collatz 1000000 4

// Collatz sequence
int collatz_f(int n) {
    if (n % 2 == 0) {
        return n / 2;
    } 
    else {
        return 3 * n + 1;
    }
}
void collatz_a(int n) {
    std::cout << n << " ";
    if (n == 1) return;
    collatz_a(collatz_f(n));
}