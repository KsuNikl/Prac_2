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
   cout << "Введите второе число и его степень через пробел: ";
   cin >> a2 >> x2;

   uint64_t p;
   cout << "Введите модуль: ";
   cin >> p;

   if (!isPrime(p))
   {
      cout << "Ошибка, p должно быть простым";
      return 0;
   }

   uint64_t result1 = aXmodPviaLog(a1, x1, p);
   uint64_t result2 = aXmodPviaLog(a2, x2, p);

   if (result1 == result2)
   {
      cout << a1 << "**" << x1 << " mod " << p << " == " << a2 << "**" << x2 << " mod " << p << endl;
   }
   else
   {
      cout << a1 << "**" << x1 << " mod " << p << " != " << a2 << "**" << x2 << " mod " << p << endl;
   }
   
   return 0;
}