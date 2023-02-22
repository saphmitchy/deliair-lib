#pragma once
#include "template.hpp"

// verify
// https://atcoder.jp/contests/tenka1-2016-final/submissions/37078941

template <int char_size, char base>
struct Trie {
    struct Node {
        array<int, char_size> next;
        vector<int> accept; // 該当する文字列の id
        int count;          // 子以下に追加された文字列の個数

        Node() : count(0) { fill(all(next), -1); }
    };

    vector<Node> nodes;

    Trie() { nodes.eb(); }

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
};