//
//  e2ee.cpp
//  e2ee
//
//  Created by 白竞帆 on 2022/12/11.
//

#include "e2ee.h"

KeyPair getKeyPair(){
    vector<ull> kp = RSA();
    KeyPair keyPair;
    keyPair.privateKey = kp[0];  // 私钥短一点
    keyPair.publicKey = kp[1];   // 公钥长一点
    keyPair.N = kp[2];
    return keyPair;
}

vector<ull> encode(string text, KeyPair kp){
    ull publicKey = kp.publicKey;
    ull N = kp.N;
    vector<ull> encodedText;
    for(auto& c: text){
        encodedText.push_back((ull)c);
    }
    for(int i = 0; i<encodedText.size(); i++){
        encodedText[i] = quick_mode(encodedText[i], publicKey, N);
    }
    return encodedText;
}

string decode(vector<ull> encodedText, KeyPair kp){
    ull privateKey = kp.privateKey;
    ull N = kp.N;
    
    for(int i = 0; i<encodedText.size(); i++){
        encodedText[i] = quick_mode(encodedText[i], privateKey, N);
    }
    
    string decodedText;
    for(auto& c: encodedText){
        decodedText.push_back((int)c);
    }
    return decodedText;
}

vector<ull> encode_2(string text, KeyPair kp){
    ull publicKey = kp.publicKey;
    ull N = kp.N;
    vector<ull> encodedText;
//    for(auto& c: text){
//        encodedText.push_back((ull)c);
//    }
    for(int i = 0; i<text.size(); i += 6){
        ull temp = 0;
        for(int j = 0; j<6 && i+j<text.size(); j++){
            //temp <<= 8;
            temp += ((ull)text[i+j])<<8*(j);
            //cout<<hex<<temp<<endl;
        }
        //cout<<hex<<temp<<endl;
        encodedText.push_back(temp);
    }
    for(int i = 0; i<encodedText.size(); i++){
        encodedText[i] = quick_mode(encodedText[i], publicKey, N);
    }
    return encodedText;
}

string decode_2(vector<ull> encodedText, KeyPair kp){
    ull privateKey = kp.privateKey;
    ull N = kp.N;
    
    for(int i = 0; i<encodedText.size(); i++){
        encodedText[i] = quick_mode(encodedText[i], privateKey, N);
    }
    
    string decodedText;
//    for(auto& c: encodedText){
//        decodedText.push_back((int)c);
//    }
    for(int i = 0; i<encodedText.size(); i++){
        for(int j = 0; j<6; j++){
            char c = (char)encodedText[i];
            if(c == 0)
                break;
            decodedText.push_back(c);
            encodedText[i] >>= 8;
        }
    }
    return decodedText;
}
