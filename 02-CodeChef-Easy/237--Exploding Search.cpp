#include<bits/stdc++.h>
#include <boost/math/common_factor.hpp>
using namespace std;
typedef long long int ll;
#define mod 1000000007;
int n;
string s;
 char a[1001][1001];
int occ(int p,int i,int j,int c)
{
  if(i>=n||i<0||j>=n||j<0)
	return 0;
	else if(s[p]!=a[i][j])
	return 0;
	else if(p==c-1)
	return 1;
	else{
	return occ(p+1,i+1,j+1,c)+occ(p+1,i+1,j-1,c)+occ(p+1,i-1,j+1,c)+occ(p+1,i-1,j-1,c);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	  int c,p=0;
    cin>>n;
    for(int i=0;i<n;i++)
     {
     for(int j=0;j<n;j++)
       {
          cin>>a[i][j];
       }
     }
     cin>>s;
	c=s.length();
		 for(int i=0;i<n;i++)
      {
      for(int j=0;j<n;j++)
        {
           if(a[i][j]==s[0])
					 {
					   p+=occ(0,i,j,c);
					 }
        }
      }
     cout<<p;
	return 0;
}
