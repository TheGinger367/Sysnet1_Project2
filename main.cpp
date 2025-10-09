#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
  
#include "mt-collatz.hpp"

using namespace std;

vector<int> globalArray;
std::atomic<int> counter(1);
mutex mtx;

void worker(int maxNumber) {
    while (true) {
        int n = counter.fetch_add(1);
        if (n > maxNumber) break;
        collatz_a(n);
    }
}

void addToVector(int value, int index) {
    lock_guard<mutex> lock(mtx);
    if (index >= 0 && index < (int)globalArray.size()) {
        globalArray[index] = value;
    }
}

int main(int argc, char *argv[]) {

    int maxNumber = stoi(argv[1]);
    int numberThreads = stoi(argv[2]);

    globalArray.resize(maxNumber + 1, 0);
    
    vector<thread> threads;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numberThreads; i++)
        threads.emplace_back(worker, maxNumber);

    for (auto &t : threads) t.join();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Printing statistics
    int maxSteps = 0;
    long long totalSteps = 0;
    int count = 0;

    for (int i = 1; i <= maxNumber; ++i) {
        int steps = globalArray[i];
        totalSteps += steps;
        if (steps > maxSteps) maxSteps = steps;
        count++;
    }

    double avgSteps = static_cast<double>(totalSteps) / count;

    cout << "Processed " << count << " numbers up to " << maxNumber << endl;
    cout << "Max stopping time: " << maxSteps << endl;
    cout << "Average stopping time: " << avgSteps << endl;
    cout << "Total time: " << duration << " ms" << endl;

    return 0;
}