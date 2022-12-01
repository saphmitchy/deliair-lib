#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../src/BipartiteMatching.hpp"

int main() {
    int l, r, m;
    cin >> l >> r >> m;

    BipartiteMatching G(l, r);

    rep(i, m) {
        int u, v;
        cin >> u >> v;
        G.add_edge(u, v);
    }

    cout << G.mm() << '\n';
    vector<pii> ans;
    rep(i, r) {
        if (G.match[i] != -1) cout << G.match[i] MM i << '\n';
    }
}