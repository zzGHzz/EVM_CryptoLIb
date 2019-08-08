//
// Created by 王星凯 on 2019-08-08.
//

#ifndef EVM_CRYPTOLIB_SECP256K1_H
#define EVM_CRYPTOLIB_SECP256K1_H

#endif //EVM_CRYPTOLIB_SECP256K1_H

#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/ec.h>

using namespace std;

//class secp256k1_key
//{
//    public:
//    secp256k1_key();
//    ~secp256k1_key() { EC_KEY_free(pKey); }
//
//    EC_KEY* getKey() const { return bSet ? pKey : nullptr; }
//    EC_KEY* newKey();
//    bytes_t getPrivKey() const;
//    EC_KEY* setPrivKey(const bytes_t& privkey);
//    bytes_t getPubKey(bool bCompressed = true) const;
//    EC_KEY* setPubKey(const bytes_t& pubkey);
//
//    private:
//    EC_KEY* pKey;
//    bool bSet;
//};


//class secp256k1_point
//{
//
//    public:
//    secp256k1_point() { init(); }
//    secp256k1_point(const secp256k1_point& source);
//    secp256k1_point(const bytes_t& bytes);
//    ~secp256k1_point();
//
//    secp256k1_point& operator=(const secp256k1_point& rhs);
//
//    void bytes(const bytes_t& bytes);
//    bytes_t bytes() const;
//
//    secp256k1_point& operator+=(const secp256k1_point& rhs);
//    secp256k1_point& operator*=(const bytes_t& rhs);
//
//    const secp256k1_point operator+(const secp256k1_point& rhs) const   { return secp256k1_point(*this) += rhs; }
//    const secp256k1_point operator*(const bytes_t& rhs) const           { return secp256k1_point(*this) *= rhs; }
//
//    // Computes n*G + K where K is this and G is the group generator
//    void generator_mul(const bytes_t& n);
//
//    // Sets to n*G
//    void set_generator_mul(const bytes_t& n);
//
//    bool is_at_infinity() const { return EC_POINT_is_at_infinity(group, point); }
//    void set_to_infinity() { EC_POINT_set_to_infinity(group, point); }
//
//    const EC_GROUP* getGroup() const { return group; }
//    const EC_POINT* getPoint() const { return point; }
//
//    protected:
//    void init();
//
//    private:
//    EC_GROUP* group;
//    EC_POINT* point;
//    BN_CTX*   ctx;
//};

class secp256k1_point {
    public:
    secp256k1_point() {
        init();
    }
    secp256k1_point(const string& bytes);
    ~secp256k1_point();

    const EC_GROUP* getGroup() const {
        return group;
    }
    const EC_POINT* getPoint() const {
        return point;
    }

    secp256k1_point& operator=(const secp256k1_point& rhs);
    secp256k1_point& operator+=(const secp256k1_point& rhs);
    secp256k1_point& operator*=(const secp256k1_point& rhs);
    const secp256k1_point operator+(const secp256k1_point& rhs) const {
        return secp256k1_point(*this) += rhs;
    }
    const secp256k1_point operator*(const string& rhs) const {
        return secp256k1_point(*this) *= rhs;
    }
    void set_ng(const string& n);
    void set_O();
    bool is_O const {
        return EC_POINT_is_at_ifinity(group, point);
    };

    protected:
    void init();

    private:
    EC_GROUP* group;
};