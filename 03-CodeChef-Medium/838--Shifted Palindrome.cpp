#include <bits/stdc++.h>
// iostream is too mainstream
#include <cstdio>
// bitch please
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <cmath>
#include <iomanip>
#include <time.h>
#define dibs reserve
#define OVER9000 1234567890
#define ALL_THE(CAKE,LIE) for(auto LIE =CAKE.begin(); LIE != CAKE.end(); LIE++)
#define tisic 47
#define soclose 1e-8
#define chocolate win
// so much chocolate
#define patkan 9
#define ff first
#define ss second
#define abs(x) (((x) < 0)?-(x):(x))
#define uint unsigned int
#define dbl long double
#define pi 3.14159265358979323846
using namespace std;
// mylittledoge
 
using cat = long long;
 
#ifdef DONLINE_JUDGE
	// palindromic tree is better than splay tree!
	#define lld I64d
#endif
 
const cat mod[2] = {1'000'000'007, 1'000'000'009};
const cat p = 26;
 
int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);
	int T;
	cin >> T;
	for(int t = 0; t < T; t++) {
		string S;
		cin >> S;
		int N = S.length();
		S = S + S;
 
		vector<cat> H[2], Hi[2];
		vector<cat> pw[2];
		for(int k = 0; k < 2; k++) {
			H[k].resize(2*N+1, 0);
			Hi[k].resize(2*N+1, 0);
			for(int i = 0; i < 2*N; i++)
				H[k][i+1] = (H[k][i] * p + S[i]-'a'+1) % mod[k];
			for(int i = 2*N-1; i >= 0; i--)
				Hi[k][i] = (Hi[k][i+1] * p + S[i]-'a'+1) % mod[k];
			pw[k].resize(2*N+1, 1);
			for(int i = 1; i <= 2*N; i++) pw[k][i] = (pw[k][i-1] * p) % mod[k];
		}
 
		int ans = 0;
		for(int i = 0; i < N; i++) {
			cat hash_direct[2], hash_inverse[2];
			for(int k = 0; k < 2; k++) {
				hash_direct[k] = (H[k][i+N] - pw[k][N] * H[k][i]) % mod[k];
				if(hash_direct[k] < 0) hash_direct[k] += mod[k];
				hash_inverse[k] = (Hi[k][i] - pw[k][N] * Hi[k][i+N]) % mod[k];
				if(hash_inverse[k] < 0) hash_inverse[k] += mod[k];
			}
			cat hd = hash_direct[0] * mod[1] + hash_direct[1];
			cat hi = hash_inverse[0] * mod[1] + hash_inverse[1];
			if(hd == hi) ans++;
		}
		cout << ans << "\n";
	}
	return 0;
    
}