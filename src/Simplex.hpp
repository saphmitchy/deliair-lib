#pragma once
#include "template.hpp"

// Maximize cx s.t. Ax <= b, x >= 0
// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html
// Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp
template <typename Float = double, int LOGEPS = 20, bool Randomize = false>
struct Simplex {
    const Float EPS = Float(1.0) / (1LL << LOGEPS);
    int n, m;
    vector<int> shuffle_idx;
    vector<int> idx;
    vector<vector<Float>> mat;
    int i_ch, j_ch;

    void _initialize(const vector<vector<Float>> &A, const vector<Float> &b, const vector<Float> &c) {
        n = c.size(), m = A.size();

        mat.assign(m + 2, vector<Float>(n + 2));
        i_ch = m;
        rep(i, m) {
            rep(j, n) mat[i][j] = -A[i][j];
            mat[i][n] = 1, mat[i][n + 1] = b[i];
            if (mat[i_ch][n + 1] > mat[i][n + 1]) i_ch = i;
        }
        rep(j, n) mat[m][j] = c[j];
        mat[m + 1][n] = -1;

        idx.resize(n + m + 1);
        iota(all(idx), 0);
    }

    inline Float abs_(Float x) noexcept { return x > -x ? x : -x; }

    void _solve() {
        vector<int> jupd;
        for (nb_iter = 0, j_ch = n;; nb_iter++) {
            if (i_ch < m) {
                swap(idx[j_ch], idx[i_ch + n + 1]);
                mat[i_ch][j_ch] = Float(1) / mat[i_ch][j_ch];
                jupd.clear();
                rep(j, n + 2) {
                    if (j != j_ch) {
                        mat[i_ch][j] *= -mat[i_ch][j_ch];
                        if (abs_(mat[i_ch][j]) > EPS) jupd.push_back(j);
                    }
                }
                rep(i, m + 2) {
                    if (abs_(mat[i][j_ch]) < EPS || i == i_ch) continue;
                    each(j, jupd) mat[i][j] += mat[i][j_ch] * mat[i_ch][j];
                    mat[i][j_ch] *= mat[i_ch][j_ch];
                }
            }

            j_ch = -1;
            rep(j, n + 1) {
                if (j_ch < 0 || idx[j_ch] > idx[j]) {
                    if (mat[m + 1][j] > EPS || (abs_(mat[m + 1][j]) < EPS && mat[m][j] > EPS)) j_ch = j;
                }
            }
            if (j_ch < 0) break;

            i_ch = -1;
            rep(i, m) {
                if (mat[i][j_ch] < -EPS) {
                    if (i_ch < 0) {
                        i_ch = i;
                    } else if (mat[i_ch][n + 1] / mat[i_ch][j_ch] - mat[i][n + 1] / mat[i][j_ch] < -EPS) {
                        i_ch = i;
                    } else if (mat[i_ch][n + 1] / mat[i_ch][j_ch] - mat[i][n + 1] / mat[i][j_ch] < EPS && idx[i_ch] > idx[i]) {
                        i_ch = i;
                    }
                }
            }
            if (i_ch < 0) {
                is_infty = true;
                break;
            }
        }
        if (mat[m + 1][n + 1] < -EPS) {
            infeasible = true;
            return;
        }
        x.assign(n, 0);
        for (int i = 0; i < m; i++) {
            if (idx[n + 1 + i] < n) x[idx[n + 1 + i]] = mat[i][n + 1];
        }
        ans = mat[m][n + 1];
    }

    unsigned nb_iter;
    bool is_infty;
    bool infeasible;
    vector<Float> x;
    Float ans;

    Simplex(vector<vector<Float>> A, vector<Float> b, vector<Float> c) {
        is_infty = infeasible = false;

        //-------------------------------基本的に使わない-----------------------------
        if (Randomize) {
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

            vector<pair<vector<Float>, Float>> Abs;
            rep(i, sz(A)) Abs.emplace_back(A[i], b[i]);
            shuffle(all(Abs), rng);
            A.clear(), b.clear();
            each(Ab, Abs) {
                A.emplace_back(Ab.first);
                b.emplace_back(Ab.second);
            }

            shuffle_idx.resize(sz(c));
            iota(all(shuffle_idx), 0);
            shuffle(all(shuffle_idx), rng);
            auto Atmp = A;
            auto ctmp = c;
            rep(i, sz(A)) {
                rep(j, sz(A[i])) {
                    A[i][j] = Atmp[i][shuffle_idx[j]]; //
                }
            }
            rep(j, sz(c)) c[j] = ctmp[shuffle_idx[j]];
        }
        //---------------------------------------------------------------------------

        _initialize(A, b, c);
        _solve();

        //-------------------------------基本的に使わない-----------------------------
        if (Randomize && sz(x) == sz(c)) {
            auto xtmp = x;
            rep(j, sz(c)) x[shuffle_idx[j]] = xtmp[j];
        }
        //---------------------------------------------------------------------------
    }

    //-------------------------------基本的に使わない-----------------------------
    static void dual(vector<vector<Float>> &A, vector<Float> &b, vector<Float> &c) {
        int n = sz(b), m = sz(c);
        vector<vector<Float>> At(m, vector<Float>(n));
        rep(i, n) {
            rep(j, m) {
                At[j][i] = -A[i][j]; //
            }
        }
        A = At;
        rep(i, n) b[i] = -b[i];
        rep(j, m) c[j] = -c[j];
        b.swap(c);
    }
    //---------------------------------------------------------------------------
};
