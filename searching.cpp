#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int jumpSearchCore(const vector<int>& arr, int target, int& steps) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    steps = 0;
    
 cout << "Langkah Lompatan (sqrt(" << n << ")) = " << step << "\n";
    while (arr[min(step, n) - 1] < target) {
        steps++;
        cout << "Iterasi " << steps << ": Lompat ke indeks " << min(step, n) - 1 << " (Nilai: " << arr[min(step, n) - 1] << ")\n";
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

 cout << "Target berada di kisaran indeks " << prev << " sampai " << min(step, n) - 1 << ". Mulai pencarian linear...\n";
    while (arr[prev] < target) {
        steps++;
        prev++;
        if (prev == min(step, n)) return -1;
    }
