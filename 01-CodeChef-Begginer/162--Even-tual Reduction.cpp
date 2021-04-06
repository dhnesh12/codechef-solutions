#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll t;
	cin>>t;
	while(t--)
	{
	    ll n,flag=0;
	    cin>>n;
	    string str;
	    cin>>str;
	    ll arr[26]={0};
	    for(ll i=0;i<n;i++)
	    {
	        arr[str[i]-97]++;
	    }
	    for(ll i=0;i<26;i++)
	    {
	        if(arr[i]%2!=0)
	        {
	            flag++;
	            break;
	        }
	    }
	    if(flag==0)
	        cout<<"YES"<<endl;
	    else
	        cout<<"NO"<<endl;
	}
	return 0;
}
