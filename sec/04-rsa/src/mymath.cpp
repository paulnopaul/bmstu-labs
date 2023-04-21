#include "mymath.h"

#include <utility>

std::vector<uint64_t> getNPrimes(uint64_t n)
{
    auto ps = std::vector<uint64_t>();
    if (n < 2)
    {
        return ps;
    }

    auto N = std::vector<bool>(n + 1);
    for (uint64_t i = 2, l = sqrt(double(n)); i <= l; ++i)
    {
        if (!N[i])
        {
            for (uint64_t j = 2; i * j <= n; ++j)
            {
                N[i * j] = true;
            }
        }
    }

    for (uint64_t i = 2, l = n + 1; i < l; ++i)
    {
        if (!N[i])
        {
            ps.push_back(i);
        }
    }
    return ps;
}

uint64_t gcd(uint64_t m, uint64_t n)
{
    if (m < n)
    {
        std::swap(m, n);
    }

    if (n == 0)
    {
        return m;
    }

    return gcd(n, m % n);
}
