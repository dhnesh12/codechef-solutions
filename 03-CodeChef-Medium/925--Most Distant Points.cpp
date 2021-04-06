#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <map>
#define for1(x,y) for(long long x = 1; x<ll(y); x++)
#define forn(x,y,z) for(long long x = y; x< ll(z); x++)
#define for0(x,y,z) for(long long x = y; x< ll(z); x++)
# define pii pair<int,int>
# define ff first
# define ss second
# define pb push_back

#define forn(x,y,z) for(long long x = y; x< ll(z); x++)
#define for0(x,y,z) for(long long x = y; x< ll(z); x++)
using namespace std;
typedef long long ll;
typedef long double ld;	
long double PI = 3.14159265359;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
const int MAXQ = 5e5 + 10;

void solve()
{
	int q;
	cin >> q;
	int ans = 0;
	priority_queue<pii> pq[4];
	int id = 0;
	vector<bool> is_removed(MAXQ);
	while(q--){
		char op;
		cin >> op;
		if(op=='+'){
			int x, y;
			cin >> x >> y;
			x ^= ans;
			y ^= ans;
			id++;
			pq[0].push({x+y, id});
			pq[1].push({-x-y, id});
			pq[2].push({x-y, id});
			pq[3].push({y-x, id});
		}
		else if(op=='-'){
			int n;
			cin >> n;
			n ^= ans;
			is_removed[n] = true;
		}
		else{
			int x, y;
			cin >> x >> y;
			x ^= ans;
			y ^= ans;
			int tmp[4];
			tmp[0] = x+y;
			tmp[1] = -x-y;
			tmp[2] = x-y;
			tmp[3] = y-x;
			ans = 0;
			for(int i=0; i<4; i++){
				while(is_removed[pq[i].top().ss])
					pq[i].pop();
				ans = max(ans, pq[i].top().ff-tmp[i]);
			}
			cout << ans << endl;
		}
	}
	return;		
}


int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
	int test;
	//cin >> test;
	//while(test--)
		solve();
	return 0;
}
