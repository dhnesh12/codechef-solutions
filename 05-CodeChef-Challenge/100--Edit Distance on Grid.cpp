#include<bits/stdc++.h>
const unsigned long long int M= 1000000007;
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()	
#define fr(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define int long long 
#define endl "\n"
using namespace std;
int power(int x,int y){int res=1;while(y>0){if(y&1)res=x*res; y=y>>1;x=x*x;}return res;}
int power(int x,int y,int mod){int res=1;while(y>0){if(y&1)res=x*res%mod; y=y>>1;x=x*x%mod;}return res;}

void nik()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif
}

 	#define F first 
	#define S second 

signed main()
{
	nik();
	int test=1;
	cin>>test;
	while(test--)
	{
		
		int n,m,a,b;
		cin>>n>>m>>a>>b;
		string s[n];

		int black=0,white=0;
		std::vector<pair<int,int>> v,v1;
		fr(i,n)cin>>s[i];
		fr(i,n)fr(j,m)if(s[i][j]=='B')v.pb({i+1,j+1}),black++;else v1.pb({i+1,j+1}),white++;
		int ans1=black*b;
		int ans2=white*a;
		if(ans1<=ans2)
		{cout<<black<<endl;
		for(auto it:v)cout<<"3 "<<it.F<<" "<<it.S<<endl;}
		else 
		{

			cout<<white<<endl;
		for(auto it:v1)cout<<"2 "<<it.F<<" "<<it.S<<endl;
		}
	}
return 0;
}

