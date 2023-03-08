//
//  main.cpp
//  e2ee
//
//  Created by 白竞帆 on 2022/11/21.
//

#include <iostream>

//#include "tools.h"
#include "e2ee.h"

typedef unsigned long long uint_64;

using namespace std;



int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    ull n = 561;
    //cout<<isPrime_lazyloop(n)<<endl;
    //cout<<isPrime_eratosthenes(n)<<endl;
    //cout<<isPrime_euler(n)<<endl;
    //cout<<isPrime_Fermat(n)<<endl;
    //cout<<isPrime_millerrabin(n)<<endl;
    
//    vector<ull> keyPair = RSA();
//    cout<<keyPair[0]<<" is the public key."<<endl;
//    cout<<keyPair[1]<<" is the private key."<<endl;
//    cout<<keyPair[2]<<" is N."<<endl;
//
//    ull e = keyPair[0];
//    ull d = keyPair[1];
//    ull N = keyPair[2];
//    //ull num = 12446744073709551615;
//    ull num = 844674407370955161;
//
//    cout<<"Origin num is "<<dec<<num<<endl;
//    //e = 2950270414624386633;
//    //d = 3659135897;
//    //N = 8009776687231414951;
//    ull encodeNum = quick_mode(num, e, N);
//    //ull encodeNum = quick_mode(num, 7, 30);
//    cout<<"Encode num is "<<hex<<encodeNum<<endl;
//    ull decodeNum = quick_mode(encodeNum, d, N);
//    //ull decodeNum = quick_mode(encodeNum, 3, 30);
//    cout<<"Decode num is "<<dec<<decodeNum<<endl;
//
////    cout<<rd_int64<<" which is ";
////    if(!isPrime_millerrabin(rd_int64)){
////        cout<<"not ";
////    }else{
////    }
////    cout<<"a prime number."<<endl;
//
//    cout<<endl<<endl;
    
    KeyPair kp = getKeyPair();
    
    string txt = "Four score and seven years ago our fathers brought forth, on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.";
    cout<<"The input text is:"<<endl;
    cout<<txt<<endl;
    
    vector<ull> encodedTxt = encode_2(txt, kp);
    cout<<"The encoded text is:"<<endl;
    for(auto& et: encodedTxt){
        cout<<hex<<et;
    }
    cout<<endl;
    
    string decodedTxt = decode_2(encodedTxt, kp);
    cout<<"The decoded text is:"<<endl;
    cout<<decodedTxt<<endl;
    
    return 0;
}
