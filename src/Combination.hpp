#pragma once
#include "template.hpp"

template <typename T>
struct Combination {
    vector<T> _fac, _ifac;

    Combination(int n) {
        _fac.resize(n + 1), _ifac.resize(n + 1);
        _fac[0] = 1;
        rep(i, n) _fac[i + 1] = _fac[i] * (i + 1);
        _ifac[n] = _fac[n].inverse();
        per(i, n) _ifac[i] = _ifac[i + 1] * (i + 1);
    }

    // k!
    T fac(int k) { return _fac[k]; }

    // 1/k!
    T ifac(int k) { return _ifac[k]; }

    // 1/k
    T inv(int k) { return _fac[k - 1] * _ifac[k]; }

    // nPk
    T P(int n, int k) {
        if (k < 0 || n < k) return 0;
        return fac(n) * ifac(n - k);
    }

    // nCk ((n,k) = (-1,-1), (-1,0) の場合に注意)
    T C(int n, int k) {
        if (k < 0 || n < k) return 0;
        return fac(n) * ifac(k) * ifac(n - k);
    }
};