#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B&lang=ja"

#include "../src/Combination.hpp"
#include "../src/ModInt.hpp"

using mint = modint<1000000007>;

int main() {
    Combination<mint> comb(1000);

    int n, k;
    cin >> n >> k;

    cout << comb.P(k, n) << '\n';
}