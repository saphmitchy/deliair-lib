#pragma once
#include "template.hpp"

struct HLD {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> par, si, depth;
    vector<int> root;       // 属する連結成分の根
    vector<int> id_v, id_e; // 各頂点、各辺が一列に並べたときに何番目に相当するか (辺の番号は 1,2,...,n-1 となることに注意)
    vector<int> vs;
    const int n;
    int m;

    HLD(int n) : es(n), par(n), si(n, -1), depth(n), root(n), id_v(n), id_e(n - 1), vs(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        es[to].emplace_back(from, m);
        m++;
    }

    int dfs1(int now, int pre = -1) {
        par[now] = pre;
        if (pre == -1) depth[now] = 0;
        si[now] = 1;
        each(e, es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                si[now] += dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void dfs2(int now, bool st, int &s, int pre = -1) {
        root[now] = (st ? now : root[pre]);
        id_v[now] = s++;
        vs[id_v[now]] = now;
        edge heavy = {-1, -1};
        int M = 0;
        each(e, es[now]) {
            if (e.to == pre) continue;
            if (M < si[e.to]) M = si[e.to], heavy = e;
        }
        if (heavy.id != -1) {
            id_e[heavy.id] = s;
            dfs2(heavy.to, false, s, now);
        }
        each(e, es[now]) {
            if (e.to != pre && e.id != heavy.id) {
                id_e[e.id] = s;
                dfs2(e.to, true, s, now);
            }
        }
    }

    void decompose() {
        int s = 0;
        rep(i, n) {
            if (si[i] != -1) continue;
            dfs1(i);
            dfs2(i, true, s);
        }
    }

    int lca(int u, int v) {
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return u;
    }

    int dist(int u, int v) { return depth[u] + depth[v] - depth[lca(u, v)] * 2; }

    // u の k 個前の祖先
    int ancestor(int u, int k) {
        if (k > depth[u]) return -1;
        while (k > 0) {
            int r = root[u];
            int l = depth[u] - depth[r];
            if (k <= l) return vs[id_v[r] + l - k];
            u = par[r];
            k -= l + 1;
        }
        return u;
    }

    // u から v の方向へ k 回移動
    int move(int u, int v, int k) {
        int w = lca(u, v);
        int l = depth[u] + depth[v] - depth[w] * 2;
        if (k > l) return -1;
        if (k <= depth[u] - depth[w]) return ancestor(u, k);
        return ancestor(v, l - k);
    }

    // パスに対応する区間たちを列挙
    vector<pair<int, int>> get_path(int u, int v, bool use_edge = false) {
        vector<pair<int, int>> ret;
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            ret.emplace_back(id_v[root[v]], id_v[v] + 1);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        ret.emplace_back(id_v[u] + use_edge, id_v[v] + 1);
        return ret;
    }

    // クエリが非可換の場合 (l > r なら子から親方向で [r,l)、l < r なら親から子方向で [l,r))
    vector<pair<int, int>> get_path_noncommutative(int u, int v, bool use_edge = false) {
        vector<pair<int, int>> l, r;
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) {
                l.emplace_back(id_v[u] + 1, id_v[root[u]]);
                u = par[root[u]];
            } else {
                r.emplace_back(id_v[root[v]], id_v[v] + 1);
                v = par[root[v]];
            }
        }
        if (depth[u] > depth[v]) {
            l.emplace_back(id_v[u] + 1, id_v[v] + use_edge);
        } else {
            r.emplace_back(id_v[u] + use_edge, id_v[v] + 1);
        }
        reverse(begin(r), end(r));
        for (auto &e : r) l.push_back(e);
        return l;
    }
};
