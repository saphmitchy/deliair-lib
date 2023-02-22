#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "../src/TwoEdgeConnectedComponents.hpp"

int main() {
    int n, m;
    cin >> n >> m;
    Two_Edge_Connected_Components G(n);
    int u, v;
    rep(i, m) cin >> u >> v, G.add_edge(u, v);
    int k = sz(G.decompose());
    vector<vector<int>> ls(k);
    rep(i, n) ls[G[i]].eb(i);
    cout << k << endl;
    rep(i, k) cout << sz(ls[i]) << ' ', print(ls[i]);
}