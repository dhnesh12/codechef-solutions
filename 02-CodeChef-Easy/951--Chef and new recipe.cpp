#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define PB push_back

int main() {
	// your code goes here
	ll int t; cin>>t;
    while(t--)
    {
        ll int n;
        cin>>n;
        vector<ll int>arr;
        for(ll int i=0; i<n; i++)
        {
            ll int el; cin>>el;
            arr.PB(el);
        }
        
        sort(arr.begin(),arr.end());
        
        bool flag = false;
        for(ll int i=0; i<n; i++)
        {
            if(arr[i]<2)
            {
                flag=1;
                break;
            }
        }
        
        if(n>1 && !flag)
        {
            ll int sum=0;
            for(ll int i = n-1; i>0; i--)
            {
                sum += arr[i];
            }
            cout<<sum+2<<endl;
        }
        
        if(n==1 && !flag)
            cout<<2<<endl;
        
        if(flag)
            cout<<-1<<endl;
    }
	return 0;
}
