#pragma once
#include "template.hpp"

// O(EV+FElog(V))
// O(FElog(V)) : 最初のグラフにコスト負の辺が存在しないまたは DAG である場合
struct MinCostFlow {
    struct edge {
        int to;
        ll cap, cost;
        int rev;
        edge(int to, ll cap, ll cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<ll> d, h;
    vector<int> pre_v, pre_e;
    ll INF = 1LL << 60;
    int n;

    MinCostFlow(int n) : es(n), d(n), h(n), pre_v(n), pre_e(n), n(n) {}

    // u -> v
    void add_edge(int u, int v, ll cap, ll cost) {
        es[u].eb(v, cap, cost, sz(es[v]));
        es[v].eb(u, 0, -cost, sz(es[u]) - 1);
    }

    // 負辺があって DAG でない場合のみ
    void bellman_ford(int s) {
        fill(all(h), INF);
        h[s] = 0;
        while (true) {
            bool upd = false;
            rep(i, n) {
                if (h[i] == INF) continue;
                each(e, es[i]) {
                    if (e.cap > 0 && chmin(h[e.to], h[i] + e.cost)) upd = true;
                }
            }
            if (!upd) break;
        }
    }

    // 負辺があって DAG の場合のみ
    void dag_shortest_path(int s) {
        vector<int> deg(n, 0);
        rep(i, n) {
            each(e, es[i]) {
                if (e.cap > 0) deg[e.to]++;
            }
        }
        fill(all(h), INF);
        h[s] = 0;
        queue<int> que;
        rep(i, n) {
            if (deg[i] == 0) que.emplace(i);
        }
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            each(e, es[i]) {
                if (e.cap == 0) continue;
                chmin(h[e.to], h[i] + e.cost);
                if (--deg[e.to] == 0) que.emplace(e.to);
            }
        }
    }

    void dijkstra(int s) {
        fill(all(d), INF);
        minheap<pll> que;
        que.emplace(d[s] = 0, s);
        while (!que.empty()) {
            auto [p, i] = que.top();
            que.pop();
            if (p > d[i]) continue;
            rep(j, sz(es[i])) {
                edge e = es[i][j];
                if (e.cap > 0 && chmin(d[e.to], d[i] + e.cost + h[i] - h[e.to])) {
                    assert(e.cost + h[i] - h[e.to] >= 0);
                    pre_v[e.to] = i;
                    pre_e[e.to] = j;
                    que.emplace(d[e.to], e.to);
                }
            }
        }
    }

    // flow 流し切れなければ -INF
    ll mcf(int s, int t, ll flow, bool negative = false, bool dag = false) {
        ll ret = 0;
        if (negative) dag ? dag_shortest_path(s) : bellman_ford(s);
        while (flow > 0) {
            dijkstra(s);
            if (d[t] == INF) return -INF;
            rep(i, n) {
                if (h[i] == INF || d[i] == INF) {
                    h[i] = INF;
                } else {
                    h[i] += d[i];
                }
            }
            ll f = flow;
            for (int i = t; i != s; i = pre_v[i]) chmin(f, es[pre_v[i]][pre_e[i]].cap);
            assert(f > 0);
            ret += h[t] * f, flow -= f;
            for (int i = t; i != s; i = pre_v[i]) {
                edge &e = es[pre_v[i]][pre_e[i]];
                e.cap -= f;
                es[i][e.rev].cap += f;
            }
        }
        return ret;
    }
};