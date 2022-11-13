// 記述量軽減のため経路圧縮のみ実装。元の個数などの情報が欲しければCOMPLEXに書かれているコードも書く

#pragma once
#include "template.hpp"

struct UnionFind {
    vector<int> data; // 正のとき親のノードを、COMPLEXかつ負の時は集合の大きさを表す
    const int n;
    #if COMPLEX
    int cnt; // 全体の集合の数を表す
    #endif

    UnionFind(int _n) : data(_n, -1), n(_n) {
        #if COMPLEX
        cnt = _n;
        #endif
    }

    int operator[](int i) { return root(i); }

    // x を含む集合の代表元を返す
    int root(int x) {
        assert(0 <= x && x < n);
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }

    // x を含む集合とyを含む集合を合併する。mergeが起こるならtrueを返す。
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if(x == y) return true;
        #if COMPLEX
        --cnt;
        data[x] += data[y];
        #endif
        data[y] = x;
        return true;
    }

    // xとyが同じ集合に含まれているか調べる
    bool same(int x, int y) { return root(x) == root(y); }

    // below functions are optinal

    // 集合ごとにvectorに分けたものを返す。
    vector<vector<int>> groups() {
        vector<vector<int>> res(n);
        rep(i,n) res[root(i)].emplace_back(i);
        // 空集合を取り除く
        res.erase(remove_if(begin(res), end(res), [&](auto &v) { return v.empty();}), res.end());
        return res;
    }

    #if COMPLEX
    void clear() {
        cnt = n;
        fill(begin(data), end(data), -1);
    }
    
    // xが含まれる集合の大きさを返す。
    int size(int x) { return -data[root(x)]; }

    // 全体の集合の個数を返す
    int count() { return cnt; }
    #endif
};