#pragma once
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <stdint.h>

using namespace std;

bool isPrime(uint64_t p);
uint64_t gcd(uint64_t a, uint64_t b);
uint64_t aXmodP(uint64_t a, uint64_t x, uint64_t p);
uint64_t MulMod(uint64_t a, uint64_t b, uint64_t n);
vector<uint64_t> prime_factors(uint64_t n);
bool is_primitive_root(uint64_t g, uint64_t p);
tuple<uint64_t, uint64_t, uint64_t, uint64_t> KeysGenerator();
void crypt(uint64_t p, uint64_t g, uint64_t x, uint64_t y, const vector<unsigned char>& plainData, vector<unsigned char>& cipherData, ofstream& out);
void decrypt(uint64_t p, uint64_t x, const vector<unsigned char>& cipherData, vector<unsigned char>& decryptedData, ofstream& out);