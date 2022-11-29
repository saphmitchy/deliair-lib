#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../src/SCC.hpp"

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> es(n);
    rep(i, m) {
        int u, v;
        cin >> u >> v;
        es[u].eb(v);
    }

    auto comp = scc(es);

    int l = *max_element(all(comp)) + 1;
    vector<vector<int>> ids(l);
    rep(i, n) ids[comp[i]].eb(i);

    cout << l << '\n';
    rep(i, l) {
        cout << sz(ids[i]) << ' ';
        print(ids[i]);
    }
}
