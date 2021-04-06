#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
int t,n,m,k;
cin>>t;
while(t--)
{   string s="CTAG";
    cin>>n>>m>>k;
    
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++)
        cout<<s[rand()%4];
      
      cout<<endl;   }
}

	return 0;
}
