#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../src/SegmentTree.hpp"

int main() {
    int n, q;
    cin >> n >> q;

    auto f = [](pll a, pll b) { return pll(a.first * b.first % MOD, (b.first * a.second + b.second) % MOD); };

    vector<pll> p(n);
    rep(i, n) cin >> p[i].first >> p[i].second;

    SegmentTree<pll> seg(p, f, pll(1, 0));

    while (q--) {
        int t;
        cin >> t;

        if (t == 0) {
            int i;
            pll q;
            cin >> i >> q.first >> q.second;
            seg.update(i, q);
        } else {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            auto [a, b] = seg.query(l, r);
            cout << (a * x + b) % MOD << '\n';
        }
    }
}
