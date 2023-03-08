//
//  tools.cpp
//  e2ee
//
//  Created by 白竞帆 on 2022/11/22.
//

#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "tools.h"

int countPrimes(int n){
    return 1;
}

ull quick_mode(ull base, ull expo, ull mode){
    ull sum = 1;
    while(expo){
        if(expo & 0x0001) sum = quick_multiply(sum, base, mode);
        expo>>=1;
        base = quick_multiply(base, base, mode);
    }
    return sum;
}

ull quick_multiply(ull a, ull b, ull mode){
    ull mul = 0;
    while(b){
        if(b & 0x0001){
            b--;
            mul = (mul+a)%mode;
        }
        b >>= 1;
        a = (a+a)%mode;
    }
    return mul;
}

bool isPrime_lazyloop(ull n){  // O(sqrt(n))
    if(n<=1 || n == 4)
        return false;
    if(n == 2 || n == 3)
        return true;
    if(n % 6 != 1 && n % 6 != 5)  // 质数一定是6k-1 / 6k+1
        return false;
    for(ull i = 2; i*i<=n; i++){  // 从2开始循环，到根号n为止
        if(n%i == 0)  // 如果n被i整除，证明不是质数
            return false;
    }
    return true;
}

bool isPrime_eratosthenes(ull n){ // O(n^2), 会生成一个质数表
    vector<int> primes(n+1, 1);  // 质数表，0表示不是质数，1表示质数
    primes[0] = 0;
    primes[1] = 0;
    primes[2] = 1;
    for(ull i = 2; i<=n; i++){
        if(primes[i]){
            ull k = 2;
            while(i*k<=n){
                primes[i*k] = 0;
                k++;
            }
        }
    }
    return primes[n];
}

bool isPrime_euler(ull n){  // O(n), 算法理解有点困难, 会生成一个质数表
    vector<int> isprimes(n+1, 1);// 质数表，0表示不是质数，1表示质数
    vector<ull> primes;
    
    isprimes[0] = 0;
    isprimes[1] = 0;
    isprimes[2] = 1;
    
    for(ull i = 2; i<=n; i++){
        if(isprimes[i]) primes.push_back(i);
        
        for(ull k = 1; k<primes.size() && i*primes[k]<=n; k++){
            isprimes[i*primes[k]] = 0;
            if(i%primes[k] == 0) break;
        }
    }
    return isprimes[n];
}

bool isPrime_Fermat(ull n){ // 费马小定律逆应用，错误率较大
    //carmichael数，561，1105，1729...
    if(n<=1) return false;
    if(n == 2) return true;
    
    //费马小定律：
    //a是整数，p是素数， a^(p-1) mod p = 1
    // (a*b)% c = (a % c)(b % c)% c
    //费马小定律有可能把合数给判断成素数,概率在1.几，有点高
    
    //我们这里把a取2, 使用快速幂取模得出结果
    return quick_mode(2, n-1, n) == 1;
//    int a = 2, p = n-1;
//    int sum = 1;
//    while(p){
//        if(p & 0x0001) sum = (sum*a)%n;
//
//        p>>=1;
//
//        a = (a*a)%n;
//
//    }
//    return sum == 1;
}

bool isPrime_millerrabin(ull n){
    // 二次检验定理：对于质数 p，在0~p-1范围内，满足
    // x^2 mod p = 1 的整数只有 1 和 p-1.
    
    //正确率比费马小定律要高很多,当a取的次数越多，正确率几乎为100%
    if(n<=1){
        return false;
    }
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    if(count(primes.begin(), primes.end(), n)){
        return true;
    }
    ull k = 0, t = n-1;  // 2^k*t = n-1; t是奇数
    while(!(t & 0x0001)){
        k++;
        t >>= 1;
    }
    for(ull i = 0; i<primes.size(); i++){
        ull a = primes[i];
        ull b = quick_mode(a, t, n);
        if(b == 1) continue;
        for(ull j = 0; j<k; j++){
            ull b_square = quick_multiply(b, b, n);
            if(b_square == 1 && b!=n-1 && b!=1)
                return false;
            b = b_square;
        }
        if(b != 1)
            return false;
    }
    return true;
}

bool isRelativelyPrime(ull a, ull b){
    if(a == 1 || b == 1)
        return false;
    ull temp;
    while((temp = a%b) != 0){
        a = b;
        b = temp;
    }
    if(b>1) return false;  // 最大公约数大于1，表示不互质
    else return true;
}

ull getRandom64bit(){
    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
    //mt19937_64 g(seed1);    // 随机数应取32位，否则两个64位随机数相乘，可能超过64位
    mt19937 g(seed1);
    return g();
}

ull getRandom64bit_prime(){
    ull rd_int64;
    while(true){
        rd_int64 = getRandom64bit();
        if(isPrime_millerrabin(rd_int64))
            break;
    }
    return rd_int64;
}

vector<ull> RSA(){
    vector<ull> nums(2, 0);
    while(true){  // 求模逆元的时候，有可能会失效，所以需要取到可用的公私钥为止
        nums[0] = getRandom64bit_prime();
        nums[1] = getRandom64bit_prime();
        //nums[0] = 17;
        //nums[1] = 61;
        
        ull N = nums[0] * nums[1];
        
        ull r = (nums[0]-1) * (nums[1]-1);
        ull e;
        while(true){
            e = getRandom64bit();
            //e = 577;
            if(e>1 && e<r && isRelativelyPrime(e, r))
                break;
        }
        // 求模逆元
        ull d = inv(e, r);           // 管用
        //ull d = inv_euler(e, r);   // 不管用
        
        if(quick_multiply(e, d, r) == 1){
            nums[0] = e;         // 返回的第一位是公钥
            nums[1] = d;         // 返回的第二位是私钥
            nums.push_back(N);   // 返回的第三位是N
            //cout<<r<<" is the r."<<endl;
            return nums;
        }else{
            continue;
        }
    }
    return {};
}

ull exgcd(ull a, ull b, ull &x, ull &y)
{
    if(a == 0){
        x = 0;
        y = 1;
        return b;
    }
    ull x1, y1;
    ull result = exgcd(b%a, a, x1, y1);
    x = y1-(b/a)*x1;
    y = x1;
    
    return result;
}

ull inv(ull a, ull p)
{
    ull x, y;
    exgcd(a, p, x, y);
    return (p + x % p) % p;
}

ull inv_euler(ull a, ull p){
    ull phi = p, mod = p;
        for (ull i = 2; i <= p / i; i++)
        if (p % i == 0)
        {
            phi = phi / i * (i - 1);
            while (p % i == 0)
                p /= i;
        }
    if (p > 1)
        phi = phi / p * (p - 1);
    phi--;
    ull res = 1, t = a;
    while (phi)
    {
        if (phi & 1)
            res = (res * t) % mod;
        t = (t * t) % mod, phi >>= 1;
    }
    return res;
}
