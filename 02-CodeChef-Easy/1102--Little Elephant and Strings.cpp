#include <iostream>
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAX 1000005

int main() {
	// your code goes here
	ll n,k,le,flag;
	cin>>k>>n;
	char lu[k][55],pi[n][55],*p;
	for(ll i=0;i<k;i++)
	cin>>lu[i];
	for(ll i=0;i<n;i++)
	cin>>pi[i];
	for(ll i=0;i<n;i++)
	{
	    flag=0;
	  le=strlen(pi[i]);
	  if(le>=47)
	  {
	      cout<<"Good"<<endl;
	  }
	  else
	  {
	      for(ll j=0;j<k;j++)
	      {
	          p=strstr(pi[i],lu[j]);
	            if(p)
	            {
	                cout<<"Good"<<endl;
	                flag=1;
	                break;
	            }
	      }
	      if(flag==0)
	      cout<<"Bad"<<endl;
	  }
	}
	return 0;
}
