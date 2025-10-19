#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <time.h>
  
#include "mt-collatz.hpp"

using namespace std;

vector<int> globalArray;
std::atomic<int> counter(1);
mutex mtx;
bool nolock = false;

void worker(int maxNumber) {
    while (true) {
        int n = counter.fetch_add(1);
        collatz_a(n);
        if (n > maxNumber) break;
        
    }
}

void addToVector(int value, int index, bool nolock) {
    if (nolock == false){
    lock_guard<mutex> lock(mtx);
    }
    if (index >= 0 && index < (int)globalArray.size()) {
        globalArray[value] = globalArray[value] + 1;
    }
}

int main(int argc, char *argv[]) {
    int maxNumber = stoi(argv[1]);
    int numberThreads = stoi(argv[2]);
    for (int i = 3; i < argc; ++i) {
        if (std::string(argv[i]) == "-nolock" || std::string(argv[i]) == "[-nolock]") {
            nolock = true;
            ::nolock = true;
            break;
        }
    }
    

    globalArray.resize(maxNumber + 1, 0);
    
    vector<thread> threads;

    //auto start = chrono::high_resolution_clock::now();
    timespec start_ts{};
    clock_gettime(CLOCK_REALTIME, &start_ts);

    for (int i = 0; i < numberThreads; i++)
        threads.emplace_back(worker, maxNumber);

    for (auto &t : threads) t.join();

    timespec end_ts{};
    clock_gettime(CLOCK_REALTIME, &end_ts);
    //auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    double duration = (end_ts.tv_sec - start_ts.tv_sec)
                    + (end_ts.tv_nsec - start_ts.tv_nsec) / 1e9;

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

    
    for(int i = 0; i < maxNumber; i++){
        cout << i << "," << globalArray[i] << endl;
    }
/*     cout << "Processed " << count << " numbers up to " << maxNumber << endl;
    cout << "Max stopping time: " << maxSteps << endl;
    cout << "Average stopping time: " << avgSteps << endl;
    cout << "Total time: " << duration << " s" << endl; */
    cerr << maxNumber << "," << numberThreads << "," << duration << endl;
    return 0;
}