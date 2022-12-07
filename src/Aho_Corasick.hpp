#pragma once
#include "template.hpp"

// verify
// https://atcoder.jp/contests/abc268/submissions/37079644

template <int char_size, char base>
struct Aho_Corasick {
    struct Node {
        array<int, char_size + 1> next; // char_size + 1 に注意
        vector<int> accept;             // 接尾辞とマッチする文字列の id
        int count;

        Node() : count(0) { fill(all(next), -1); }
    };

    vector<Node> nodes;
    int FAIL = char_size;
    vector<int> correct;

    Aho_Corasick() { nodes.eb(); }

    void insert(const string &s, int id) {
        int now = 0;
        rep(i, sz(s)) {
            int t = s[i] - base;
            int next = nodes[now].next[t];
            if (next == -1) {
                next = nodes.size();
                nodes[now].next[t] = next;
                nodes.eb();
            }
            nodes[now].count++;
            now = next;
        }
        nodes[now].count++;
        nodes[now].accept.eb(id);
    }

    void insert(const string &s) { insert(s, nodes[0].count); }

    // build を呼ぶのを忘れない！
    void build() {
        correct.resize(sz(nodes));
        rep(i, sz(nodes)) correct[i] = sz(nodes[i].accept);
        queue<int> que;
        rep(i, char_size + 1) {
            if (nodes[0].next[i] != -1) {
                nodes[nodes[0].next[i]].next[FAIL] = 0;
                que.emplace(nodes[0].next[i]);
            } else {
                nodes[0].next[i] = 0;
            }
        }
        while (!que.empty()) {
            auto &now = nodes[que.front()];
            int fail = now.next[FAIL];
            correct[que.front()] += correct[fail];
            que.pop();
            rep(i, char_size) {
                if (now.next[i] != -1) {
                    nodes[now.next[i]].next[FAIL] = nodes[fail].next[i];
                    auto &u = nodes[now.next[i]].accept;
                    auto v = nodes[nodes[fail].next[i]].accept;
                    vector<int> accept;
                    set_union(all(u), all(v), back_inserter(accept));
                    u = accept;
                    que.emplace(now.next[i]);
                } else {
                    now.next[i] = nodes[fail].next[i];
                }
            }
        }
    }
};