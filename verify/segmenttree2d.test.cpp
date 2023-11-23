#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../src/SegmentTree2D.hpp"
#include "../src/SegmentTree.hpp"

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> x(N), y(N);
    vector<ll> w(N);

    auto f = [](ll x, ll y) { return x + y; };

    SegmentTree2D<ll, int> seg(f, 0);

    rep(i, N) {
        cin >> x[i] >> y[i] >> w[i];
        seg.insert(x[i], y[i]);
    }

    vector<int> t(Q), lx(Q), ly(Q), rx(Q), ry(Q);
    vector<ll> c(Q);

    rep(i, Q) {
        cin >> t[i];
        if (t[i] == 0) {
            cin >> lx[i] >> ly[i] >> c[i];
            seg.insert(lx[i], ly[i]);
        } else {
            cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];
        }
    }

    seg.build();

    rep(i, N) seg.update(x[i], y[i], w[i], true);

    rep(i, Q) {
        if (t[i] == 0) {
            seg.update(lx[i], ly[i], c[i], true);
        } else {
            cout << seg.query(lx[i], rx[i], ly[i], ry[i]) << '\n';
        }
    }
}