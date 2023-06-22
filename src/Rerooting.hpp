#pragma once
#include "template.hpp"

// S: 部分木のデータの型, T: 辺のデータの型
template <typename S, typename T>
struct Rerooting {
    struct edge {
        int to;
        T data;
        S dp, ndp; // to 側の部分木 dp（辺も含む）、from 側の部分木 dp（辺は含まない）
        edge(int to, const T &data, const S &dp, const S &ndp) : to(to), data(data), dp(dp), ndp(ndp) {}
    };

    using F = function<S(S, S)>;
    using G = function<S(S, T)>;
    vector<vector<edge>> es;
    const int n;
    vector<S> sdp, dp; // 部分木の dp、全方位の dp
    unordered_map<ll, S> mp;
    const F f;                // 1 頂点を間に挟んで隣り合う 2 つの部分木の情報をマージ
    const G g;                // 部分木の根に 1 本辺を足す
    const S e1;           // f の単位元
    const vector<S> b; // 1 頂点の場合の dp の値

    Rerooting(int n, const F &f, const G &g, const S &e1, const vector<S> &b) : es(n), n(n), sdp(b), dp(n), f(f), g(g), e1(e1), b(b) {}

    void add_edge(int from, int to, const T &data) {
        es[from].eb(to, data, e1, b[from]);
        es[to].eb(from, data, e1, b[to]);
    }

    void dfs_sub(int now, int pre = -1) {
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            dfs_sub(e.to, now);
            sdp[now] = f(sdp[now], g(sdp[e.to], e.data));
        }
    }

    void dfs_all(int now, const S &top, int pre = -1) {
        S s = e1;
        for (int i = 0; i < (int)es[now].size(); i++) {
            auto &e = es[now][i];
            e.ndp = f(e.ndp, s);
            e.dp = g(e.to == pre ? top : sdp[e.to], e.data);
            s = f(s, e.dp);
        }
        dp[now] = f(b[now], s);
        s = e1;
        per(i, sz(es[now])) {
            auto &e = es[now][i];
            e.ndp = f(e.ndp, s);
            if (e.to != pre) {
                mp[1LL * n * now + e.to] = e.ndp;
                mp[1LL * n * e.to + now] = sdp[e.to];
                dfs_all(e.to, e.ndp, now);
            }
            s = f(s, e.dp);
        }
    }

    vector<S> solve() {
        dfs_sub(0);
        dfs_all(0, e1);
        return dp;
    }

    // 辺 {u,v} で切った後の u 側の部分木 dp
    S get_subtree(int u, int v) { return mp[1LL * n * u + v]; }
};
