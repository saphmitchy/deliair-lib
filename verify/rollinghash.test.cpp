#define PROBLEM  "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include "../src/RollingHash.hpp"

int main() {
    string t, p; cin >> t >> p;
    RollingHash rh1(t);
    auto h1 = rh1.get_hash(p);
    auto ps = p.size();

    rep(i,t.size() - ps + 1) {
        if(eq(h1, rh1.get_hash(i, i + ps))) {
            cout << i << endl;
        }
    }
}