#pragma once
#include "template.hpp"

using ull = unsigned long long;
const ull mod = (1LL << 61) - 1;

ull h_mod(ull x) {
    ull ret = (x >> 61) + (x & mod);
    return ret - (ret >= mod ? mod : 0);
}

ull h_mul(ull x, ull y) {
    x = h_mod(x), y = h_mod(y);
    ull x1 = x >> 31, x2 = x & ((1LL << 31) - 1), y1 = y >> 31, y2 = y & ((1LL << 31) - 1);
    ull z = x1 * y2 + x2 * y1, z1 = z >> 30, z2 = z & ((1 << 30) - 1);
    return h_mod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
}

// 0 が含まれないように
template <typename T>
struct RollingHash {
    const int n;
    const ull b; // 基数
    vector<ull> h, p;

    RollingHash(const T &s, ull b = 887'446'835'055'281'585) : n(sz(s)), b(b) {
        h.assign(n + 1, 0), p.assign(n + 1, 1);
        rep(i, n) {
            p[i + 1] = h_mul(p[i], b);
            h[i + 1] = h_mul(h[i], b) + s[i];
            if (h[i + 1] >= mod) h[i + 1] -= mod;
        }
    }

    // 文字列の [l,r) の部分のハッシュ値
    ull get_hash(int l, int r) const {
        ull ret = h[r] + mod - h_mul(h[l], p[r - l]);
        return ret - (ret >= mod ? mod : 0);
    }

    ull get_all_hash() const { return h[n]; }

    // s[l1:r1) と s[l2:r2) の辞書順大小比較 (-1 : <, 0 : =, 1 : >)
    int comp(int l1, int r1, int l2, int r2) {
        int l = 0, r = min(r1 - l1, r2 - l2) + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            (get_hash(l1, l1 + m) == get_hash(l2, l2 + m) ? l : r) = m;
        }
        if (r1 == l1 + l && r2 == l2 + l) return 0;
        if (r1 == l1 + l) return -1;
        if (r2 == l2 + l) return 1;
        return get_hash(l1 + l, l1 + l + 1) < get_hash(l2 + l, l2 + l + 1) ? -1 : 1;
    }
};