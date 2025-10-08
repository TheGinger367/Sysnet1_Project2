#include <iostream>
#include <string>
#include "mt-collatz.hpp"

using namespace std;
int main (int argc, char *argv[]) {

    collatz_a(stoi(argv[1]));

    return 0;
}