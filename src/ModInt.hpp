#pragma once
#include "template.hpp"

template <ll mod>
struct modint {
    ll x;

    modint() : x(0) {}

    modint(ll y) {
        x = y % mod;
        if (x < 0) x += mod;
    }

    // NTT を使うときに必要
    static ll get_mod() { return mod; }

    modint &operator+=(modint p) {
        x += p.x;
        x %= mod;
        return *this;
    }

    modint &operator-=(modint p) {
        x += mod - p.x;
        x %= mod;
        return *this;
    }

    modint &operator*=(modint p) {
        x *= p.x;
        x %= mod;
        return *this;
    }

    modint &operator/=(modint p) {
        *this *= p.inverse();
        return *this;
    }

    modint operator-() { return modint(-x); }
    modint operator+(modint p) const { return modint(*this) += p; } // const つけないと print で使えないという罠
    modint operator-(modint p) { return modint(*this) -= p; }
    modint operator*(modint p) { return modint(*this) *= p; }
    modint operator/(modint p) { return modint(*this) /= p; }
    bool operator==(modint p) { return x == p.x; }
    bool operator!=(modint p) { return x != p.x; }

    modint pow(ll k) {
        modint now = *this, ret = 1;
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    modint inverse() {
        assert(x != 0);
        return pow(mod - 2);
    }

    friend ostream &operator<<(ostream &os, modint p) { return os << p.x; }

    friend istream &operator>>(istream &is, modint &p) {
        ll y;
        is >> y;
        p = modint(y);
        return is;
    }
};