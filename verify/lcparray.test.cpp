#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../src/SuffixArray.hpp"

int main() {
    string S;
    cin >> S;

    auto sa = suffixarray(S);
    auto lcp = lcparray(S, sa);

    ll n = sz(S), ans = n * (n + 1) / 2;
    rep(i, n - 1) ans -= lcp[i];
    cout << ans << '\n';
}