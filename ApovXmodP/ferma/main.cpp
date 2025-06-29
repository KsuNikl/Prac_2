#include <iostream>
#include <stdint.h>

#include "func.h"

using namespace std;

int main()
{
   uint64_t a1, x1;
   cout << "Введите первое число и его степень через пробел: ";
   cin >> a1 >> x1;

   uint64_t a2, x2;
   cout << "Введите второе число и его степень: ";
   cin >> a2 >> x2;

   uint64_t p;
    cout << "Введите модуль p: ";
    cin >> p;

    if(!isPrime(p)){
        cout << endl << "Модуль не является простым числом, попробуйте другой. Модуль обязательно должен быть > 0!" << endl;
        return 0;
    }
     if(aXmodP(a1, x1, p) == aXmodP(a2, x2, p)){
        cout << a1 << "**" << x1 << " mod " << p << " == " << a2 << "**" << x2 << " mod " << p << endl;
    }
    else{
        cout << a1 << "**" << x1 << " mod " << p << " != " << a2 << "**" << x2 << " mod " << p << endl;
    }
    return 0;
}