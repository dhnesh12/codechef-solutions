#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
using namespace std;
typedef long long int lld;
typedef vector<lld> vi;
typedef pair<lld,lld> pi;
#define F first
#define S second
#define N 100005
#define MOD 1000000007
#define PB push_back
#define MP make_pair
#define rep(i, a, b) for (lld i = a; i < b; i++)
lld m,t,y,z,q,j,i,r,m1,m2,n,l,d,blocks,x;

lld a[N];

bool check(string s){
       string ns = s;
       reverse(s.begin(),s.end());
       return s == ns;
}
lld brute(string s){
       string curr = "";
       lld nn = s.size();
       lld ans = 0;
       for(i=0;i<=s.size();i++){
              for(j=0;j<26;j++){
                     string ns = curr + (char)(97+j) + s.substr(i,nn-i);
              //       cout<<i<<' '<<j<<' '<<ns<<endl;
                     if(check(ns)){
                            ans++;break;
                     }
              }
              curr += s[i];
       }
       return ans;
}

int main(){
       
       ios_base::sync_with_stdio(false);
       cin.tie(NULL);

       cin>>t;
       while(t--){
              string s;
              cin>>s;
              n = s.length();
              lld maximatch = 0,ans=0;
              for(i=0;i<n/2;i++){
                     if(s[i] == s[n-i-1])maximatch++;
                     else break;
              }
              r = n/2;
              l = n/2 - 1;
              if(n%2==0)r--;
              for(i=maximatch;i>=0;i--){
                     while(l >= i && s[l] == s[r])l--,r++;
                     if(l>=i)break;
              }
              ans += (maximatch-i);
              if(n%2==0 && maximatch==n/2)ans--;

              reverse(s.begin(),s.end());

              r = n/2;
              l = n/2 - 1;
              if(n%2==0)r--;
              for(i=maximatch;i>=0;i--){
                     while(l >= i && s[l] == s[r])l--,r++;
                     if(l>=i)break;
              }
              ans += (maximatch-i);
              ans = min(ans,n+1);
              cout<<ans<<endl;

       }

}
