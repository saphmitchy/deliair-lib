#pragma once
#include "template.hpp"

using ld = long double;
using comp = complex<ld>;

struct FFT {
    const ld pi = acos(-1.0);
    vector<comp> r, ir;

    FFT() {
        r.resize(30), ir.resize(30);
        rep(i, 30) {
            r[i] = -polar(ld(1), pi / (1 << (i + 1)));
            ir[i] = -polar(ld(1), -pi / (1 << (i + 1)));
        }
    }

    vector<comp> to_comp(vector<ll> a) {
        int n = sz(a);
        vector<comp> b(n);
        rep(i, n) b[i] = comp(a[i], 0);
        return b;
    }

    vector<ll> to_ll(vector<comp> a) {
        int n = sz(a);
        vector<ll> b(n);
        rep(i, n) b[i] = a[i].real() + 0.1;
        return b;
    }

    void fft(vector<comp> &a) {
        int n = sz(a);
        for (int k = n; k >>= 1;) {
            comp w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    comp x = a[i], y = w * a[j];
                    a[i] = x + y, a[j] = x - y;
                }
                w *= r[__builtin_ctz(++t)];
            }
        }
    }

    void ifft(vector<comp> &a) {
        int n = sz(a);
        for (int k = 1; k < n; k <<= 1) {
            comp w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    comp x = a[i], y = a[j];
                    a[i] = x + y, a[j] = w * (x - y);
                }
                w *= ir[__builtin_ctz(++t)];
            }
        }
        rep(i, n) a[i] /= n;
    }

    vector<ll> convolve(vector<ll> a, vector<ll> b) {
        if (empty(a) || empty(b)) return {};
        int k = sz(a) + sz(b) - 1, n = 1;
        while (n < k) n <<= 1;
        a.resize(n), b.resize(n);
        vector<comp> A = to_comp(a), B = to_comp(b);
        fft(A), fft(B);
        rep(i, n) A[i] *= B[i];
        ifft(A);
        a = to_ll(A);
        a.resize(k);
        return a;
    }
};