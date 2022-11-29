#pragma once
#include "template.hpp"

// 各頂点が含まれる強連結成分の番号を持つ配列を返す
vector<int> scc(vector<vector<int>> es) {
    int n = sz(es);
    vector<vector<int>> rs(n);
    rep(i, n) each(e, es[i]) rs[e].eb(i);

    vector<int> comp(n, -1);
    vector<int> vs;

    auto dfs = [&](int i, auto &&dfs) -> void {
        if (comp[i] != -1) return;
        comp[i] = 1;
        each(e, es[i]) dfs(e, dfs);
        vs.eb(i);
    };

    auto rdfs = [&](int i, int col, auto &&rdfs) -> void {
        if (comp[i] != -1) return;
        comp[i] = col;
        each(e, rs[i]) rdfs(e, col, rdfs);
    };

    rep(i, n) dfs(i, dfs);
    fill(all(comp), -1);
    reverse(all(vs));
    int cnt = 0;
    each(e, vs) {
        if (comp[e] == -1) rdfs(e, cnt++, rdfs);
    }
    return comp;
}