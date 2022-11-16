#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../src/NTT.hpp"
#include "../src/ModInt.hpp"

using mint = modint<998244353>;

int main() {
    NTT<mint> ntt;

    int n, m;
    cin >> n >> m;

    vector<mint> a(n), b(m);
    rep(i, n) cin >> a[i];
    rep(i, m) cin >> b[i];

    auto c = ntt.convolve(a, b);
    print(c);
}