#pragma once
#include "template.hpp"

vector<int> zalgo(string S) {
    int n = sz(S);
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && S[j] == S[i + j]) j++;
        ret[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < n && k + ret[k] < j) ret[i + k] = ret[k], k++;
        i += k, j -= k;
    }
    return ret;
}
