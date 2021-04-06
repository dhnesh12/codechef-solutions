#include<bits/stdc++.h>
using namespace std ;

int main(){
  int T ;cin >> T;
  while(T--)
  {
      string s ;
      cin >> s  ;
       long long n = s.size(),t=0,ans=0,p=0;
      map<int,int>mp ;mp[0]++;
      for(char x:s) if(x!='?')  t^=(1<<(x-'a')) ;
      for(int i=0;i<n;i++)
      {
        p^=((s[i]=='?')?(1<<26):(1<<(s[i]-'a')));
        for(int j=0;j<26;j++)
        ans+=mp[t^p^(1<<j)^(1<<26)] ;
        ans+=mp[t^p] ;
        mp[p]++ ;
      }
        cout << ans<< '\n' ;
    }
    
}
