#include "template.hpp"

struct RollingHash {
    using ull = unsigned long long;

    static const ull MOD = 1'000'000'021;
    const int n;
    const ull b;

    vector<ull> hashed, pw;
    RollingHash(const string &s, ull base = 211)
    : n(s.size()), b(base), hashed(n + 1), pw(n + 1) {
        pw[0] = 1;
        rep(i,n) {
            pw[i+1] = pw[i] * b % MOD;
            hashed[i + 1] = hashed[i] * b % MOD + s[i];
            if(hashed[i + 1] >= MOD) hashed[i + 1] -= MOD;
        }
    }

    ull get_hash() {
        return hashed.back();
    }

    ull get_hash(int l, int r) {
        assert(0 <= l && l <= n);
        assert(0 <= r && r <= n);
        assert(l <= r);
        ull res = hashed[r] + MOD - hashed[l] * pw[r - l] % MOD;
        return res >= MOD ? res - MOD : res; 
    }

    ull get_hash(string &s) {
        ull res = 0;
        for(auto &i : s) {
            res = (res * b + i) % MOD;
        }
        return res;
    }
};