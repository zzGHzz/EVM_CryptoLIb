//
// Created by 王星凯 on 2019-08-16.
//

#ifndef EVM_CRYPTOLIB_POINT_H
#define EVM_CRYPTOLIB_POINT_H

#endif //EVM_CRYPTOLIB_POINT_H

#include <string>

#include <openssl/ec.h>

using namespace std;

class Point {
public:
    string P, G, G_compressed, ORDER;
    Point() {}
    ~Point() {}
    virtual vector<unsigned char> toBin() const = 0;
    virtual const EC_GROUP* getGroup() const = 0;
    virtual const EC_POINT* getPoint() const = 0;
    virtual void set_ng(const vector<unsigned char> &n) = 0;
    virtual void set_O() = 0;
    virtual bool is_O() const = 0;

private:
    EC_GROUP* group;
    EC_POINT* point;
    BN_CTX* ctx;
};