#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+100;
typedef long long ll;
#define fr(i,a,b) for(int i = a;i <= b; ++i)
#define nfr(i,a,b) for(int i = a;i >= b; --i)
#define pb push_back

struct SAM{
   int cnt,l[N],nxt[N][26],fa[N];
   ll siz[N],siz2[N];
   inline void init(){
      cnt = 1;
      l[1] = fa[1] = 0;
      memset(nxt[1],0,sizeof nxt[1]);
   }
   inline int add(int x,int lst){
      int np = ++cnt,p = lst;
      l[np] = l[p]+1;
      while(p && !nxt[p][x])nxt[p][x] = np,p = fa[p];
      if(!p)fa[np] = 1;
      else {
         int q = nxt[p][x];
         if(l[q] == l[p]+1)fa[np] = q;
         else {
            int nq = ++cnt;
            l[nq] = l[p]+1;
            fa[nq] = fa[q]; fa[np] = fa[q] = nq;
            memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
            while(nxt[p][x] == q)nxt[p][x] = nq,p = fa[p];
         }
      }
      return np;
   }
   int cntL[N],posL[N];
   void sort(){
      fr(i,0,cnt)cntL[i] = 0;
      fr(i,1,cnt)cntL[l[i]]++;
      fr(i,1,cnt)cntL[i] += cntL[i-1];
      fr(i,1,cnt)posL[cntL[l[i]]--] = i;
   }
   void solve(){
      sort();
      nfr(i,cnt,1){
         int x = posL[i];
         siz[x] += l[x]-l[fa[x]];
         siz[fa[x]] += siz[x];
         fr(j,0,25)siz2[x] += siz2[nxt[x][j]];
         siz2[x]++;
      }
   }
}s;

char ch[N];
vector<int> edge[N];
void dfs(int x,int fa,int lst){
   lst = s.add(ch[x]-'a',lst);
   fr(i,0,(int)edge[x].size()-1){
      int y = edge[x][i];
      if(y == fa)continue ;
      dfs(y,x,lst);
   }
}

inline char read_char(){
   char ch1;
   for(ch1 = getchar();ch1 == ' ' || ch1 == '\n';ch1 = getchar());
   return ch1;
}

int n,q;
int main(){
//   freopen("a4.in","r",stdin);
 //  freopen("a4.ans","w",stdout);
   scanf("%d%d",&n,&q);
   s.init();
   scanf("%s",ch+1);
   fr(i,1,n-1){
      int u,v; scanf("%d%d",&u,&v);
      edge[u].pb(v); edge[v].pb(u);
   }
   dfs(1,0,1);
   s.solve();
   printf("%lld\n",s.siz[1]+1);
   fr(i,1,q){
      char str[28]; ll k;
      scanf("%s",str); scanf("%lld",&k);
      if(k > s.siz[1]+1)puts("-1");
      else {
         int cur = 1;
         while(cur){
            if(k <= 1)break;
            k --;
            fr(j,0,25){
               if(s.siz2[s.nxt[cur][str[j]-'a']] < k){
                  k -= s.siz2[s.nxt[cur][str[j]-'a']];
               } else {
                  putchar(str[j]);
                  cur = s.nxt[cur][str[j]-'a']; break;
               }
            }
         }
         puts("");
      }
   }
   return 0;
}
