// Low-Link
// 計算量 O(n+m)

// articulationに関節点の番号、bridgeに橋の番号が格納される

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja

#pragma once
#include "template.hpp"

template <bool directed = false>
struct Low_Link {

    vector<vector<pii>> es;
    vector<int> o, l;
    vector<bool> u;
    vector<int> articulation, bridge;
    const int n;
    int m;

    Low_Link(int n) : es(n), o(n), l(n), u(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].eb(to, m);
        if (!directed)
            es[to].eb(from, m);
        m++;
    }

    int dfs(int now, int p, int k) {
        u[now] = true;
        o[now] = l[now] = k++;
        bool isa = false;
        int c = 0;
        for (auto &[to, id] : es[now]) {
            if (id == p)
                continue;
            if (!u[to]) {
                c++;
                k = dfs(to, id, k);
                chmin(l[now], l[to]);
                if (p != -1 && l[to] >= o[now])
                    isa = true;
                if (o[now] < l[to])
                    bridge.eb(id);
            } else {
                chmin(l[now], o[to]);
            }
        }
        if (p == -1 && c >= 2)
            isa = true;
        if (isa)
            articulation.eb(now);
        return k;
    }

    void build() {
        fill(all(u), false);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (!u[i])
                k = dfs(i, -1, k);
        }
    }
};