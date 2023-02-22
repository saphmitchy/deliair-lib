// 点を arctan で偏角 ((-π,π] の範囲で) ソートする。
// ただし、(0,0) の偏角は 0 とする。

int type(pll p) {
    if (p.first == 0 && p.second == 0) return 0;
    if (p.second < 0 || (p.second == 0 && p.first > 0)) return -1;
    return 1;
}

bool compare_arg(pll p, pll q) {
    int a = type(p), b = type(q);
    if (a != b) return a < b;
    return p.first * q.second > q.first * p.second;
}

void sort_arg(vector<pll> &p) {
    sort(all(p), compare_arg);
}