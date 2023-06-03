#define PROBLEM  "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include "../src/RollingHash_ull.hpp"

int main() {
    string t, p; cin >> t >> p;
    RollingHash rh(t + p);
    int n = sz(t), m = sz(p);
    ull h = rh.get_hash(n, n + m);

    rep(i, n - m + 1) {
        if(h == rh.get_hash(i, i + m)) {
            cout << i << endl;
        }
    }
}