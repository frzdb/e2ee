//
//  e2ee.h
//  e2ee
//
//  Created by 白竞帆 on 2022/12/11.
//

#ifndef e2ee_h
#define e2ee_h

#include <iostream>

#include "tools.h"

struct KeyPair{
    ull privateKey;
    ull publicKey;
    ull N;
};

KeyPair getKeyPair();

vector<ull> encode(string text, KeyPair kp);

string decode(vector<ull> encodedText, KeyPair kp);

vector<ull> encode_2(string text, KeyPair kp);  // 缩短加密密文长度

string decode_2(vector<ull> encodedText, KeyPair kp);

#endif /* e2ee_h */
