#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../src/LazySegmentTree.hpp"

int main() {
    int n, q;
    cin >> n >> q;

    auto f = [](pll a, pll b) { return pll((a.first + b.first) % MOD, (a.second + b.second) % MOD); };
    auto g = [](pll a, pll b) { return pll((a.first * b.first + a.second * b.second) % MOD, a.second); };
    auto h = [](pll a, pll b) { return pll(a.first * b.first % MOD, (a.second * b.first + b.second) % MOD); };

    vector<pll> p(n);
    rep(i, n) {
        cin >> p[i].first;
        p[i].second = 1;
    }

    LazySegmentTree<pll, pll> seg(p, f, g, h, pll(0, 0), pll(1, 0));

    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            ll a, b;
            cin >> a >> b;
            seg.apply(l, r, pll(a, b));
        } else {
            cout << seg.query(l, r).first << '\n';
        }
    }
}
