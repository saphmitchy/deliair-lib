#pragma once
#include "template.hpp"

using ull = unsigned long long;
const ull mod = (1LL << 61) - 1;

namespace Hash {
ull getmod(ull x) {
    ull ret = (x >> 61) + (x & mod);
    if (ret >= mod) ret -= mod;
    return ret;
}

ull mul(ull x, ull y) {
    x = getmod(x), y = getmod(y);
    ull x1 = x >> 31;
    ull x2 = x & ((1LL << 31) - 1);
    ull y1 = y >> 31;
    ull y2 = y & ((1LL << 31) - 1);
    ull z = x1 * y2 + x2 * y1;
    ull z1 = z >> 30;
    ull z2 = z & ((1LL << 30) - 1);
    return getmod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
}
} // namespace Hash

// 0 が含まれないように
template <typename T>
struct RollingHash {
    const int n;
    const ull b; // 基数
    vector<ull> h, p;

    //                          b = 887'446'835'055'281'585
    RollingHash(const T &s, ull b = 887446835055281585) : n(sz(s)), b(b) {
        h.assign(n + 1, 0), p.assign(n + 1, 1);
        rep(i, n) {
            p[i + 1] = Hash::mul(p[i], b);
            h[i + 1] = Hash::mul(h[i], b) + s[i];
            if (h[i + 1] >= mod) h[i + 1] -= mod;
        }
    }

    // 文字列の [l,r) の部分のハッシュ値
    ull get_hash(int l, int r) const {
        ull ret = h[r] + mod - Hash::mul(h[l], p[r - l]);
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