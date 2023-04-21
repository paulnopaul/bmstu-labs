#ifndef KEYS_H
#define KEYS_H

#include <cstdint>
#include <ostream>

class PrivateKey
{
public:
    PrivateKey() = default;
    PrivateKey(uint64_t n, uint64_t d);

    bool Check();

    friend std::ostream &operator<<(std::ostream &os, const PrivateKey &key);

private:
    uint64_t _N, _D;
};

class PublicKey
{
public:
    PublicKey() = default;
    PublicKey(uint64_t n, uint64_t e);

    bool Check();

    friend std::ostream &operator<<(std::ostream &os, const PublicKey &key);

private:
    uint64_t _N, _E;
};

#endif
