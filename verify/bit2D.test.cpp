#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../src/BIT.hpp"
#include "../src/BIT2D.hpp"

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> x(N), y(N);
    vector<ll> w(N);

    BIT2D<ll, int> bit;

    rep(i, N) {
        cin >> x[i] >> y[i] >> w[i];
        bit.insert(x[i], y[i]);
    }

    vector<int> t(Q), lx(Q), ly(Q), rx(Q), ry(Q);
    vector<ll> c(Q);

    rep(i, Q) {
        cin >> t[i];
        if (t[i] == 0) {
            cin >> lx[i] >> ly[i] >> c[i];
            bit.insert(lx[i], ly[i]);
        } else {
            cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];
        }
    }

    bit.build();

    rep(i, N) bit.add(x[i], y[i], w[i]);

    rep(i, Q) {
        if (t[i] == 0) {
            bit.add(lx[i], ly[i], c[i]);
        } else {
            cout << bit.query(lx[i], rx[i], ly[i], ry[i]) << '\n';
        }
    }
}