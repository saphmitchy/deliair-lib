#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include "../src/Hungarian.hpp"

int main() {
    int n;
    cin >> n;

    vector<vector<ll>> a(n, vector<ll>(n));
    rep(i, n) rep(j, n) cin >> a[i][j];

    auto [s, p] = hungarian(a);
    cout << s << '\n';
    print(p);
}