#include <bits/stdc++.h>
// #include <bits/extc++.h>
#define pb push_back
#define sz(x) x.size()
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long int;
using vi = vector<int>;
const int MOD = 1e9 + 7;

template<class T> struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); } 
	vector<T> v; vector<vi> jmp;
	int comb(int a, int b) { 
		return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b); 
	}
	void init(const vector<T>& _v) {
		v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
									jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) { 
		int d = level(r-l+1);
		return comb(jmp[d][l],jmp[d][r-(1<<d)+1]);
	}
	T query(int l, int r) { return v[index(l,r)]; }
};

struct SuffixArray {
	string S; int N;
	void init(const string& _S) {
		S = _S; N = sz(S);
		genSa(); genLcp(); 
	}
	vi sa, isa;
	void genSa() {
		sa.resize(N), isa.resize(N); iota(all(sa),0);
		sort(all(sa),[&](int a, int b) { return S[a] < S[b]; });
		F0R(i,N) {
			bool same = i && S[sa[i]] == S[sa[i-1]];
			isa[sa[i]] = same ? isa[sa[i-1]] : i; 
		}
		for (int len = 1; len < N; len *= 2) { 
			vi is(isa), s(sa), nex(N); iota(all(nex),0); 
			FOR(i,-1,N) { 
				int s1 = (i == -1 ? N : s[i])-len; 
				if (s1 >= 0) sa[nex[isa[s1]]++] = s1; 
			} 
			F0R(i,N) { 
				bool same = i && sa[i-1]+len < N
							  && is[sa[i]] == is[sa[i-1]]
							  && is[sa[i]+len] == is[sa[i-1]+len]; 
				isa[sa[i]] = same ? isa[sa[i-1]] : i; 
			}
		}
	}
	vi lcp;
	void genLcp() { 
		lcp = vi(N-1); int h = 0;
		F0R(i,N) if (isa[i]) {
			for (int j=sa[isa[i]-1]; j+h<N && S[i+h]==S[j+h]; h++);
			lcp[isa[i]-1] = h; if (h) h--; 
		}
		R.init(lcp);
	}
	RMQ<int> R; 
	int getLCP(int a, int b) { 
		if (max(a,b) >= N) return 0;
		if (a == b) return N-a;
		int t0 = isa[a], t1 = isa[b];
		if (t0 > t1) swap(t0,t1);
		return R.query(t0,t1-1);
	}
};

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	
	int q; cin >> q;
	vector<int> len;
	string s = "";
	while (q--)
	{
		string p; cin >> p;
		reverse(p.begin(), p.end());
		len.pb(p.size());
		s += p;
	}
	int n = s.size();
	reverse(s.begin(), s.end());
	SuffixArray Suf;
	Suf.init(s);
	vector<ll> distinct(s.size(), 0);
	
	auto &sa = Suf.sa;
	vector<int> inv(n, 0);
	for (int i = 0; i < n; ++i)
		inv[sa[i]] = i;
	set<int> active;
	for (int i = n-1; i >= 0; --i)
	{
		distinct[i] = s.size() - i;
		if (n == 1) break;
		active.insert(inv[i]);
		auto it = active.find(inv[i]);
		int y = 0;
		if (it != active.begin())
		{
			auto it2 = it; --it2;
			y = Suf.getLCP(i, sa[*it2]);
		}
		++it;
		if (it != active.end()) y = max(y, Suf.getLCP(i, sa[*it]));
		distinct[i] -= y;
	}
	reverse(distinct.begin(), distinct.end());
	for (size_t i = 1; i < s.size(); ++i)
		distinct[i] += distinct[i-1];
	int cur = 0;
	for (auto x : len)
	{
		cur += x;
		cout << distinct[cur-1] << ' ';
	}
}