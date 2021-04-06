#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int sum(int a, int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}
int sub(int a, int b) {
    return a - b < 0 ? a - b + MOD : a - b;
}
int mul(int a, int b) {
    return (1LL*a*b)%MOD;
}
int pw(int a, int b) {
	if (!b) return 1;
	int r = pw(a, b/2);
	r = mul(r, r);
	if (b%2) r = mul(r, a);
	return r;
}

int power(int a, int p, int mod) {
    if (p==0)   return 1;
    int ans = power(a, p/2, mod);
    ans = (ans * 1LL * ans)%mod;
    if (p%2)    ans = (ans * 1LL * a)%mod;
    return ans;
}

/** Find primitive root of p assuming p is prime.
if not, we must add calculation of phi(p)
Complexity : O(Ans * log (phi(n)) * log n + sqrt(p)) (if exists)
             O(p * log (phi(n)) * log n + sqrt(p))   (if does not exist)
Returns -1 if not found
*/
int primitive_root(int p) {
    if (p == 2) return 1;
    vector<int> factor;
    int phi = p-1,  n = phi;

    for (int i=2; i*i<=n; ++i)
        if (n%i == 0) {
            factor.push_back (i);
            while (n%i==0)  n/=i;
        }

    if (n>1)  factor.push_back(n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (int i=0; i<factor.size() && ok; ++i)
            ok &= power(res, phi/factor[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

struct NTT {
    int N;
    vector<int> perm;
    vector<int>wpowers[2][20];

    int mod, root, inv, pw;

    NTT(int mod, int root, int inv, int pw) :
        mod(mod), root(root), inv(inv), pw(pw) {}

    void precalculate() {
        perm.resize(N);
        perm[0] = 0;

        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }

        for (int invert = 0 ; invert < 2; invert++) {
            for (int idx = 0, len = 2; len <= N; idx++, len <<= 1) {
                int factor = invert ? inv : root;
                for (int i = len; i < pw; i <<= 1)
                    factor = mul(factor, factor);

                wpowers[invert][idx].resize(N);
                wpowers[invert][idx][0] = 1;
                for (int i = 1; i < len; i++) {
                    wpowers[invert][idx][i] = mul(wpowers[invert][idx][i-1], factor);
                }
            }
        }
    }

    void fft(vector<int> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N&(N-1)) == 0);
            precalculate();
        }

        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int idx = 0, len = 2; len <= N; idx++, len <<= 1) {
            for (int i=0; i<N; i+=len) {
                int half = len/2;
                for (int j=0; j<half; j++) {
                    int x = v[i+j];
                    int y = mul(wpowers[invert][idx][j], v[i+j+half]);
                    v[i+j] = sum(x, y);
                    v[i+j+half] = sub(x, y);
                }
            }
        }
        if (invert) {
            int n1 = power(N, mod-2, mod);
            for (int &x : v) x = mul(x, n1);
        }
    }

    const int THR = 100;

//    vector<LL> multiply(vector<LL> a, vector<LL> b) {
////        while (a.size() > 1 && a.back() == 0) a.pop_back();
////        while (b.size() > 1 && b.back() == 0) b.pop_back();
//
////        if (a.size() * b.size() <= THR) {
////            vector< LL >c(a.size()+b.size(), 0);
////            for (int i = 0; i < a.size(); i++) {
////                for (int j = 0; j < b.size(); j++) {
////                    c[i+j] = sum(c[i+j], mul(a[i], b[j]));
////                }
////            }
////            return c;
////        }
//
//        int n = 1;
//        while (n < a.size()+ b.size())  n<<=1;
//        a.resize(n);
//        b.resize(n);
//
//        fft(a);
//        fft(b);
//        for (int i=0; i<n; i++) a[i] = (a[i] * b[i])%mod;
//        fft(a, true);
//        return a;
//    }

//    vector<LL> square(vector<LL> a) {
//        int n = 1;
//        while (n < a.size()+ a.size())  n<<=1;
//        a.resize(n);
//
//        fft(a);
//        for (int i=0; i<n; i++) a[i] = (a[i] * a[i])%mod;
//        fft(a, true);
//
//        return a;
//    }
};

NTT ntt(998244353, 15311432, 469870224, 1<<23);

void normalize(vector< int >&v, int modulo, int sz) {
    for (int i = modulo, j = 0; i < v.size(); i++) {
        v[j] = sum(v[j], v[i]);
        v[i] = 0;
        j++;
        if (j == modulo) j = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    int n, p, k;
    cin >> n >> p >> k;

    vector< int >ghat(p, -1);
    ///what if p = 2?
    int root = primitive_root(p);
//    cout << "root " << root << endl;

    int prod = 1;
    for (int i = 0; i < p-1; i++) {
        ghat[prod] = i;
        prod = (prod*1LL*root)%p;
    }

    int sz = 1;
    while (sz < 2*(p-1)) sz <<= 1;

    vector< int >unit(sz, 0);
    int zeroes = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == 0) zeroes++;
        else unit[ghat[x]]++;
    }


    int zeroway = sub(power(n, k, MOD), power(n-zeroes, k, MOD));

    vector< int >ans(sz, 0);
    ans[0] = 1;

    while (k > 0) {
        bool ffted = false;
        if (k & 1) {
            ffted = true;
            ntt.fft(ans, false);
            ntt.fft(unit, false);
            for (int i = 0; i < sz; i++) ans[i] = mul(ans[i], unit[i]);
            ntt.fft(ans, true);
            normalize(ans, p-1, sz);
        }
        k >>= 1;
        if (k > 0) {
            if (!ffted) ntt.fft(unit, false);
            for (int i = 0; i < sz; i++) unit[i] = mul(unit[i], unit[i]);
            ntt.fft(unit, true);
            normalize(unit, p-1, sz);
        }
    }

    cout << zeroway;
    for (int i = 1; i < p; i++) cout << " " << ans[ghat[i]];
    cout << "\n";


    return 0;
}
