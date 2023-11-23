#pragma once
#include "template.hpp"

template <typename T>
struct BIT {
    int n;
    vector<T> a;

    BIT(vector<T> v) : n(sz(v)) {
        a.assign(n + 1, 0);
        copy(all(v), begin(a) + 1);
        for (int i = 2; i <= n; i <<= 1) {
            for (int j = i; j <= n; j += i) a[j] += a[j - i / 2];
        }
    }

    BIT(int n, T x) : BIT(vector<T>(n, x)) {}

    void add(int i, T x) {
        for (i++; i <= n; i += (i & -i)) a[i] += x;
    }

    T sum(int i) {
        T ret = 0;
        for (; i > 0; i -= (i & -i)) ret += a[i];
        return ret;
    }

    T query(int l, int r) { return sum(r) - sum(l); }
};
