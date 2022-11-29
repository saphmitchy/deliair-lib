#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include "../src/Dijkstra.hpp"

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pll>> es(n);
    rep(i, m) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        es[u].eb(v, c);
    }

    auto d = dijkstra(es, s);
    rep(i, n) {
        if (d[i] == (1LL << 60)) {
            cout << "INF\n";
        } else {
            cout << d[i] << '\n';
        }
    }
}