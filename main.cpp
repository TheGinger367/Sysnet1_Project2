#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
#include <time.h>
  
#include "mt-collatz.hpp"

using namespace std;

constexpr int MAX_K = 1000;
vector<atomic<int>> globalArray(MAX_K + 1);
atomic<int> counter = 1;
mutex mtx;
bool nolock = false;

void worker(int maxNumber) {
    while (true) {
        int n = counter++;
        if (n > maxNumber) break;
        collatz_a(n);
    }
}

void addToVector(int value) {
    if (value < 0) return;
    if (value > MAX_K) value = MAX_K;
    globalArray[value]++;
}

int main(int argc, char *argv[]) {
    int maxNumber = stoi(argv[1]);
    int numberThreads = stoi(argv[2]);
    for (int i = 3; i < argc; ++i) {
        if (string(argv[i]) == "-nolock" || string(argv[i]) == "[-nolock]") {
            nolock = true;
        }
    }
    
    timespec start_ts{}, end_ts{};
    clock_gettime(CLOCK_MONOTONIC, &start_ts);

    vector<thread> threads;
    for (int i = 0; i < numberThreads; ++i)
        threads.emplace_back(worker, maxNumber);

    for (auto &t : threads) t.join();

    clock_gettime(CLOCK_MONOTONIC, &end_ts);

    double duration = (end_ts.tv_sec - start_ts.tv_sec) + (end_ts.tv_nsec - start_ts.tv_nsec) / 1e9;

    for (int k = 0; k <= MAX_K; ++k)
        cout << k << "," << globalArray[k].load() << "\n";

    cerr << maxNumber << "," << numberThreads << "," << duration << endl;
    return 0;
}
