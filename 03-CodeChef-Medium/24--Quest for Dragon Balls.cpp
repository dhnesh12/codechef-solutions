#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define fix(f,n) std::fixed<<std::setprecision(n)<<f

typedef long long ll;

ll mod = 1e9 + 7;
 
using namespace std;
using namespace __gnu_pbds;
 
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>; 

#ifndef ONLINE_JUDGE
template<typename T>
void __p(T a) {
	cout<<a;
}
template<typename T, typename F>
void __p(pair<T, F> a) {
	cout<<"{";
	__p(a.first);
	cout<<",";
	__p(a.second);
	cout<<"}";
}
template<typename T>
void __p(std::vector<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it<a.end(); it++)
		__p(*it),cout<<",}"[it+1==a.end()];
}
template<typename T>
void __p(std::set<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it!=a.end();){
		__p(*it); 
		cout<<",}"[++it==a.end()];
	}
 
}
template<typename T>
void __p(std::multiset<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it!=a.end();){
		__p(*it); 
		cout<<",}"[++it==a.end()];
	}
}
template<typename T, typename F>
void __p(std::map<T,F> a) {
	cout<<"{\n";
	for(auto it=a.begin(); it!=a.end();++it)
	{
		__p(it->first);
		cout << ": ";
		__p(it->second);
		cout<<"\n";
	}
	cout << "}\n";
}
 
template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
	__p(a1);
	__p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
	cout<<name<<" : ";
	__p(arg1);
	cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
	int bracket=0,i=0;
	for(;; i++)
		if(names[i]==','&&bracket==0)
			break;
		else if(names[i]=='(')
			bracket++;
		else if(names[i]==')')
			bracket--;
	const char *comma=names+i;
	cout.write(names,comma-names)<<" : ";
	__p(arg1);
	cout<<" | ";
	__f(comma+1,args...);
}
#define trace(...) cout<<"Line:"<<__LINE__<<" ", __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...)
#endif

struct edge{
	int a, b, weight;
};
		
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
		
long long modInverse(long long a, long long m) { 
    if(__gcd(a, m) != 1){
		throw "modular inverse does not exist.";
	}
	long long m0 = m;
    long long y = 0, x = 1; 
    if (m == 1) return 0; 
    while (a > 1) {  
        long long q = a / m; 
        long long t = m;  
        m = a % m, a = t; 
        t = y; 
        y = x - q * y; 
        x = t; 
    }  
    if (x < 0) 
       x += m0; 
    return x; 
} 

vector<int> sieveOfEratosthenes(int n) {
	vector<int> primes;
	bool prime[n + 1];
	memset(prime, true, sizeof(prime));
	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}
	for (int p = 2; p <= n; p++)
		if (prime[p])
			primes.push_back(p);
	return primes;
}

int add(int a, int b) {
	a += b;
	if (a >= mod) a -= mod;
	return a;
}
 
int sub(int a, int b) {
	a -= b;
	if (a < 0) a += mod;
	return a;
}
 
int mul(ll a, int b) {
	return (a * b) % mod;
}

int divide(int a, int b, int m) {
	a = mul(a, modInverse(b, mod));
	return a;
}
 
int pwr(int x, int e) {
	int res = 1;
	while (e) {
		if (e & 1) {
			res = mul(res, x);
		}
		x = mul(x, x);
		e /= 2;
	}
	return res;
}
 
void solve() {
	int n;
	cin >> n; 
	vector<int> a(n); 
	for(int i = 0; i < n; i++) {
		cin >> a[i]; 
	}
	bool poss = 0; 
	int ev = 0; 
	int od = 0; 
	ll sum = 0; 
	for(int i = 0; i < n; i++) {
		if(i < n-1 && (a[i] - a[i+1]) % 2 == 0) {
			poss = 1;
		}
		if(a[i] % 2) od++; 
		else ev++;
		sum += a[i]; 
	}
	
	if(!poss) {
		cout << n << "\n"; 
		for(int an: a) cout << an << " "; 
		cout << "\n"; 
	} else {
		int k = 1;
		if((ev - od) % 3 == 0) {
			k = 2; 
			if(a[0] % 2) od--;
			else ev--;
			sum -= a[0];  
		}
		int m = (((ev - od) % 3) + 3) % 3; 
		ll fin = sum; 
		if(m == 1) {
			fin += (2*(ev-1) + od)/3; 
		} else {
			fin += (2*ev + od - 1)/3; 
		}
		cout << k << "\n"; 
		if(k == 2) cout << a[0] << " "; 
		cout << fin << "\n"; 
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	cin >> t;
	for (int i = 0; i < t; i++) {
		solve();
	}
	return 0;
}
