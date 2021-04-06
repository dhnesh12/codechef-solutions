#include <bits/stdc++.h>

using namespace std;
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        unsigned long long int n,k,ans=0,s=1;
        cin>>n>>k;
        for(int i=0;i<n;i++)
        {
             if(k%2!=0)
             {
                  ans=ans+(s<<n-i-1);
             }
             k=k>>1;
        }
        cout<<ans<<endl;
        
    }
	
	return 0;
}