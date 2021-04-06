#include "bits/stdc++.h"
using namespace std;
namespace fft {
	struct cd {
		double x, y;
		cd(): x(0), y(0){}
		cd(const double &x, const double &y): x(x), y(y){}
		inline double real(){ return x; }
		inline double imag(){ return y; }
	};
	inline cd operator + (const cd &a, const cd &b){ return cd(a.x + b.x, a.y + b.y); }
	inline cd operator - (const cd &a, const cd &b){ return cd(a.x - b.x, a.y - b.y); }
	inline cd operator * (const cd &a, const cd &b){ return cd(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
	inline cd conj(const cd &a){ return cd(a.x, -a.y); }
	const double PI = acos(-1);
	const int MAXN = 1<<24;
	cd e[2][MAXN];
	int rev[MAXN];
	int init(int n){
		int len = 1;
		for(; len <= 2 * n; len <<= 1);
		for(int i = 0; i < len; i++){
			e[0][i] = cd(cos(2 * PI * i / len), sin(2 * PI * i / len));
			e[1][i] = cd(cos(2 * PI * i / len), -sin(2 * PI * i / len));
		}
		for (int i = 1, j = 0; i < len; i++) {
			int bit = len >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;
			rev[i] = j;
		}
        return len;
	}
	void fft(vector<cd> &a, bool inv){
		int n = a.size();
		for(int i = 0; i < n; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
		for(int len = 2; len <= n; len <<= 1){
			for(int i = 0; i < n; i += len){
				for(int j = 0; j < (len >> 1); j++){
					cd u = a[i + j];
					cd v = a[i + j + (len >> 1)] * e[inv][n / len * j];
					a[i + j] = u + v;
					a[i + j + (len >> 1)] = u - v;
				}
			}
		}
		if(inv){
			for(int i = 0; i < n; i++)
				a[i].x /= n;
		}
	}
    template<typename T = int>
	vector<T> multiply(const vector<int> &a, const vector<int> &b){
		int na = a.size(), nb = b.size();
		int len = max(na, nb);
		len = init(len);
		vector<cd> fa(len), fb(len);
		for(int i = 0; i < na; i++) fa[i].x = a[i];
		for(int i = 0; i < nb; i++) fb[i].x = b[i];
		fft(fa, false);
		fft(fb, false);
		for(int i = 0; i < len; i++) fa[i] = fa[i] * fb[i];
		fft(fa, true);
		vector<T> res(na + nb - 1);
		for(int i = 0; i < na + nb - 1; i++) res[i] = round(fa[i].x);
		return res;
	}
    template<typename T = int>
    vector<T> brute(const vector<int> &a, const vector<int> &b){
		int na = a.size(), nb = b.size();
        vector<T> res(na + nb - 1);
        for(int i = 0; i < na; i++) for(int j = 0; j < nb; j++) {
            res[i + j] += a[i] * b[j];
        }
        return res;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<long long> a(n), pref(n + 1); 
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    const int T = 10000;
    if(n <= T){
        unordered_set<long long> can;
        for(int i = 0; i < n; i++) for(int j = i; j < n; j++){
            can.insert(pref[j + 1] - pref[i]);
        }
        cout << can.size() - 1 << endl;
    } else {
        int mx = *max_element(pref.begin(), pref.end());
        vector<int> a(mx + 1, 0), b(mx + 1, 0);
        for(int i = 0; i <= n; i++) a[pref[i]]++;
        for(int i = 0; i <= n; i++) b[mx - pref[i]]++;
        vector<long long> ways = fft::multiply<long long>(a, b);
        int len = ways.size();
        int ans = 0;
        for(int i = mx + 1; i < len; i++) if(ways[i] > 0) ans++;
        cout << ans - 1 << endl;
    }
    return 0;
}