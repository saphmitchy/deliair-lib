#pragma once
#include "template.hpp"

struct Centroid_Decomposition {
    vector<vector<int>> es;
    int n;
    vector<int> si, used;

    Centroid_Decomposition(vector<vector<int>> es) : es(es), n(sz(es)), si(sz(es)), used(sz(es), 0) {}

    int dfs1(int now, int pre = -1) {
        si[now] = 1;
        each(e, es[now]) {
            if (e == pre || used[e]) continue;
            si[now] += dfs1(e, now);
        }
        return si[now];
    }

    pii dfs2(int now, int s, int pre = -1) {
        pii ret = pii(INT_MAX, -1);
        int M = 0, S = 1;
        each(e, es[now]) {
            if (e == pre || used[e]) continue;
            chmin(ret, dfs2(e, s, now));
            chmax(M, si[e]);
            S += si[e];
        }
        chmax(M, s - S);
        chmin(ret, pii(M, now));
        return ret;
    }

    int centroid(int r) {
        dfs1(r);
        return dfs2(r, si[r]).second;
    }
};