#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A&lang=ja"

#include "../src/ModInt.hpp"

using mint = modint<1000000007>;

int main() {
    int n;
    mint k;
    cin >> n >> k;

    cout << k.pow(n) << '\n';
}