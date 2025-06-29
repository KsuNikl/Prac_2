#include <iostream>
#include "func.h"

using namespace std;

int main()
{
    uint64_t c = 0, m = 0;
    cout << "Введите c (число для обратного элемента): ";
    cin >> c;
    cout << "Введите m (модуль): ";
    cin >> m;

    MutuallyPrimeCheck(gcd(c, m));

    uint64_t d = extendedEuclidean(c, m, m);

    cout << "Обратный элемент d = " << d << endl;
    cout << c << "^(-1) mod " << m << " = " << d << endl;
    cout << c << "*" << d << " mod " << m << " = " << (c * d) % m << endl;

    return 0;
}