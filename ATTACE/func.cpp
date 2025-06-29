#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <stdint.h>

#include "func.h"

using namespace std;

bool isPrime(uint64_t p) {
    if (p <= 1) return false;
    if (p <= 3) return true;
    if (p % 2 == 0 || p % 3 == 0) return false;

    for (uint64_t i = 5; i * i <= p; i += 6) {
        if (p % i == 0 || p % (i + 2) == 0) 
            return false;
    }
    return true;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t aXmodP(uint64_t a, uint64_t x, uint64_t p) {
    uint64_t res = 1;
    a %= p;
    while (x > 0) {
        if (x & 1) 
            res = (res * a) % p;
        a = (a * a) % p;
        x >>= 1;
    }
    return res;
}

uint64_t MulMod(uint64_t a, uint64_t b, uint64_t n) {
    return (a * b) % n;
}

vector<uint64_t> prime_factors(uint64_t n) {
    vector<uint64_t> factors;
    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

bool is_primitive_root(uint64_t g, uint64_t p) {
    if (g == 1) return false;
    if (gcd(g, p) != 1) return false;
    uint64_t m = p - 1;
    auto factors = prime_factors(m);
    for (uint64_t q : factors) {
        if (aXmodP(g, m / q, p) == 1) 
            return false;
    }
    return true;
}

tuple<uint64_t, uint64_t, uint64_t, uint64_t> KeysGenerator() {
    uint64_t p, g, x, y;
    
    do {
        p = rand() % 9000 + 1000;
    } while (!isPrime(p));

    do {
        g = rand() % (p - 1) + 1;
    } while (!is_primitive_root(g, p));

    x = rand() % (p - 1) + 1;
    y = aXmodP(g, x, p);

    return make_tuple(p, g, x, y);
}

void crypt(uint64_t p, uint64_t g, uint64_t x, uint64_t y, 
          const vector<unsigned char>& plainData, 
          vector<unsigned char>& cipherData, 
          ofstream& out) {
    
    out << "Открытый ключ (p, g, y) = (" << p << ", " << g << ", " << y << ")" << endl;
    out << "Закрытый ключ x = " << x << endl << endl;

    out << "Шифруемые данные (бинарные, " << plainData.size() << " байт):" << endl;
    
    for (size_t i = 0; i < plainData.size(); ++i) {
        uint64_t m = plainData[i];
        uint64_t k;

        do {
            k = rand() % (p - 2) + 1;
        } while (gcd(k, p - 1) != 1);

        uint64_t a = aXmodP(g, k, p);
        uint64_t b = MulMod(aXmodP(y, k, p), m, p);

        for (int j = 0; j < 8; ++j) {
            cipherData.push_back((a >> (8 * j)) & 0xFF);
        }
        for (int j = 0; j < 8; ++j) {
            cipherData.push_back((b >> (8 * j)) & 0xFF);
        }

        if (i < 3) {
            out << "Байт " << i << " (m=" << (int)m << ") → (a=" << a << ", b=" << b << ")" << endl;
        }
    }

    out << "\nЗашифровано " << plainData.size() << " байт. Размер шифра: " 
        << cipherData.size() << " байт." << endl;
}

void decrypt(uint64_t p, uint64_t x, 
            const vector<unsigned char>& cipherData, 
            vector<unsigned char>& decryptedData, 
            ofstream& out) {
    
    out << "\nВНИМАНИЕ! ВНЕШТАТНАЯ СИТУАЦИЯ. НАБЛЮДАЕТСЯ АТАКА ПОСЕРЕДИНЕ. РАСШИФРОВКА МОЖЕТ НЕ СООТВЕТСТВОВАТЬ ОЖИДАНИЮ." << endl;
    out << "Дешифрование:" << endl;

    for (size_t i = 0; i < cipherData.size(); i += 16) {
        if (i + 16 > cipherData.size()) break;

        uint64_t a = 0, b = 0;
        for (int j = 0; j < 8; ++j) {
            a |= (uint64_t)cipherData[i + j] << (8 * j);
            b |= (uint64_t)cipherData[i + 8 + j] << (8 * j);
        }

        uint64_t m = MulMod(b, aXmodP(a, p - 1 - x, p), p);
        decryptedData.push_back((unsigned char)m);

        if (i / 16 < 3) {
            out << "(a=" << a << ", b=" << b << ") → m=" << (int)m << endl;
        }
    }

    out << "\nДешифровано " << decryptedData.size() << " байт." << endl;
}