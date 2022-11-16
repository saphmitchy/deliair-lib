#pragma once
#include "template.hpp"

template <typename T>
struct NTT {
    T root;
    vector<T> r, ir;

    NTT(int root = 3) : root(root) {
        ll mod = T::get_mod();
        r.resize(30), ir.resize(30);
        rep(i, 30) {
            r[i] = -T(root).pow((mod - 1) >> (i + 2)); // i+2 に注意
            ir[i] = r[i].inverse();
        }
    }

    void ntt(vector<T> &a) {
        int n = sz(a);
        for (int k = n; k >>= 1;) { // intt と違うとこ
            T w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    T x = a[i], y = w * a[j];   // intt と違うとこ
                    a[i] = x + y, a[j] = x - y; // intt と違うとこ
                }
                w *= r[__builtin_ctz(++t)]; // intt と違うとこ
            }
        }
    }

    void intt(vector<T> &a) {
        int n = sz(a);
        for (int k = 1; k < n; k <<= 1) { // ntt と違うとこ
            T w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    T x = a[i], y = a[j];             // ntt と違うとこ
                    a[i] = x + y, a[j] = w * (x - y); // ntt と違うとこ
                }
                w *= ir[__builtin_ctz(++t)]; // ntt と違うとこ
            }
        }
        T inv = T(n).inverse();
        rep(i, n) a[i] *= inv; // ntt と違うとこ
    }

    vector<T> convolve(vector<T> a, vector<T> b) {
        if (a.empty() || b.empty()) return {};
        int k = sz(a) + sz(b) - 1, n = 1;
        while (n < k) n *= 2;
        a.resize(n), b.resize(n);
        ntt(a), ntt(b);
        rep(i, n) a[i] *= b[i];
        intt(a);
        a.resize(k);
        return a;
    }
};