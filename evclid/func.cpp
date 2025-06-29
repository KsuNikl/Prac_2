#include <iostream>
#include <cstdlib>
#include "func.h"

using namespace std;

// Алгоритм Евклида для нахождения НОД
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

// Расширенный алгоритм Евклида для нахождения обратного элемента
uint64_t extendedEuclidean(uint64_t a, uint64_t b, uint64_t m) {
    cout << "-------------------------" << endl;
    cout << "r \tx \ty \tq " << endl;
    cout << "-------------------------" << endl;
    
    uint64_t x0 = 1, x1 = 0;
    uint64_t y0 = 0, y1 = 1;
    uint64_t r = 0, q = 0;

    while (b != 0) {
        r = a % b;
        q = a / b;

        uint64_t new_x = x0 - q * x1;
        uint64_t new_y = y0 - q * y1;

        cout << r << "\t" << new_x << "\t" << new_y << "\t" << q << endl;
        cout << "-------------------------" << endl;
        
        a = b;
        b = r;
        
        x0 = x1;
        x1 = new_x;
        y0 = y1;
        y1 = new_y;
    }

    if (x0 < 0) {
        x0 += m;
    }
    
    return x0;
}

void MutuallyPrimeCheck(int gcd){
    if(gcd != 1){
        cerr << "Ошибка: c и m не взаимно просты, обратный элемент не существует." << endl;
        exit(1);
    }
}