#include <bits/stdc++.h>
using namespace std;
long int a[1000006];
long int n;
bool comp(pair<string,pair<int,int>> a,pair<string,pair<int,int>> b)
{
    if(a.second.first!=b.second.first)
    {
  return a.second.first<b.second.first;
    }
  
    return a.second.second<b.second.second;

}
void solve()
{
    map<string,pair<int,int>> mp;
string teamA,teamB,tok;
int scoreA,scoreB;
for(int i=0;i<12;i++)
{
    cin>>teamA>>scoreA>>tok>>scoreB>>teamB;




if(scoreA>scoreB)
{
    mp[teamA].first+=3;
}else if(scoreB>scoreA)
{
    mp[teamB].first+=3;
}
else
{
    mp[teamA].first+=1;
    mp[teamB].first+=1;
}
mp[teamA].second+=(scoreA-scoreB);
mp[teamB].second+=(scoreB-scoreA);
}

vector<pair<string,pair<int,int>>> v;
for(auto x: mp )
{
    v.push_back(x);
}
sort(v.begin(),v.end(),comp);


cout<<v[v.size()-1].first<<" "<<v[v.size()-2].first<<endl;
}

int main()
{
   long int t;
    cin>>t;
    while(t--)
    {

        solve();
    }
    return 0;
}