#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#define n 1000000
#define p 10
using namespace std;

// static
int a[n], b[n], c[n];

void print() {
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
    }
}

void print2(int* z) {
    for (int i = 0; i < n; i++) {
        cout << z[i] << ' ';
    }
}

void run(int id, int start, int end) {
    cout << "hello " << id << endl;
    for (int i = start; i <= end; i++) {
        c[i] = a[i] + b[i];
    }
}

void run2(int id, int* x, int* y, int* z, int start, int end) {
    cout << "hello " << id << endl;
    for (int i = start; i <= end; i++) {
        z[i] = x[i] + y[i];
    }
}

void run3(int id) {
    cout << "hello " << id << endl;
    for(int i = id; i < n; i += p){
        c[i] = sqrt(pow(a[i], 3) + pow(b[i], 3));
    }
}

void run4(int id, int* x, int* y, int* z) {
    cout << "hello " << id << endl;
    for (int i = id; i < n; i += p) {
        z[i] = sqrt(pow(x[i],3) + pow(y[i],3));
    }
}

int main() {
    // dynamic
    int* x = new int[n];
    int* y = new int[n];
    int* z = new int[n];

    auto t_start = std::chrono::high_resolution_clock::now();

    thread th[p];
    int l, r;
    l = n/p;
    r = n%p;

    for (int i = 0; i < n; i ++) {
        a[i] = b[i] = sqrt(i);
        x[i] = y[i] = sqrt(i);
    }

    //int start, end;
    // start = end = -1;
    for (int i = 0; i < p; i ++) {
        th[i] = thread(run3, i); //140
        //th[i] = thread(run2, i, x, y, z, start, end);
        //th[i] = thread(run4, i, x, y, z); //160
    }

    for (int i = 0; i < p; i++) {
        th[i].join();
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    cout << "elapsed_time_ms = " << elapsed_time_ms << "\n";

    //ciclic - 55:static; 56:dinamic;

    //print2(z);

    return 0;
}
