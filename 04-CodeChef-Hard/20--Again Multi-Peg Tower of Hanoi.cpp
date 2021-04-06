#include <bits//stdc++.h>
using namespace std;
#define ll  long double

struct ext{
 ll mov,mx;
int cnt;
   ext(){}
   ext(ll _mov,ll _mx,int _cnt)
   {
       mov=_mov;
       mx=_mx;
       cnt=_cnt;
   }
   bool operator <(const ext&p)const{

      if(mov!=p.mov)return mov<p.mov;
      if(mx!=p.mx)return mx>p.mx;
      return cnt>p.cnt;
   }
};
ext mini(ext a,ext b)
{
   if(a.mov!=b.mov){
      if(a.mov>b.mov)return b;
      return a;
   }
   if(a.mx!=b.mx)
   {
      if(b.mx>a.mx)return b;
      return a;
   }
   if(b.cnt>a.cnt)return b;
   return a;

}
ext dp[200][80];
bool vis[200][80];
ll big=2e18;
ext dp_func(int rem,int pag)
{
    assert(rem);
   if(pag==0)return ext(big,big,0);
   if(rem==1)return ext(1,1,1);
   if(vis[rem][pag])return dp[rem][pag];
   if(pag<=2)return ext(big,big,0);

   ext ans=ext(big,big,0);
   for(int j=1;j<rem;j++)
   {
       if(pag==3&&j!=rem-1)continue;
       ext ps=dp_func(j,pag);
       ext rs=dp_func(rem-j,pag-1);
       ext ret;
       ret.mov=ps.mov*2+rs.mov;
       ps.mx*=2;
       if(ret.mov>=big)continue;
       if(ps.mx>rs.mx)
       {
           ret.mx=ps.mx;
           ret.cnt=ps.cnt;

       }
       else if(rs.mx>ps.mx)
       {
           ret.mx=rs.mx;
           ret.cnt=rs.cnt;
       }
       else{
          ret.mx=ps.mx;
          ret.cnt=ps.cnt+rs.cnt;
       }
     //  if(rem==6&&pag==3)cout<<ret.mx<<" "<<ret.cnt<<" "<<ret.mov<<ans.mx<<" "<<ans.cnt<<" "<<ans.mov<<" "<<j<<" "<<" "<<rs.mov<<" "<<ret.mov<<endl;
       ans=mini(ans,ret);
   }
   vis[rem][pag]=1;
   return dp[rem][pag]=ans;

}
int main()
{
    int i,j,k,l,m,n;
    while(cin>>n>>m)
    {
        if(n==0&&m==0)break;
        ext ret=dp_func(n,m);
         int ans=ret.cnt;
         //cout<<ret.mov<<endl;
         if(m==3)ans=1;
        printf("%d\n",ans);
    }
}
///ssadsd