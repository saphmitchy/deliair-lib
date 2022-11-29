#pragma once
#include "template.hpp"

// s を始点とする各点への最短距離
vector<ll> dijkstra(vector<vector<pll>> es, int s) {
    int n = sz(es);
    minheap<pll> que;
    vector<ll> d(n, 1LL << 60);
    que.emplace(d[s] = 0, s);
    while (!empty(que)) {
        auto [t, i] = que.top();
        que.pop();
        if (t > d[i]) continue;
        each(e, es[i]) {
            if (chmin(d[e.first], d[i] + e.second)) que.emplace(d[e.first], e.first);
        }
    }
    return d;
}
