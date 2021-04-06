#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define debp(...) cerr << "[ "<< #__VA_ARGS__": "<< __VA_ARGS__<<"]"<<endl

long long pw[100001];


int main()
{
  int t;
  cin >> t;

  while(t--)
  {
    int i, n, k;
    int sTree[400001];
    cin >> n>>k;
    std::vector<long long> v(n);
    for(auto &a: v)
    {
      cin >> a;
    }
    sort(all(v));
    int comp = 0;
    long long prev= -1;
    map<int, long long> mp;
    std::vector<int> V(n);
    int cnt[100001]={0};
    for(i=0;i<n;i++)
    {
      if(v[i]!=prev)
      {
        mp[comp]=v[i];
        comp++;prev= v[i];
      }
      V[i]=comp;
      cnt[V[i]]++;
    }
    for(i=0;i<=100000;i++)
      cnt[i] = cnt[i]%k;
    std::vector<pair<int,int>> ans;
    int count = 0;
    for(i=100000;i>=0;i--)
    {
      if(cnt[i]!=0)ans.push_back(make_pair(i, cnt[i]));
    }
    if(ans.size()==0){cout<<0<<endl;continue;}
    auto build = [&ans, &sTree]()
    {
      int n = ans.size();
      for(int i =0;i<n;i++){
        sTree[n+i] = i;
      }
      for(int i = n-1;i>=1;i--)
      {
        if(ans[sTree[2*i]].S == ans[sTree[2*i+1]].S)
          sTree[i] = min(sTree[2*i], sTree[2*i+1]);
        else if(ans[sTree[2*i]].S > ans[sTree[2*i+1]].S)
          sTree[i] = sTree[2*i];
        else sTree[i] = sTree[2*i+1];
      }
    };
    auto update = [&](int pos)
    {
      pos+=ans.size();
      //sTree[pos]=0;
      while(pos>1){
        pos = pos>>1;
        //sTree[pos] = max(sTree[2*pos], sTree[2*pos+1]);
        if(ans[sTree[2*pos]].S == ans[sTree[2*pos+1]].S)
          sTree[pos] = min(sTree[2*pos], sTree[2*pos+1]);
        else if(ans[sTree[2*pos]].S > ans[sTree[2*pos+1]].S)
          sTree[pos] = sTree[2*pos];
        else sTree[pos] = sTree[2*pos+1];
      }
    };
    auto query = [&](int l, int r)
    {
      int n = ans.size();
      l+=n; r+=n;
      int ma = INT_MIN;
      int pos=INT_MAX;
      while(l<r)
      {
        if(l&1){
          if(ans[sTree[l]].S > ma)
          {
            ma = ans[sTree[l]].S; pos = sTree[l];
          }
          else if(ans[sTree[l]].S == ma) pos = min(sTree[l], pos);
          l++;
        }
        if(r&1){
          r--;
          if(ans[sTree[r]].S > ma)
          {
            ma = ans[sTree[r]].S;
            pos = sTree[r];
          }
          else if(ans[sTree[r]].S == ma) pos = min(sTree[r], pos);
        }
        l = l >> 1;
        r = r >> 1;
      }
      return pos;
    };

    build();

    int N = ans.size(), mx;
    int sum = 0, X=0;
    for(i=N-1;i>=0; i--)
    {
      int pos;
      pos = query(i,(int)ans.size());
      sum+=ans[i].S;
      if(sum>0)
      {
        sum -=k;
        X+=(k-ans[pos].S);
        ans[pos].S=0;
        update(pos);
      }
      //sum+= ans[i].S;
    }
    cout<<X<<endl;
  }
  return 0;

}
