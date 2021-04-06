#include <bits/stdc++.h>
#define ll long long
#define S set<int>
#define V vector<int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
        ll n,m,c=0;
        cin>>n>>m;
        V a(n),b(m);
        for(auto &i:a)cin>>i;
        for(auto &i:b)cin>>i;
       S s;
       vector<pair<int,int>> ans;
       ll temp=0;
       for(ll i=0;i<n;i++)
       for(ll j=0;j<m;j++)
       {
          s.insert(a[i]+b[j]);
          if(temp!=s.size())
          {ans.push_back({i,j});
          c++;
              temp=s.size();
          }
          if(c==(n+m-1))break;
          
       }
       for(ll i=0;i<n+m-1;i++)
       cout<<ans[i].first<<" "<<ans[i].second<<endl;
    
	return 0;
}
