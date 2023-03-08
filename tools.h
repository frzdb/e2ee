//
//  tools.h
//  e2ee
//
//  Created by 白竞帆 on 2022/11/22.
//

#ifndef tools_h
#define tools_h

#include <vector>
#include <chrono>
#include <random>
using namespace std;

typedef unsigned long long ull;
//typedef long long ull;

//
//count the number of primes which is less than given n
//

int countPrimes(int n);

bool isPrime_lazyloop(ull n);

bool isPrime_eratosthenes(ull n);

bool isPrime_euler(ull n);

bool isPrime_Fermat(ull n);

bool isPrime_millerrabin(ull n);

ull quick_mode(ull base, ull expo, ull mode);

ull quick_multiply(ull a, ull b, ull mode);

bool isRelativelyPrime(ull a, ull b);

ull getRandom64bit();

ull getRandom64bit_prime();

vector<ull> RSA();

ull inv(ull a, ull p);  // 求模逆元，ab 模 p 等于1，求b
// 转换为 ax+by = 1的问题
ull exgcd(ull a, ull b, ull &x, ull &y); // 这里需要用的拓展欧几里得算法

ull inv_euler(ull a, ull p);

#endif /* tools_h */
