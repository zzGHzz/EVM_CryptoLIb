//
// Created by 王星凯 on 2019-08-08.
//

#include "include/secp256k1.h"

#include <string>
#include <cassert>
#include <iostream>

using namespace std;

void secp256k1_point::init()
{
    group = NULL;
    point = NULL;
    ctx   = NULL;

    group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    if (!group) {
        throw runtime_error("secp256k1_point::init(): NEW CURVE GENERATED FAILED!!");
    }

    point = EC_POINT_new(group);
    if (!point) {
        EC_GROUP_free(group);
        throw runtime_error("secp256k1_point::init(): NEW POINT GENERATED FAILED!!");
    }

    ctx = BN_CTX_new();
    if (!ctx) {
        EC_GROUP_free(group);
        EC_POINT_free(point);
        throw runtime_error("secp256k1_point::init(): BN_CTX_new FAILED!!");
    }

    return;
}

secp256k1_point::secp256k1_point(const secp256k1_point& source)
{
    init();
    if (!EC_GROUP_copy(group, source.group)) throw std::runtime_error("secp256k1_point::secp256k1_point(const secp256k1_point&) - EC_GROUP_copy failed.");
    if (!EC_POINT_copy(point, source.point)) throw std::runtime_error("secp256k1_point::secp256k1_point(const secp256k1_point&) - EC_POINT_copy failed.");
}

secp256k1_point::secp256k1_point(const bytes_t& bytes)
{
    init();
    this->bytes(bytes);
}


secp256k1_point::~secp256k1_point()
{
    if (point) EC_POINT_free(point);
    if (group) EC_GROUP_free(group);
    if (ctx)   BN_CTX_free(ctx);
}

secp256k1_point& secp256k1_point::operator=(const secp256k1_point& rhs)
{
    if (!EC_GROUP_copy(group, rhs.group)) throw std::runtime_error("secp256k1_point::operator= - EC_GROUP_copy failed.");
    if (!EC_POINT_copy(point, rhs.point)) throw std::runtime_error("secp256k1_point::operator= - EC_POINT_copy failed.");

    return *this;
}

void secp256k1_point::bytes(const bytes_t& bytes)
{
    std::string err;

    EC_POINT* rval;

    BIGNUM* bn = BN_bin2bn(&bytes[0], bytes.size(), NULL);
    if (!bn) {
        err = "BN_bin2bn failed.";
        goto finish;
    }

    rval = EC_POINT_bn2point(group, bn, point, ctx);
    if (!rval) {
        err = "EC_POINT_bn2point failed.";
        goto finish;
    }

    finish:
    if (bn) BN_clear_free(bn);

    if (!err.empty()) {
        throw std::runtime_error(std::string("secp256k1_point::set() - ") + err);
    }
}

bytes_t secp256k1_point::bytes() const
{
    bytes_t bytes(33);

    std::string err;

    BIGNUM* rval;

    BIGNUM* bn = BN_new();
    if (!bn) {
        err = "BN_new failed.";
        goto finish;
    }

    rval = EC_POINT_point2bn(group, point, POINT_CONVERSION_COMPRESSED, bn, ctx);
    if (!rval) {
        err = "EC_POINT_point2bn failed.";
        goto finish;
    }

    assert(BN_num_bytes(bn) == 33);
    BN_bn2bin(bn, &bytes[0]);

    finish:
    if (bn) BN_clear_free(bn);

    if (!err.empty()) {
        throw std::runtime_error(std::string("secp256k1_point::get() - ") + err);
    }

    return bytes;
}

secp256k1_point& secp256k1_point::operator+=(const secp256k1_point& rhs)
{
    if (!EC_POINT_add(group, point, point, rhs.point, ctx)) {
        throw std::runtime_error("secp256k1_point::operator+= - EC_POINT_add failed.");
    }
    return *this;
}

secp256k1_point& secp256k1_point::operator*=(const bytes_t& rhs)
{
    BIGNUM* bn = BN_bin2bn(&rhs[0], rhs.size(), NULL);
    if (!bn) {
        throw std::runtime_error("secp256k1_point::operator*=  - BN_bin2bn failed.");
    }

    int rval = EC_POINT_mul(group, point, NULL, point, bn, ctx);
    BN_clear_free(bn);

    if (rval == 0) {
        throw std::runtime_error("secp256k1_point::operator*=  - EC_POINT_mul failed.");
    }

    return *this;
}

// Computes n*G + K where K is this and G is the group generator
void secp256k1_point::generator_mul(const bytes_t& n)
{
    BIGNUM* bn = BN_bin2bn(&n[0], n.size(), NULL);
    if (!bn) throw std::runtime_error("secp256k1_point::generator_mul  - BN_bin2bn failed.");

    //int rval = EC_POINT_mul(group, point, bn, (is_at_infinity() ? NULL : point), BN_value_one(), ctx);
    int rval = EC_POINT_mul(group, point, bn, point, BN_value_one(), ctx);
    BN_clear_free(bn);

    if (rval == 0) throw std::runtime_error("secp256k1_point::generator_mul - EC_POINT_mul failed.");
}

// Sets to n*G
void secp256k1_point::set_generator_mul(const bytes_t& n)
{
    BIGNUM* bn = BN_bin2bn(&n[0], n.size(), NULL);
    if (!bn) throw std::runtime_error("secp256k1_point::set_generator_mul  - BN_bin2bn failed.");

    int rval = EC_POINT_mul(group, point, bn, NULL, NULL, ctx);
    BN_clear_free(bn);

    if (rval == 0) throw std::runtime_error("secp256k1_point::set_generator_mul - EC_POINT_mul failed.");
}

