#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 1e9 + 7;

template <int32_t MOD>
struct modint {
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
    inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
    inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const {
        modint<MOD> x = *this, y = 1;
        for (; k; k >>= 1) {
            if (k & 1) y *= x;
            x *= x;
        }
        return y;
    }
    modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
    inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
    inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
    inline bool operator == (modint<MOD> other) const { return value == other.value; }
    inline bool operator != (modint<MOD> other) const { return value != other.value; }
    inline bool operator < (modint<MOD> other) const { return value < other.value; }
    inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

struct combi{
	int n; vector<mint> facts, finvs, invs;
	combi(int _n): n(_n), facts(_n), finvs(_n), invs(_n){
		facts[0] = finvs[0] = 1;
		invs[1] = 1;
	    for (int i = 2; i < n; i++) invs[i] =  invs[mod % i] * (-mod / i);
		for(int i = 1; i < n; i++){
			facts[i] = facts[i - 1] * i;
			finvs[i] = finvs[i - 1] * invs[i];
		}
	}
	inline mint fact(int n) { return facts[n]; }
	inline mint finv(int n) { return finvs[n]; }
	inline mint inv(int n) { return invs[n]; }
	inline mint ncr(int n, int k) { return facts[n] * finvs[k] * finvs[n-k]; }
};
combi C(N);

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
    	int n, k; cin >> n >> k;
    	if((n - k) % 2 == 0) {
    		mint ans = 0;
    		mint two = mint(2).pow(k);
    		for (int r = 0; r <= k; r ++) {
    			mint nw = r & 1 ? -1 : 1;
    			nw *= C.ncr(k, r) * mint(k - 2 * r).pow(n);
    			nw /= two;
    			ans += nw;
    		}
    		cout << mint(2).pow(k) - 1 << ' ' << ans << '\n';
    	}
    	else {
    		mint ans = 0;
    		mint two = mint(2).pow(k);
    		for (int r = 0; r < k; r ++) {
    			mint nw = r & 1 ? -1 : 1;
    			nw *= C.ncr(k - 1, r) * (mint(k - 2 * r).pow(n) + mint(k - 2 * r - 2).pow(n));
    			nw /= two;
    			ans += nw;
    		}
    		cout << mint(2).pow(k) - 2 << ' ' << ans << '\n';
    	}

    }
    return 0;
}