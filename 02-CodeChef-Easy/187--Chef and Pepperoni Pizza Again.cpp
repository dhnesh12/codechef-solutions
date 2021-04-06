#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <map>
#include <string> 
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip> 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
//setbase - cout << setbase (16)a; cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 <<endl;prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val
 
using namespace std;
using namespace __gnu_pbds;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define fd(i,a,b) for(i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define vi vector< int >
#define vl vector< ll >
#define ss second
#define ff first
#define ll long long
#define pii pair< int,int >
#define pll pair< ll,ll >
#define sz(a) a.size()
#define inf (1000*1000*1000+5)
#define all(a) a.begin(),a.end()
#define tri pair<int,pii>
#define vii vector<pii>
#define vll vector<pll>
#define viii vector<tri>
#define mod (1000*1000*1000+7)
#define pqueue priority_queue< int >
#define pdqueue priority_queue< int,vi ,greater< int > >
//#define int ll
 
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
 
 
//std::ios::sync_with_stdio(false);
 
int vis[155][6005][2],dp[155][6005][2],nxt[155][6005][2];
int arr[155];
string s[155];
int n,iter=0;
main(){
	std::ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin>>t;
	//t=1;
	while(t--){
		int i,j,c=0,sum,pos,fl,fl1,lim;
		cin>>n;
		iter++;
		for(i=0;i<n;i++){
			cin>>s[i];
		}
		for(i=0;i<n;i++){
			c=0;
			for(j=0;j<n/2;j++){
				c+=(s[i][j]-'0');
			}
			for(j=n/2;j<n;j++){
				c-=(s[i][j]-'0');
			}
			arr[i]=c;
		}
		lim=6000;
		f(i,-1*lim,lim){
			fl=0;
			if(i<0){
				fl=1;
			}
			dp[n][abs(i)][fl]=abs(i);
		}
		fd(i,n-1,0){
			f(j,-1*lim,lim){
				fl=0;
				if(j<0){
					fl=1;
				}
				dp[i][abs(j)][fl]=inf;
				if(j+arr[i]<lim&&j+arr[i]>=-1*lim){
					fl1=0;
					if(j+arr[i]<0){
						fl1=1;
					}
					dp[i][abs(j)][fl]=min(dp[i][abs(j)][fl],dp[i+1][abs(j+arr[i])][fl1]);
					nxt[i][abs(j)][fl]=1;
				}
				if(j-arr[i]<lim&&j-arr[i]>=-1*lim){
					fl1=0;
					if(j-arr[i]<0){
						fl1=1;
					}
					dp[i][abs(j)][fl]=min(dp[i][abs(j)][fl],dp[i+1][abs(j-arr[i])][fl1]);
					if(dp[i][abs(j)][fl]==dp[i+1][abs(j-arr[i])][fl1]){
						nxt[i][abs(j)][fl]=-1;
					}
				}
 
			}
		}
		sum=0;
		pos=0;
		while(pos!=n){
			fl=0;
			if(sum<0){
				fl=1;
			}
			if(nxt[pos][abs(sum)][fl]==1){
				cout<<s[pos]<<endl;
				sum+=arr[pos];
			}
			else{
				sum-=arr[pos];
				reverse(s[pos].begin(),s[pos].end());	
				cout<<s[pos]<<endl;
			}
			pos++;
		}
	}
	return 0;
} 