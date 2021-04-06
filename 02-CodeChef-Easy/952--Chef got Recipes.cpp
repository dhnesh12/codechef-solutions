#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define mod 1000000007
#define lli long long int
#define endl '\n'
using namespace std;
int main()
{
         lli F[32];
         int t;
         cin>>t;
         while(t--){
                  int n;
                  cin>>n;
                  REP(i,32)F[i]=0;
                  REP(i,n)
                  {
                           string st;
                           cin>>st;
                           int mask=0;
                           for(int ch=0;ch<st.size();ch++)///(char ch=0;ch<st.size();ch++)
                           {
                                    if(st[ch]=='a')mask=mask|(1<<0);
                                    if(st[ch]=='e')mask=mask|(1<<1);
                                    if(st[ch]=='i')mask=mask|(1<<2);
                                    if(st[ch]=='o')mask=mask|(1<<3);
                                    if(st[ch]=='u')mask=mask|(1<<4);
                           }
                           F[mask]++;///F[mask]=F[mask]+1;
                  }
                  lli res=0;
                  for(int i=1;i<32;i++)
                  {
                           for(int j=i+1;j<32;j++)
                           {
                                    if((i|j)==31)res=res+F[i]*F[j];
                           }
                  }
                  res=res+(F[31]*(F[31]-1))/2;
                  cout<<res<<endl;
         }
}
