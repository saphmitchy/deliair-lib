#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../src/SuffixArray.hpp"

int main() {
    string S;
    cin >> S;

    print(suffixarray(S));
}