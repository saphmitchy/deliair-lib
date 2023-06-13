#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "../src/CentroidDecomposition.hpp"

template <typename T>
struct Fast_Fourier_Transform {
    using comp = complex<double>;
    static double pi;
    static vector<comp> r, ir;

    Fast_Fourier_Transform() {}

    static void init() {
        if (!r.empty()) return;
        r.resize(30), ir.resize(30);
        for (int i = 0; i < 30; i++) {
            r[i] = -polar(1.0, pi / (1 << (i + 1)));   // r[i] := 1 の 2^(i+2) 乗根
            ir[i] = -polar(1.0, -pi / (1 << (i + 1))); // ir[i] := 1/r[i]
        }
    }

    static vector<comp> to_comp(vector<T> a) {
        vector<comp> ret(a.size());
        for (int i = 0; i < (int)a.size(); i++) ret[i] = comp(a[i], 0.0);
        return ret;
    }

    static vector<T> to_T(vector<comp> a) {
        vector<T> ret(a.size(), 0);
        for (int i = 0; i < (int)a.size(); i++) ret[i] = a[i].real() + 0.1; // 整数の場合、誤差をケア
        // for(int i = 0; i < (int)a.size(); i++) ret[i] = a[i].real(); // 小数の場合
        return ret;
    }

    static void fft(vector<comp> &a) {
        init();
        int n = a.size();
        assert((n & (n - 1)) == 0);
        for (int k = n; k >>= 1;) {
            comp w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    comp x = a[i], y = w * a[j];
                    a[i] = x + y, a[j] = x - y;
                }
                w *= r[__builtin_ctz(++t)];
            }
        }
    }

    static void ifft(vector<comp> &a) {
        init();
        int n = a.size();
        assert((n & (n - 1)) == 0);
        a.resize(n);
        for (int k = 1; k < n; k <<= 1) {
            comp w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    comp x = a[i], y = a[j];
                    a[i] = x + y, a[j] = w * (x - y);
                }
                w *= ir[__builtin_ctz(++t)];
            }
        }
        for (auto &e : a) e /= n;
    }

    static vector<T> convolve(vector<T> a, vector<T> b) {
        int k = (int)a.size() + (int)b.size() - 1, n = 1;
        while (n < k) n <<= 1;
        vector<comp> A = to_comp(a), B = to_comp(b);
        A.resize(n), B.resize(n);
        fft(A), fft(B);
        for (int i = 0; i < n; i++) A[i] *= B[i];
        ifft(A);
        vector<T> c = to_T(A);
        c.resize(k);
        return c;
    }
};

template <typename T>
double Fast_Fourier_Transform<T>::pi = acos(-1.0);

template <typename T>
vector<complex<double>> Fast_Fourier_Transform<T>::r = vector<complex<double>>();

template <typename T>
vector<complex<double>> Fast_Fourier_Transform<T>::ir = vector<complex<double>>();

using FFT = Fast_Fourier_Transform<long long>;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> es(n);
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        es[u].eb(v), es[v].eb(u);
    }

    Centroid_Decomposition G(es);

    vector<ll> ans(n, 0);

    auto rec = [&](int now, auto &&rec) -> void {
        int c = G.centroid(now);
        G.used[c] = true;
        vector<ll> s = {0};
        each(e, es[c]) {
            
        }
    };
}