#pragma once
#include "template.hpp"

// n*m 行列 a が与えられたときに、Σ[i=0,...,n-1] a[i][p[i]] を最小化するような配列 p を求める (p の要素は相異なる)

pair<ll, vector<int>> hungarian(vector<vector<ll>> a) {
    ll INF = 1LL << 60;
    if (a.empty()) return {0, {}};
    int n = sz(a), m = sz(a[0]);
    assert(n <= m);
    vector<ll> u(n, 0), v(m + 1, 0);
    vector<int> p(m + 1, -1);
    rep(t, n) {
        p[m] = t;
        int j0 = m;
        vector<ll> d(m + 1, INF);
        vector<int> pre(m + 1, -1), used(m + 1, 0);
        while (j0 != -1 && p[j0] != -1) {
            used[j0] = 1;
            int i0 = p[j0], j1 = 1;
            ll del = INF;
            rep(j, m) {
                if (used[j]) continue;
                ll tmp = a[i0][j] - u[i0] - v[j];
                if (tmp < d[j]) d[j] = tmp, pre[j] = j0;
                if (d[j] < del) del = d[j], j1 = j;
            }
            rep(j, m + 1) {
                if (used[j]) u[p[j]] += del, v[j] -= del;
                d[j] -= del;
            }
            j0 = j1;
        }
        while (j0 != m) {
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    vector<int> match(n, -1);
    rep(i, m) {
        if (p[i] != -1) match[p[i]] = i;
    }
    return {-v[m], match};
}