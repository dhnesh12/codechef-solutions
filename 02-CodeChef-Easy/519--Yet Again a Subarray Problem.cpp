/*
Author: Nachiket Kanore
Created: Saturday 20 February 2021 03:33:31 PM IST
(ツ) Here is one quality that one must possess to win, and that is definiteness of purpose, the knowledge of what one wants, and a burning desire to possess it.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <string>
#include <cstring>

#define int long long
#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = (L); i <= (R); i++)
using namespace std;

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } 

const int N = 2005;
int n, a[N], k, occ[N+1][N+1], occUpto[N+1][N+1];

int get_kth(int L, int R) {
	int ret = -1, len = R-L+1;
	int lo = 1, hi = 2000;
	int times = (k + len - 1) / len;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int sum_of_smallest_mid_values_in_subarray = times * (occUpto[mid][R] - occUpto[mid][L-1]);
		if (sum_of_smallest_mid_values_in_subarray >= k) {
			ret = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	assert(~ret);
	return ret;
}

void solve() {
	memset(a, 0, sizeof(a));
	memset(occ, 0, sizeof(occ));
	memset(occUpto, 0, sizeof(occUpto));
	cin >> n >> k;
	FOR (i,1,n) {
		cin >> a[i];
		FOR (val,1,N)
			occ[val][i] = occ[val][i-1];
		occ[a[i]][i]++;
	}
	FOR (val,1,N) {
		FOR (i,1,n) {
			occUpto[val][i] = occUpto[val-1][i] + occ[val][i];
		}
	}
	int answer = 0;
	FOR (i,1,n) FOR (j,i,n) {
		int who = get_kth(i, j);
		int itsOcc = occ[who][j] - occ[who][i-1];
		itsOcc = occ[itsOcc][j] - occ[itsOcc][i-1];
		answer += itsOcc > 0;
	}
	cout << answer << '\n';
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T;	cin >> T;
	while (T--) solve();
}
