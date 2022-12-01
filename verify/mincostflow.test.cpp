#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja"

#include "../src/MinCostFlow.hpp"

int main() {
    int n, m;
    ll f;
    cin >> n >> m >> f;

    MinCostFlow G(n);
    rep(i, m) {
        int u, v;
        ll c, d;
        cin >> u >> v >> c >> d;
        G.add_edge(u, v, c, d);
    }

    ll ans = G.mcf(0, n - 1, f);
    cout << (ans == -(1LL << 60) ? -1 : ans) << '\n';
}