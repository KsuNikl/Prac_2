#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <stdint.h>

#include "func.h"

using namespace std;

// Быстрое возведение в степень
uint64_t aXmodP(uint64_t a, uint64_t x, uint64_t p)
{
   uint64_t degree = x % (p - 1);

   uint64_t result = 1;
   for (uint64_t i = 1; i <= degree; i++)
   {
      result = result * a;
      result %= p;
   }

   return result;
}

// Поиск НОД (алгоритм Евклида)
uint64_t gcd(uint64_t a, uint64_t b)
{
   while (b != 0)
   {
      uint64_t r = b;
      b = a % b;
      a = r;
   }

   return a;
}

// Проверка на простоту
bool isPrime(uint64_t p)
{
   if (p % 2 == 0 || p % 3 == 0 || p <= 1)
   {
      return false;
   }

   uint64_t squareRootN = static_cast<uint64_t>(sqrt(p)) + 1;
   uint64_t maxI = (squareRootN + 1) / 6;

   for (uint64_t i = 1; i < maxI; i++)
   {
      uint64_t dividerMinusOne = 6 * i - 1;
      uint64_t dividerPlusOne = 6 * i + 1;

      if (dividerMinusOne <= squareRootN)
      {
         if (p % dividerMinusOne == 0)
            return false;
      }
      if (dividerPlusOne <= squareRootN)
      {
         if (p % dividerPlusOne == 0)
            return false;
      }
   }

   return true;
}
