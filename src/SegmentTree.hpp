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

    // apply : false なら data[i] <- x, true なら data[i] <- f(data[i], x)
    void update(int i, T x, bool apply = false) {
        i += n;
        data[i] = (apply ? f(data[i], x) : x);
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

    // comp(query[l,r]) = true となるような最小の r (存在しなければ n(2 べき))
    template <typename C>
    int find_first(int l, C comp, T &x, int k = 1, int L = 0, int R = -1) {
        if (R == -1) R = n;
        if (R <= l) return n;
        if (l <= L) {
            if (!comp(f(x, data[k]))) {
                x = f(x, data[k]);
                return n;
            }
            if (R - L == 1) return L;
        }
        int M = (L + R) / 2;
        int r = find_first(l, comp, x, 2 * k, L, M);
        return (r == n ? find_first(l, comp, x, 2 * k + 1, M, R) : r);
    }

    template <typename C>
    int find_first(int l, C comp) {
        T x = e;
        return find_first(l, comp, x);
    }

    // comp(query[l,r)) = true となるような最大の r (存在しなければ -1)
    template <typename C>
    int find_last(int r, C comp, T &x, int k = 1, int L = 0, int R = -1) {
        if (R == -1) R = n;
        if (r <= L) return -1;
        if (R <= r) {
            if (!comp(f(data[k], x))) {
                x = f(data[k], x);
                return -1;
            }
            if (R - L == 1) return L;
        }
        int M = (L + R) / 2;
        int l = find_last(r, comp, x, 2 * k + 1, M, R);
        return (l == -1 ? find_last(r, comp, x, 2 * k, L, M) : l);
    }

    template <typename C>
    int find_last(int r, C comp) {
        T x = e;
        return find_last(r, comp, x);
    }
};