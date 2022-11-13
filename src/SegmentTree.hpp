#pragma once
#include "template.hpp"

template <typename T>
struct SegmentTree {
    using F = function<T(T, T)>;
    vector<T> data;
    int n;
    const F f;
    const T e;

    SegmentTree(vector<T> v, F f, T e) : f(f), e(e) {
        int m = v.size();
        n = 1;
        while (n < m) n *= 2;
        data.assign(2 * n, e);
        rep(i, m) data[n + i] = v[i];
        per2(i, 1, n) data[i] = f(data[2 * i], data[2 * i + 1]);
    }

    SegmentTree(int m, T x, F f, T e) : SegmentTree(vector<T>(m, x), f, e) {}

    // update : true なら data[i] <- x, false なら data[i] <- f(data[i], x)
    void change(int i, T x, bool update = true) {
        i += n;
        data[i] = (update ? x : f(data[i], x));
        while (i > 1) {
            i /= 2;
            data[i] = f(data[2 * i], data[2 * i + 1]);
        }
    }

    T query(int l, int r, int k = 1, int L = 0, int R = -1) {
        if (R == -1) R = n;
        if (r <= L || R <= l) return e;
        if (l <= L && R <= r) return data[k];
        int M = (L + R) / 2;
        return f(query(l, r, 2 * k, L, M), query(l, r, 2 * k + 1, M, R));
    }

    T operator[](int i) { return data[i]; }
};