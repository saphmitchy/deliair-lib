#pragma once
#include "template.hpp"

// 辞書順 i 番目が sa[i] から始まる接尾辞
vector<int> suffixarray(string S) {
    int n = sz(S);
    vector<int> sa(n);
    iota(all(sa), 0);
    sort(all(sa), [&](int i, int j) { return S[i] == S[j] ? i > j : S[i] < S[j]; });
    vector<int> rank(n), c(n), cnt(n);
    rep(i, n) c[i] = S[i];
    for (int len = 1; len < n; len <<= 1) {
        rep(i, n) {
            if (i == 0 || c[sa[i - 1]] != c[sa[i]]) {
                rank[sa[i]] = i;
            } else {
                if (sa[i - 1] + len >= n || c[sa[i - 1] + len / 2] != c[sa[i] + len / 2]) {
                    rank[sa[i]] = i;
                } else {
                    rank[sa[i]] = rank[sa[i - 1]];
                }
            }
        }
        iota(all(cnt), 0);
        copy(all(sa), begin(c));
        rep(i, n) {
            int j = c[i] - len;
            if (j >= 0) sa[cnt[rank[j]]++] = j;
        }
        swap(rank, c);
    }
    return sa;
};

// lcp[i] := S[sa[i]:] と S[sa[i+1]:] の最長共通接頭辞の長さ
vector<int> lcparray(string S, vector<int> sa) {
    int n = sz(S);
    vector<int> rank(n), lcp(n - 1);
    rep(i, n) rank[sa[i]] = i;
    int h = 0;
    rep(i, n) {
        if (rank[i] + 1 < n) {
            int j = sa[rank[i] + 1];
            while (max(i, j) + h < n && S[i + h] == S[j + h]) h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}