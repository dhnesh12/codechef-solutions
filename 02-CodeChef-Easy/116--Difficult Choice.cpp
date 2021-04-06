#include<bits/stdc++.h>
    using namespace std;

    ///***********SICK BOY******************///
    #define uli unsigned long long int
    ///***input******// for +ve int
    inline uli in() {
        uli p=0; register char ch=0;
        while(ch<'0' or ch>'9') {ch=getchar();}
        while(ch>='0' and ch<='9') {p=(p<<1)+(p<<3)+ch-'0'; ch=getchar();}
        return p;
    }
    ///***output*****// for +ve int
    #define pc(x) putchar(x)
    inline void dukya(uli n){
            uli N = n, rev, count_ = 0;
            rev = N;
            if (N == 0) { pc('0'); pc('\n'); return ;}
            while ((rev % 10) == 0) { count_++; rev /= 10;}
            rev = 0;
            while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}
            while (rev != 0) { pc(rev % 10 + '0'); rev /= 10;}
            while (count_--) pc('0');
           pc('\n');
        }
    ///
    #define li  long long int
    #define ld  long double
    #define chal(n) for(li i=0;i<n; ++i)
    #define ot(n) cout<<n<<"\n"
    #define vi vector<li>
    #define ii pair<li, li>
    #define ict int test_case=in(); while(test_case--)
    #define INF 1000000000009
    #define mod 1000000007
    #define fastScan ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
    ///***************SICK BOY*************************//

li n;
vi adj[100005];
li cnt[4][2];
li bval[100005];

void dfs(li u, li p, li path)
{
 cnt[bval[u]][path%2]++;
 chal(adj[u].size())
 {
   if(adj[u][i]!=p)
   dfs(adj[u][i], u, path+1);
 }
}

int main(){

ict
{
   n=in();
   memset(cnt, 0, sizeof cnt);
  chal(n)
  adj[i].clear();
  li u,  v;
  chal(n-1)
  {
   u=in()-1, v=in()-1;
   adj[u].push_back(v);
   adj[v].push_back(u);
  }
  chal(n)
  {
   li val=in();
   li co=0;
   while(val)
   {
   ++co;
   val-=val&(-val);
   }
   bval[i]=co%2;
   //ot(co);
  }

  dfs(0, -1, 0);
  li ans=0;
  for(li a=0; a<2; ++a)
    for(li b=0; b<2; ++b)
      for(li c=0; c<2; ++c)
        for(li d=0; d<2; ++d)
          if((a^b)!=(c^d))
            ans+=(cnt[a][b]*cnt[c][d]);
  //ot(cnt[0][0]<<" "<<cnt[0][1]<<" "<<cnt[1][0]<<" "<<cnt[1][1]);
  ans/=2;
  ot(ans);
}


	return 0;
}
