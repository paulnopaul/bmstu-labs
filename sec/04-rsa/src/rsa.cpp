#include "rsa.h"

#include <chrono>
#include <iostream>
#include <cstdint>
#include <exception>
#include <unordered_map>

#include "mymath.h"
#include "keys.h"

RSA::RSA()
{
}

RSA::RSA(uint64_t newN)
{
    int64_t nowNanoseconds = std::chrono::system_clock::now().time_since_epoch().count();
    int64_t n = int64_t(nowNanoseconds / 1e6) % (1000 + int64_t(newN)) + 13; // WTF
    auto ps = getNPrimes(n);
    size_t l = ps.size();
    if (l == 0)
    {
        throw std::runtime_error("l can't be 0");
    }
    auto psm = std::unordered_map<uint64_t, bool>();
    for (const uint64_t value : ps)
    {
        psm[value] = true;
    }
    uint64_t p = 0, q = 0;
    for (const auto [k, _] : psm)
    {
        if (!(k < 5 || k == p))
        {
            q = k;
        }
    }

    _p = p;
    _q = q;
    _o = (p - 1) * (q - 1);
    _N = p * q;

    auto tps = getNPrimes(_o);
    auto tpsm = std::unordered_map<uint64_t, bool>();
    for (const uint64_t value : tps)
    {
        tpsm[value] = true;
    }

    for (const auto [t, _] : psm)
    {
        if (gcd(t, p - 1) == 1 && gcd(t, q - 1) == 1)
        {
            _E = t;
        }
    }

    for (auto i = _o / _E; i < _o; ++i)
    {
        if (_E * i % _o == 1) // WTF
        {
            _D = i;
            break;
        }
    }

    this->_pub = PublicKey(_N, _E);
    this->_pri = PrivateKey(_N, _D);
}
