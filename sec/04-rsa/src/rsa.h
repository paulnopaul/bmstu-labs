#ifndef RSA_H
#define RSA_H

#include <cstdint>

#include "keys.h"

class RSA
{
public:
    RSA();
    explicit RSA(uint64_t newN);

    // TODO ADD ENCRYPT/DECRYPT

private:
    uint64_t _p, _q, _o, _N, _E, _D;
    PublicKey _pub;
    PrivateKey _pri;
    // TODO add keys;
};

#endif