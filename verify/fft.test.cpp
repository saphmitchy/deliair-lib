#define PROBLEM "https://atcoder.jp/contests/atc001/tasks/fft_c"

#include "../src/FFT.hpp"

FFT fft;

int main() {
    int N;
    cin >> N;

    vector<ll> a(N + 1, 0), b(N + 1, 0);
    rep2(i, 1, N + 1) cin >> a[i] >> b[i];

    auto c = fft.convolve(a, b);
    rep2(i, 1, 2 * N + 1) cout << c[i] << '\n';
}
