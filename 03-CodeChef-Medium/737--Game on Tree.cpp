#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;
#define sz 300008
#define mod 1000000007
#define f first
#define s second
#define pa pair<ll,ll>
ll arr[sz+10],brr[sz+10],crr[sz],a,n;   
std::vector<ll> v[sz];
void bfs(ll node,ll par)
{
  ll mx=0;
  for(int i=0;i<v[node].size();i++)
  {
    ll x=v[node][i];
    if(x==par)
       continue;
    bfs(x,node);
    mx=max(mx,arr[x]);
    arr[node]+=arr[x];
  }
  arr[node]++;
  mx=max(mx,n-arr[node]);
  if((2*mx)<=n && n%2==0)
brr[node]=1;
//arr[node]++;
return;
}
int main()
{
 /// ios_base::sync_with_stdio(0);cin.tie(0);
  int test_case=1;
  scanf("%d",&test_case);
  while(test_case--)
  {
  scanf("%lld",&n);
  for(int i=1;i<n;i++)
  {
    ll a,b;
    scanf("%lld %lld",&a,&b);
    v[a].push_back(b);
    v[b].push_back(a);
  }
  a=(n+1)/2-1;
  //if(n%2)
  bfs(1,-1);
  for(int i=1;i<=n;i++)
  {
    printf("%lld",brr[i]);
    arr[i]=brr[i]=0;
    v[i].clear();
  }
  printf("\n"); 
  }
  return 0;
}