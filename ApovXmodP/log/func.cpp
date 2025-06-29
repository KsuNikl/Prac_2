#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdint.h>

#include "func.h"

using namespace std;

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

// Возведение в степень по модулю
uint64_t aXmodP(uint64_t a, uint64_t x, uint64_t p)
{
   uint64_t degree = x % (p - 1);
   if (x == 0)
   {
      degree = 1;
   }

   uint64_t result = 1;
   for (uint64_t i = 1; i <= degree; i++)
   {
      result = result * a;
      result %= p;
   }

   return result;
}

vector<short> DecToBin(uint64_t number)
{
   vector<short> BinNumbers;
   while (number != 0)
   {
      BinNumbers.push_back(number % 2);
      number /= 2;
   }
   return BinNumbers;
}

uint64_t aXmodPviaLog(uint64_t a, uint64_t x, uint64_t p)
{
   if (x == 0)
      return 1 % p;
   if (p == 1)
      return 0;

   int maxPowerOfTwo = static_cast<int>(ceil(log2(x)));
   if (pow(2, maxPowerOfTwo) < x)
      maxPowerOfTwo++;

   vector<uint64_t> rowOfAs;
   for (uint64_t i = 0; i <= maxPowerOfTwo; ++i)
   {
      uint64_t exponent = 1 << i;
      rowOfAs.push_back(aXmodP(a, exponent, p));
   }

   vector<short> BinX = DecToBin(x);

   uint64_t result = 1;
   for (uint64_t i = 0; i < static_cast<uint64_t>(BinX.size()); ++i)
   {
      if (i < static_cast<uint64_t>(rowOfAs.size()) && BinX[i] == 1)
      {
         result = (result * rowOfAs[i]) % p;
      }
   }

   return result;
}