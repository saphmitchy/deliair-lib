// 二重辺連結成分分解（分解後は森になる）
// 計算量 O(n+m)

#include "LowLink.hpp"

struct Two_Edge_Connected_Components : Low_Link {
    using L = Low_Link;
    vector<int> c;
    const int n;

    Two_Edge_Connected_Components(int n) : L(n), c(n), n(n) {}

    int dfs(int now, int p, int k) {
        if (p != -1 && this->o[p] >= this->l[now]) {
            c[now] = c[p];
        } else {
            c[now] = k++;
        }
        for (auto &[to, id] : this->es[now]) {
            if (c[to] == -1) k = dfs(to, now, k);
        }
        return k;
    }

    // 構築し、縮約されたグラフを返す
    vector<vector<int>> decompose() {
        this->build();
        fill(all(c), -1);
        int k = 0;
        rep(i, n) {
            if (c[i] == -1) k = dfs(i, -1, k);
        }
        vector<vector<int>> ret(k);
        vector<int> isb(this->m, 0);
        each(e, this->bridge) isb[e]++;
        rep(i, n) {
            for (auto &[to, id] : this->es[i]) {
                if (isb[id]-- > 0) {
                    ret[c[i]].eb(c[to]);
                    ret[c[to]].eb(c[i]);
                }
            }
        }
        return ret;
    }

    // 頂点iが属する連結成分の番号
    int operator[](int i) const { return c[i]; }
};