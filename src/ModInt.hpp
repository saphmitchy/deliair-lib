#pragma once
#include "template.hpp"

template <int mod>
struct modint {
    int x;

    modint() : x(0) {}

    modint(ll y) {
        x = y % mod;
        if (x < 0) x += mod;
    }

    static int get_mod() { return mod; }

    modint &operator+=(modint p) {
        x += p.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    modint &operator-=(modint p) {
        x -= p.x;
        if (x < 0) x += mod;
        return *this;
    }

    modint &operator*=(modint p) {
        x = (1LL * x * p.x) % mod;
        return *this;
    }

    modint &operator/=(modint p) {
        *this *= p.inverse();
        return *this;
    }

    modint operator-() { return modint(-x); }

    modint operator+(modint p) { return modint(*this) += p; }

    modint operator-(modint p) { return modint(*this) -= p; }

    modint operator*(modint p) { return modint(*this) *= p; }

    modint operator/(modint p) { return modint(*this) /= p; }

    bool operator==(modint p) { return x == p.x; }

    bool operator!=(modint p) { return x != p.x; }

    modint pow(ll k) {
        modint ret = 1, x = *this;
        while (k > 0) {
            if (k & 1) ret *= x;
            x *= x;
            k >>= 1;
        }
        return ret;
    }

    modint inv() { return pow(mod - 2); }

    friend ostream &operator<<(ostream &os, modint p) { return os << p.x; }

    friend istream &operator>>(istream &is, modint &p) {
        ll y;
        is >> y;
        p = modint(y);
        return is;
    }
};

using mint = modint<998244353>;
