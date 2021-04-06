#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);
#define endl "\n"
int main() {
	// your code goes here
	fast
	int t;cin>>t;
	while(t--)
	{
	    int n,k;cin>>n>>k;
	    set<int> r,c;
	    for(int i=1;i<=n;i++)
	    r.insert(i),c.insert(i);
	    int x,y;
	    for(int i=0;i<k;i++)
	    {
	        cin>>x>>y;
	        r.erase(x),c.erase(y);
	    }
	    vector<pair<int,int>> v;
	    
	    while(r.size()!=0 && c.size()!=0)
	    {   auto a=r.begin(),b=c.begin();
	        v.push_back({(*a),(*b)});
	        r.erase(*a),c.erase(*b);
	    }
	    cout<<v.size()<<" ";
	    for(auto i:v)
	    cout<<i.first<<" "<<i.second<<" ";
	    cout<<endl;
	}
	return 0;
}
