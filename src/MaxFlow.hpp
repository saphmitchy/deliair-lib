#pragma once
#include "template.hpp"

// Dinic O(EV^2)
struct MaxFlow {
    struct edge {
        int to;
        ll cap;
        int rev;
        edge(int to, ll cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<int> d, pos;
    int n;
    ll INF = 1LL << 60;

    MaxFlow(int n) : es(n), d(n), pos(n), n(n) {}

    // u -> v
    void add_edge(int u, int v, ll cap) {
        es[u].eb(v, cap, sz(es[v]));
        es[v].eb(u, 0, sz(es[u]) - 1);
    }

    bool bfs(int s, int t) {
        fill(all(d), -1);
        queue<int> que;
        d[s] = 0;
        que.emplace(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            each(e, es[i]) {
                if (e.cap > 0 && d[e.to] == -1) {
                    d[e.to] = d[i] + 1;
                    que.emplace(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    ll dfs(int i, int t, ll flow) {
        if (i == t) return flow;
        for (int &j = pos[i]; j < sz(es[i]); j++) {
            edge &e = es[i][j];
            if (e.cap > 0 && d[e.to] > d[i]) {
                ll f = dfs(e.to, t, min(flow, e.cap));
                if (f > 0) {
                    e.cap -= f;
                    es[e.to][e.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }

    // 操作後の d 配列は最小カットの 1 つを表す (0 以上なら s 側、-1 なら t 側)
    ll mf(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(all(pos), 0);
            ll f = 0;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};