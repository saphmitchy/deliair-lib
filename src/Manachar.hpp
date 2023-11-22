#pragma once
#include "template.hpp"

vector<int> manachar(string S) {
    int n = sz(S);
    vector<int> ret(n);
    int i = 0, j = 0;
    while (i < n) {
        while (i - j >= 0 && i + j < n && S[i - j] == S[i + j]) j++;
        ret[i] = j;
        int k = 1;
        while (i - k >= 0 && k + ret[i - k] < j) ret[i + k] = ret[i - k], k++;
        i += k, j -= k;
    }
    return ret;
}
