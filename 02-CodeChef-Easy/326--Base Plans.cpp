#include<bits/stdc++.h>
#define ll long long int
#define f first
#define s second
#define pb push_back

using namespace std;

int main(){
     ios_base::sync_with_stdio(false);
     cout.tie(NULL);
     cin.tie(NULL);
     ll t;
     cin>>t;
     while(t--)
     {
          ll n;
          cin>>n;
          ll pos[n];
          for(int i=0;i<n;i++)
          {
               string s;
               cin>>s;
               for(int j=0;j<n;j++)
               {
                    if(s[j]=='1')
                    pos[i]=j;
               }
          }
          ll ans=0;
          for(int i=0;i<n;i++)
          {
               ll maxi=pos[i];
               ll mini=pos[i];
               for(int j=i;j<n;j++)
               {
                    maxi=max(maxi,pos[j]);
                    mini=min(mini,pos[j]);
                    if(j-i==maxi-mini)
                    ans++;
               }
          }
          cout<<ans<<'\n';
     }
}