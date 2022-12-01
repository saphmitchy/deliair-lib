#pragma once
#include "template.hpp"

// O(E√V)
struct BipartiteMatching {
    vector<vector<int>> es;
    vector<int> d, match;
    vector<bool> used, used2;
    int n, m;

    // 左側 n 頂点、右側 m 頂点
    BipartiteMatching(int n, int m) : es(n), d(n), match(m), used(n), used2(n), n(n), m(m) {}

    void add_edge(int u, int v) { es[u].eb(v); }

    void bfs() {
        fill(all(d), -1);
        queue<int> que;
        rep(i, n) {
            if (!used[i]) {
                que.emplace(i);
                d[i] = 0;
            }
        }
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            each(e, es[i]) {
                int j = match[e];
                if (j != -1 && d[j] == -1) {
                    que.emplace(j);
                    d[j] = d[i] + 1;
                }
            }
        }
    }

    bool dfs(int i) {
        used2[i] = true;
        each(e, es[i]) {
            int j = match[e];
            if (j == -1 || (!used2[j] && d[j] == d[i] + 1 && dfs(j))) {
                match[e] = i;
                used[i] = true;
                return true;
            }
        }
        return false;
    }

    // 右側の i は左側の match[i] とマッチングする
    int mm() {
        fill(all(match), -1);
        fill(all(used), false);
        int ret = 0;
        while (true) {
            bfs();
            fill(all(used2), false);
            int f = 0;
            rep(i, n) {
                if (!used[i] && dfs(i)) f++;
            }
            if (f == 0) break;
            ret += f;
        }
        return ret;
    }
};