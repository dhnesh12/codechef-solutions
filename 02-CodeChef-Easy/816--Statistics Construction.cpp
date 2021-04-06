#include<bits/stdc++.h>
#define Harsh_Srivastava std::ios::sync_with_stdio(false);
#define H_S std::cin.tie(nullptr);
#define F first
#define S second
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define mp make_pair
#define mt make_tuple
#define FL cout.flush()
#define all(x) (x).begin(),(x).end()
#define mem(x,i) memset((x),(i),sizeof((x)))
#define ll long long
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

ll sum=0;





void solve(){
    ll n;
   std::cin >> n;
		for(int i = 1; i <= n; ++i) {
			std::cout << 2*i;
			if (i < n) {
				std::cout << " ";
			}
			else {
				std::cout << "\n";
			}
		}
}


int main() {
    Harsh_Srivastava
    H_S
    ll t;
    std::cin>>t;
    while(t--) solve();
	return 0;
}
