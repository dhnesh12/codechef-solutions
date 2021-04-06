#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define forr(i,v) for (int i = 0; i < v; i++)
#define each(i,v) for (auto i: v)
#define forrr(i,j,v,w) for (int i = 0; i < v; i++) for (int j = 0; j < w; j++)
#define in(A, B, C) assert( B <= A && A <= C)
#define ni(x) int x; cin >> x;
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define rz resize
#define inf (int)1e9
#define eps 1e-9
#define pi 3.1415926535897932384626433832795
#define mod 1000000007
#define read(type) readInt<type>()
#define W() int T; cin >> T; while(T--)
#define trace(x) cerr<<#x<<": "<<x<<endl;
#define output()
#define ff first
#define float double
typedef string str;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<pii> vpii;
typedef vector<vi> vii;
typedef map<int,int> mpii;
typedef set<int> seti;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
typedef long long ll;

template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }

void out(vi v){
    for (int i:v){
        cout << i << ", ";
    }
    cout << endl;
}
void out(vii v){
    for (vi i:v){
        for (int j: i){
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << "__________" << endl;
}

vpii v;
int N;
void solve(){
    sort(all(v));
    int d =0, n = 0;
    each(a,v){
        if (a.ss > d){
            n++;
            d = a.ff;
        }
    }
    cout << n << endl;
    
}
int main()
{
    cin >> N;
    v.rz(N);
    forr(i,N){
        cin >> v[i].ss >> v[i].ff;
        v[i].ff += v[i].ss;
    }
    solve();
	return 0;
}

/*
4
2 5
9 7
15 6
9 3

4
2 5
9 7
9 3
15 6
*/