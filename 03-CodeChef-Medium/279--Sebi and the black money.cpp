/*
 © 2020-04-13 09:35:01 crystaalroo all Rights Reserved
*/

#include <bits/stdc++.h>

#define f first
#define s second
#define fore(i,a,b) for(int i = (a), ThxMK = (b); i < ThxMK; ++i)
#define pb push_back
#define all(s) begin(s), end(s)
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define sz(s) int(s.size())
#define ENDL '\n'
using namespace std;
typedef long double ld;
typedef pair<int,int> ii;
typedef long long lli;

int t,n;
string s;
vector<int>w(10);
bool can = 0;
string ans;


void bck(int u, int sum, int mask, vector<int>ass, string good){
  if(can)return;
  if(u<0){can = 1; ans = good; return;}
  vector<ii> inter(n);
  fore(i,0,n)inter[i]={ass[i],ass[i]};
  int l=0,r=25;
  fore(i,0,n){
    if(ass[i]==-1)inter[i].f=l;
    else l = ass[i]+1;
    if(ass[n-i-1]==-1)inter[n-i-1].s=r;
    else r = ass[n-i-1]-1;
  }
  for(auto i:inter)if(i.f>i.s)return;
  fore(i,0,n)if(!(mask & (1<<i))){
    int res = (w[u] - (sum+i) + 10) % 10;
    ii q = inter[i];
    while(res<26){
      if(q.f<=res and q.s>=res){
        ass[i]=res;
        string aux = ""; aux+=char(res+'a');
        bck(u-1,sum+res,mask | (1<<i), ass, good+aux);
        ass[i]=-1;
      }
      res+=10;
    }
  }
}
int main(){
  cin>>t>>n;
  while(t--){
    cin>>s;
    fore(i,0,sz(s))w[i]=s[i]-'0';
    can = 0;
    bck(n-1,0,0,vector<int>(n,-1),"");
    reverse(all(ans));
    cout<<(can?ans:"-1")<<ENDL;

    // fore(i,0,sz(ans)){
    //   int x = 0;
    //   fore(j,0,sz(ans))if(ans[j]<ans[i])x++;
    //   fore(j,i,sz(ans))x+=ans[j]-'a';
    //   cout<<x%10;
    // }

  }

}
