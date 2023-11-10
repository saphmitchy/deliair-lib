#pragma once
#include "template.hpp"

template <typename T, typename O>
struct LazySegmentTree {
    using F = function<T(T, T)>;
    using G = function<T(T, O)>;
    using H = function<O(O, O)>;
    vector<T> data;
    vector<O> lazy;
    int n;
    const F f;
    const G g;
    const H h;
    const T e1;
    const O e2;

    LazySegmentTree(vector<T> v, F f, G g, H h, T e1, O e2) : f(f), g(g), h(h), e1(e1), e2(e2) {
        int m = v.size();
        n = 1;
        while (n < m) n *= 2;
        data.assign(2 * n, e1);
        rep(i, m) data[n + i] = v[i];
        lazy.assign(2 * n, e2);
        per2(i, 1, n) data[i] = f(data[2 * i], data[2 * i + 1]);
    }

    LazySegmentTree(int m, T x, F f, G g, H h, T e1, O e2) : LazySegmentTree(vector<T>(m, x), f, g, h, e1, e2) {}

    T get(int k) { return g(data[k], lazy[k]); }

    void eval(int k) {
        data[k] = get(k);
        rep(i, 2) lazy[2 * k + i] = h(lazy[2 * k + i], lazy[k]);
        lazy[k] = e2;
    }

    T update(int l, int r, O x, int k = 1, int L = 0, int R = -1) {
        if (R == -1) R = n;
        // if の中身要注意！
        if (l >= r || r <= L || R <= l) return get(k);
        if (l <= L && R <= r) {
            lazy[k] = h(lazy[k], x);
            return get(k);
        }
        eval(k);
        int M = (L + R) / 2;
        return data[k] = f(update(l, r, x, 2 * k, L, M), update(l, r, x, 2 * k + 1, M, R));
    }

    T query(int l, int r, int k = 1, int L = 0, int R = -1) {
        if (R == -1) R = n;
        // if の中身要注意！
        if (l >= r || r <= L || R <= l) return e1;
        if (l <= L && R <= r) return get(k);
        eval(k);
        int M = (L + R) / 2;
        return f(query(l, r, 2 * k, L, M), query(l, r, 2 * k + 1, M, R));
    }
};
