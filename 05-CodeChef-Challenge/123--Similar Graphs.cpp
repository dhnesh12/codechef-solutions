#include <iostream>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <cassert>
#include <queue>
#include <cstring>
#include <cstdio>
#include <iomanip>
using namespace std; 
#define mod 1000000007
 
typedef unsigned int uint; 
typedef long long int64; 
typedef unsigned long long uint64; 
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef long long int ll;
typedef long long LL;
typedef unsigned long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;
 
#define rep(i,a,b) for(int i = a; i < b; i++)
#define gi(n) scanf("%d",&n)
#define gi2(x,y) scanf("%d%d",&x,&y)
#define gl(n) cin >> n
#define pi(n) printf("%d",n)
#define pl(n) cout << n
#define pss printf(" ")
#define pn printf("\n")
const int INF = 0x7f7f7f7f;
//ios_base::sync_with_stdio(false);

int main() {
	int t,n;
	gi(t);
	while(t--) {
		gi(n);
		int g1[n][n],g2[n][n];
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				gi(g1[i][j]);
			} 
		}
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				gi(g2[i][j]);
			} 
		}
		for(int i=1;i<=n;i++) cout<<i<<" ";
		pn;
		for(int i=1;i<=n;i++) cout<<i<<" ";
		pn;
	}
}