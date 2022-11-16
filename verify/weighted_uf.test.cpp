#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"

#include "../src/Weighted_uf.hpp"

int main() {
    int n, q; cin >> n >> q;
    Weighted_uf<int> uf(n);
    rep(i,q) {
        int id; cin >> id;
        if(id == 0) {
            int x, y, z; cin >> x >> y >> z;
            uf.unite(y, x, z);
        } else {
            int x, y; cin >> x >> y;
            if(uf.same(x, y)) {
                cout << uf.diff(y, x) << endl;
            } else {
                cout << "?" << endl;
            }
        }
    }
}