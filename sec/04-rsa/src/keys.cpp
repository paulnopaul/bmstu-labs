#include "keys.h"

PrivateKey::PrivateKey(uint64_t n, uint64_t d)
{
}

bool PrivateKey::Check()
{
    return !(_N < 6 || _D < 2);
}

std::ostream &operator<<(std::ostream &os, const PrivateKey &key)
{
    os << key._N << "," << key._D;
    return os;
}

PublicKey::PublicKey(uint64_t n, uint64_t e)
{
}

bool PublicKey::Check()
{
    return !(_N < 6 || _E < 2);
}

std::ostream &operator<<(std::ostream &os, const PublicKey &key)
{
    os << key._N << "," << key._E;
    return os;
}