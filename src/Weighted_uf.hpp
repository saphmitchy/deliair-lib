// 記述量軽減のため経路圧縮のみ実装。元の個数などの情報が欲しければCOMPLEXに書かれているコードも書く

#pragma once

#include "template.hpp"

template<class T>
struct Weighted_uf {
    const int n;
    vector<int> data; // 正のとき親のノードを、COMPLEXかつ負の時は集合の大きさを表す
    vector<T> ws; // (自分の重み) - (親の重み)
    #ifdef COMPLEX
    int cnt; // 全体の集合の数を表す
    #endif

    Weighted_uf(int _n) : n(_n), data(n, -1), ws(n, 0) {
        #ifdef COMPLEX
        cnt = n;
        #endif
    }

    // x を含む集合の代表元を返す
    int root(int x) {
        if(data[x] < 0) return x;
        int par = root(data[x]);
        ws[x] += ws[data[x]];
        return data[x] = par;
    }

    int operator[](int i) { return root(i); }

    T weight(int x) {
        root(x);
        return ws[x];
    }


    // weight(x) - weghit(y) = w;
    // x, yが既に同じ集合に属しておりかる以前の情報と不整合が起こるならばfalseを、それ以外ならtrueを返す。
    bool unite(int x, int y, T w) {
        int a = root(x), b = root(y);
        w -= ws[x], w += ws[y];
        if(a == b) return w == 0;
        #ifdef COMPLEX
        --cnt;
        data[b] += data[a];
        #endif
        data[a] = b;
        ws[a] = w;
        return true;
    }

    // weight(x) - weghit(y)
    T diff(int x, int y) { return weight(x) - weight(y); }

    // xとyが同じ集合に含まれているか調べる
    bool same(int x, int y) { return root(x) == root(y); }

    // below functions are optional

    // 集合ごとにvectorに分けたものを返す。
    vector<vector<int>> groups() {
        vector<vector<int>> res(n);
        rep(i,n) res[root(i)].emplace_back(i);
        // 空集合を取り除く
        res.erase(remove_if(begin(res), end(res), [&](auto &v) { return v.empty();}), res.end());
        return res;
    }

    #ifdef COMPLEX
    // 初期化する
    void clear() {
        cnt = n;
        fill(all(data), -1);
        fill(all(ws), 0);
    }

    // xが含まれる集合の大きさを返す。
    int size(int x) { return -data[root(x)]; }

    // 全体の集合の個数を返す
    int count() { return cnt; }
    #endif
};