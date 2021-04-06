#include<cstdio>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<numeric>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;

#define ALL(t) t.begin(),t.end()
#define FOR(i,n) for (int i=0; i<(int)(n); i++)
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
typedef vector<int> vi;
typedef long long int64;

int n,e[20],ans,ans_set,nbr[1<<20],cnt[1<<20];
#define __builtin_popcount(x) cnt[(x)]
bool find(int take){
  int take2=(1<<n)-1-take;
  FOR(i,n)if(take&1<<i && __builtin_popcount(e[i]&take2)>__builtin_popcount(e[i]&take))return 1;
  for(int check=take;check;check=(check-1)&take)if(__builtin_popcount(nbr[check]&take2)>__builtin_popcount(nbr[check]&take))return 1;
  return 0;
}
int main() {
  int m;
  for(int i=1;i<(1<<20);i++)cnt[i]=1+cnt[i&i-1];
  while(scanf("%d %d",&n,&m),n){
    FOR(i,n)e[i]=1<<i;
    while(m--){
      int x,y;
      scanf("%d %d",&x,&y);
      x=n-1-x;
      y=n-1-y;
      e[x]|=1<<y;
      e[y]|=1<<x;
    }
    ans=n;
    ans_set=(1<<n)-1;
    for(int i=1;i<(1<<n);i++){
      int j=0;
      while(!(i&1<<j))j++;
      nbr[i]=nbr[i-(1<<j)]|e[j];
    }
    for(int take=(1<<n)-1;take;take--){
      if(__builtin_popcount(take)>=ans)goto fail;
      if(__builtin_popcount(take)*2<n)goto fail;
      FOR(i,n)if(!(take&1<<i)&&!(e[i]&take))goto fail;
      if(!find(take)){ans=__builtin_popcount(take);ans_set=take;}
fail:;
    }
    printf("%d",ans);FOR(i,n)if(ans_set&1<<n-1-i)printf(" %d",i);puts("");
  }
  return 0;
}
