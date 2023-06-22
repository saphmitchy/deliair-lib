#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"

#include "../src/Rerooting.hpp"

int main() {
    int n;
    cin >> n;
    Rerooting<int, int> g(n, [](int x, int y){return max(x, y);}, [](int x, int w){return x + w;}, 0, vector<int>(n, 0));
    int u, v;
    rep(i, n - 1) cin >> u >> v, u--, v--, g.add_edge(u, v, 1);
    auto ret = g.solve();
    rep(i, n) cout << 2 * (n - 1) - ret[i] << '\n';
}