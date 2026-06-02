#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int jumpSearchCore(const vector<int>& arr, int target, int& steps) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    steps = 0;
    
