// ローリングハッシュ。簡単のためMODを1e9程度に固定している。
// 誕生日のパラドックスよりこれでは弱い可能性があるのに注意。
// stringは適宜vectorに入れ替えてもよい。
// get_hash()は必要なものだけ記述するとよい。
// hash(s) = \sum{i = 0...n-1} s[i] * b^(n - i - 1)
//         = \sum{i = 0...n-1} s[i] * pw[n - i - 1]
#pragma once
#include "template.hpp"

struct RollingHash {
    using ull = unsigned long long;

    static const ull MOD = 1e9 + 21;
    const int   n;  // 文字列の長さ
    const ull   b;  // 基数
    vector<ull> hs, // sh[i] = s[0, i) のハッシュ値
                pw; // pw[i]   = b^i

    RollingHash(const string &s, ull base = 211)
        : n(s.size()), b(base), hs(n + 1), pw(n + 1, 1) {
        rep(i, n) {
            pw[i + 1] = pw[i] * b % MOD;
            hs[i + 1] = hs[i] * b % MOD + s[i];
            if (hs[i + 1] >= MOD) hs[i + 1] -= MOD;
        }
    }

    ull get_hash() { return hs.back(); } // s全体のハッシュ値を返す。

    ull get_hash(int l, int r) { // s[l, r)のハッシュ値を返す。
        assert(0 <= l && l <= n);  // 省略可
        assert(0 <= r && r <= n);  // 省略可
        assert(l <= r);            // 省略可
        ull res = hs[r] + MOD - hs[l] * pw[r - l] % MOD;
        return res >= MOD ? res - MOD : res;
    }

    // 現在のbaseを使って与えられた文字列のハッシュ値を計算する。
    ull get_hash(const string &s) {
        ull res = 0;
        for (auto &i : s) res = (res * b + i) % MOD;
        return res;
    }
};