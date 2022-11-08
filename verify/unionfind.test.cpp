#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../src/UnionFind.hpp"

int main() {
    int n, q; cin >> n >> q;
    UnionFind uf(n);
    rep(i,q) {
        int t, u, v;
        cin >> t >> u >> v;
        if(t == 0) {
            uf.unite(u, v);
        } else {
            cout << (uf.same(u, v) ? 1 : 0) << endl;
        }
    }
}
