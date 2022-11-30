// ローリングハッシュ。簡単のためMODを1e9程度に固定している。
// 誕生日のパラドックスよりこれでは弱い可能性があるのに注意。
// stringは適宜vectorに入れ替えてもよい。
// **ハッシュ値の比較は**必ず`eq`で行うこと！
// get_hash()は必要なものだけ記述するとよい。
// hash(s) = \sum{i = 0...n-1} s[i] * b^(n - i - 1)
//         = \sum{i = 0...n-1} s[i] * pw[n - i - 1]
#pragma once
#include "template.hpp"

using vul = valarray<size_t>; // ハッシュ値の型
using ull = uint64_t;

// L: valarrayの長さ
template<ull L = 3, ull mod = 1000000021>
struct RollingHash {

    const int   n;  // 文字列の長さ
    const vul   b;  // 基数
    vector<vul> hs, // hs[i] = s[0, i) のハッシュ値
                pw; // pw[i]   = b^i

    RollingHash(const string &s, vul base = {211, 341, 455})
        : n(s.size()), b(base), hs(n + 1, vul(L)), pw(n + 1, vul(1, L)) {
        assert(b.size() == L); // 省略可
        rep(i, n) {
            pw[i + 1] = pw[i] * b % mod;
            hs[i + 1] = (hs[i] * b + s[i]) % mod;
        }
    }
    
    // s全体のハッシュ値を返す。
    vul get_hash() { return hs.back(); }

    // s[l, r)のハッシュ値を返す。
    vul get_hash(int l, int r) {
        assert(0 <= l && l <= n);  // 省略可
        assert(0 <= r && r <= n);  // 省略可
        assert(l <= r);            // 省略可
        vul res = hs[r] + mod - hs[l] * pw[r - l] % mod;
        return res.apply([](ull x){
            return x >= mod ? x - mod : x;
        });
    }

    // 現在のbaseを使って与えられた文字列のハッシュ値を計算する。
    vul get_hash(const string &s) {
        vul res(L);
        // `for (auto &i : s) res = (res * base + i) % mod;
        // これだとなぜかバグる（HELP！）
        for (auto &i : s) {
            res *= b;
            res += i;
            res %= mod;
        }
        return res;
    }
};

// ハッシュ値の比較を行う
bool eq(const vul &a, const vul &b) {
    valarray<bool> c = a == b;
    return all_of(all(c), [](bool x){ return x; });
}
