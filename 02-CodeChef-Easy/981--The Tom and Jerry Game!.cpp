//BISMILLAHIR RAHMANIR RAHIM//
#include<bits/stdc++.h>
using namespace std;
int main()
{
 long long int t,n;
 cin>>t;
 while(t--)
  {
 cin>>n;
 if(n%2==1)
  cout<<(n-1)/2<<endl;
  else
  {
 while(n%2==0)
  {
      n=n/2;
  }
  cout<<(n-1)/2<<endl;
  }
  }
return 0;
}
