#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <stdint.h>

#include "func.h"

using namespace std;

// Проверка на простоту
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

// Алгоритм Евклида
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Быстрое возведение в степень по модулю
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

// Умножение по модулю
uint64_t MulMod(uint64_t a, uint64_t b, uint64_t n) {
    return (a * b) % n;
}

// Разложение на простые множители
vector<uint64_t> prime_factors(uint64_t n) {
    vector<uint64_t> factors;
    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (uint64_t i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

// Проверка, является ли число первообразным корнем
bool is_primitive_root(uint64_t g, uint64_t p) {
    if (gcd(g, p) != 1) return false;
    uint64_t phi = p - 1;
    auto factors = prime_factors(phi);
    for (uint64_t q : factors) {
        if (aXmodP(g, phi / q, p) == 1) 
            return false;
    }
    return true;
}

// Генерация ключей
tuple<uint64_t, uint64_t, uint64_t, uint64_t> KeysGenerator() {
    uint64_t p, g, x, y;

    // Генерация простого p
    do {
        p = rand() % 9000 + 1000;
    } while (!isPrime(p));

    // Поиск первообразного корня g
    do {
        g = rand() % (p - 1) + 1;
    } while (!is_primitive_root(g, p));

    // Закрытый ключ x
    x = rand() % (p - 1) + 1;

    // Открытый ключ y
    y = aXmodP(g, x, p);

    return make_tuple(p, g, x, y);
}

// Шифрование (с логированием)
void crypt(uint64_t p, uint64_t g, uint64_t x, uint64_t y, 
          const vector<unsigned char>& plainData, 
          vector<unsigned char>& cipherData, 
          ofstream& out) {
    
    out << "Открытый ключ (p, g, y) = (" << p << ", " << g << ", " << y << ")" << endl;
    out << "Закрытый ключ x = " << x << endl << endl;

    out << "Шифруемые данные (бинарные, " << plainData.size() << " байт):" << endl;
    
    // Шифрование каждого байта
    for (size_t i = 0; i < plainData.size(); ++i) {
        uint64_t m = plainData[i];
        uint64_t k;

        // Выбор случайного k (взаимно простого с p-1)
        do {
            k = rand() % (p - 2) + 1;
        } while (gcd(k, p - 1) != 1);

        uint64_t a = aXmodP(g, k, p);
        uint64_t b = MulMod(aXmodP(y, k, p), m, p);

        // Запись (a, b) в бинарный формат (по 8 байт)
        for (int j = 0; j < 8; ++j) {
            cipherData.push_back((a >> (8 * j)) & 0xFF);
        }
        for (int j = 0; j < 8; ++j) {
            cipherData.push_back((b >> (8 * j)) & 0xFF);
        }

        // Логирование (первые 10 байт для примера)
        if (i < 10) {
            out << "Байт " << i << " (m=" << (int)m << ") → (a=" << a << ", b=" << b << ")" << endl;
        }
    }

    out << "\nЗашифровано " << plainData.size() << " байт. Размер шифра: " 
        << cipherData.size() << " байт." << endl;
}

// Дешифрование (с логированием)
void decrypt(uint64_t p, uint64_t x, 
            const vector<unsigned char>& cipherData, 
            vector<unsigned char>& decryptedData, 
            ofstream& out) {
    
    out << "\nДешифрование:" << endl;

    for (size_t i = 0; i < cipherData.size(); i += 16) {
        if (i + 16 > cipherData.size()) break;

        // Извлечение a и b из бинарных данных
        uint64_t a = 0, b = 0;
        for (int j = 0; j < 8; ++j) {
            a |= (uint64_t)cipherData[i + j] << (8 * j);
            b |= (uint64_t)cipherData[i + 8 + j] << (8 * j);
        }

        // Вычисление исходного байта
        uint64_t m = MulMod(b, aXmodP(a, p - 1 - x, p), p);
        decryptedData.push_back((unsigned char)m);

        // Логирование (первые 10 значений)
        if (i / 16 < 10) {
            out << "(a=" << a << ", b=" << b << ") → m=" << (int)m << endl;
        }
    }

    out << "\nДешифровано " << decryptedData.size() << " байт." << endl;
}