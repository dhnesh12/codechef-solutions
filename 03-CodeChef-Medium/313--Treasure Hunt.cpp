#include "bits/stdc++.h"
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,mmx,avx,avx2")
using namespace std;
using ll = long long int;

const int mod = 1e9+7;

int mpow(int a, int n)
{
    int ret = 1;
    while (n) {
        if (n&1) ret = 1LL*ret*a%mod;
        a = 1LL*a*a%mod;
        n >>= 1;
    }
    return ret;
}

const int LIM = 905;

int solveLinearBinary(vector<bitset<LIM>> &A, vector<int> &B)
{
    int n = A.size(), rank = 0, br = 0;
    // vector<int> col(m); iota(begin(col), end(col), 0);
    for (int i = 0; i < n; ++i) {
        for (br = i; br < n; ++br)
            if (A[br].any()) break;
        if (br == n) {
            for (int j = i; j < n; ++j)
                if (B[j]) return -1;
            break;
        }

        int bc = int(A[br]._Find_next(i-1));
        swap(A[i], A[br]);
        swap(B[i], B[br]);
        // swap(col[i], col[bc]);
        for (int j = 0; j < n; ++j) {
            if (A[j][i] != A[j][bc])
                A[j].flip(i), A[j].flip(bc);
        }
        for (int j = i+1; j < n; ++j) {
            if (A[j][i])
                B[j] ^= B[i], A[j] ^= A[i];
        }
        ++rank;
    }
    /*
    x = bitset<LIM>();
    for (int i = rank; i--; ) {
        if (!B[i]) continue;
        x[col[i]] = 1;
        for (int j = 0; j < i; ++j) B[j] ^= A[j][i];
    }
    */

    return rank;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<bitset<LIM>> A(n*m);
        vector<int> B(n*m);
        bitset<LIM> X;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x; cin >> x;
                if (x == -1) continue;
                auto &row = A[i*m + j];
                if (i > 0) row[(i-1)*m + j] = 1;
                if (j > 0) row[i*m + j-1] = 1;
                if (i+1 < n) row[(i+1)*m + j] = 1;
                if (j+1 < m) row[i*m + j+1] = 1;
                B[i*m + j] = x;
            }
        }
        int res = solveLinearBinary(A, B);
        if (res >= 0) cout << mpow(2, n*m-res) << '\n';
        else cout << 0 << '\n';
    }
}