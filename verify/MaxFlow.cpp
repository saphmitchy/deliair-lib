#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include "../src/MaxFlow.hpp"

int main() {
    int n, m;
    cin >> n >> m;

    MaxFlow G(n);
    rep(i, m) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.mf(0, n - 1) << '\n';
}