#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define vii vector<int>
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pdd pair<double,double>
#define pldld pair<long long double, long long double>
#define ff first
#define ss second
#define pb push_back
#define read freopen("alu.txt","r",stdin);
#define write freopen("vorta.txt","w",stdout);
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define PI 2*acos(0.0)
#define eps 1e-11
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 2e5 + 5, MOD = 1e9 + 7  , MAXLG = log2(MAX)+1;
const ll inf = 1e18 + 5;

typedef complex<double> base;

void fft(vector<base> & a, bool invert) {
    int n = (int)a.size();

    for (int i = 1, j = 0; i<n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i<n; i += len) {
            base w(1);
            for (int j = 0; j<len / 2; ++j) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (int i = 0; i<n; ++i) a[i] /= n;
}

vector<int> Mul(vector<int>& a, vector<int>& b){
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (int i = 0; i<n; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> res;
    res.resize(n);
    for (int i = 0; i<n; ++i) res[i] = round(fa[i].real());
    return res;
}

vector<int> to_vec(string s){
    vector<int> ret;
    for(int i=0; i<s.size(); i++) ret.pb(s[i] - '0');
    return ret;
}

void flip(vector<int> &v){
    for(int i=0; i<v.size(); i++) v[i] = v[i] ^ 1;
}

int arr[MAX];
int main(){

    fastio;
    string str;
    cin >> str;
    vector<int> s = to_vec(str);
    vector<int> fs = s;
    flip(fs);

    int k;
    cin >> k;
    while(k--){
        cin >> str;
        vector<int> p = to_vec(str);
        vector<int> fp = p;
        flip(fp);
        reverse(p.begin(), p.end());
        reverse(fp.begin(), fp.end());

        vector<int> res_one = Mul(p,s);
        vector<int> res_zero = Mul(fp,fs);

        int st = (int)p.size() - 1;
        ll hash = (int)p.size() - res_one[st] - res_zero[st];
        for(int i = st + 1; i < s.size(); i++){
            hash = (hash * 100001) % MOD;
            hash += ((int)p.size() - res_one[i] - res_zero[i]);
            if(hash >= MOD) hash -= MOD;
        }
        cout << hash << "\n";
    }
}