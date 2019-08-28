//
// Created by 王星凯 on 2019-08-08.
//

#ifndef EVM_CRYPTOLIB_SECP256K1_H
#define EVM_CRYPTOLIB_SECP256K1_H

#endif //EVM_CRYPTOLIB_SECP256K1_H

#include "point.h"

#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/pem.h>

using namespace std;

class Secp256k1_point : public Point {
public:
    Secp256k1_point() {
        P = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F";
        G = "0479BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8";
        G_compressed = "0279BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798";
        ORDER = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141";
        init();
    }
    Secp256k1_point(const Secp256k1_point& src);
    Secp256k1_point(const vector<unsigned char>& bytes);
    ~Secp256k1_point();

    const EC_GROUP* getGroup() const {
        return group;
    }
    const EC_POINT* getPoint() const {
        return point;
    }

    vector<unsigned char> toBin() const;

    Secp256k1_point& operator=(const Secp256k1_point& rhs);
    Secp256k1_point& operator+=(const Secp256k1_point& rhs);
    Secp256k1_point& operator*=(const vector<unsigned char>& rhs);
    const Secp256k1_point operator+(const Secp256k1_point& rhs) const {
        return Secp256k1_point(*this) += rhs;
    }
    const Secp256k1_point operator*(const vector<unsigned char>& rhs) const {
        return Secp256k1_point(*this) *= rhs;
    }
    void set_ng(const vector<unsigned char>& n);
    void set_O();
    bool is_O() const {
        return EC_POINT_is_at_infinity(group, point);
    };

    protected:
    void init();

    private:
    EC_GROUP* group;
    EC_POINT* point;
    BN_CTX* ctx;
};