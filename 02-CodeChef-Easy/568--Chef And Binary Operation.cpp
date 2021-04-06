#include<bits/stdc++.h>
using namespace std;
#define int long long
#define float double
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)
#define vi vector<int>
#define vl vector<long>
#define fill(a,b) memset(a,b,sizeof a)
#define ff first
#define ss second
#define sync ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);



signed main()
{
	int tc;
	cin>>tc;
	while(tc--){
		string s,p;
		cin>>s>>p;
		int cnt=0,cnt1=0,cnt2=0;
		for(auto e:s){
			if(e=='0') cnt1++;
			else cnt2++;
		}
		if(s!=p && (cnt1==0 || cnt2==0)){
			cout<<"Unlucky Chef"<<endl;
		}
		else{
			if(s==p) {
				cout<<"Lucky Chef"<<endl;
				cout<<"0"<<endl;
			}
			else{
				int cnt1=0,cnt0=0;
				for(int i=0;i<s.size();i++){
					if(s[i]!=p[i]) if(s[i]=='1') cnt1++;
					else if(s[i]!=p[i]) cnt0++;
				}
				cout<<"Lucky Chef"<<endl;
				cout<<cnt1+cnt0-min(cnt0,cnt1)<<endl;
			}
		}
	}
}
