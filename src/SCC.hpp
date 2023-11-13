#pragma once
#include "template.hpp"

// 各頂点が含まれる強連結成分の番号を持つ配列を返す

vector<int> scc(vector<vector<int>> es) {
    int n = sz(es);
    vector<vector<int>> rs(n);
    rep(i, n) each(e, es[i]) rs[e].eb(i);

    vector<int> comp(n, -1);
    vector<int> vs;

    auto dfs = [&](auto &&dfs, int now) -> void {
        if (comp[now] != -1) return;
        comp[now] = 1;
        each(e, es[now]) dfs(dfs, e);
        vs.eb(now);
    };

    auto rdfs = [&](auto &&rdfs, int now, int col) -> void {
        if (comp[now] != -1) return;
        comp[now] = col;
        each(e, rs[now]) rdfs(rdfs, e, col);
    };

    rep(i, n) dfs(dfs, i);
    fill(all(comp), -1);
    reverse(all(vs));
    int cnt = 0;
    each(e, vs) {
        if (comp[e] == -1) rdfs(rdfs, e, cnt++);
    }
    return comp;
}
