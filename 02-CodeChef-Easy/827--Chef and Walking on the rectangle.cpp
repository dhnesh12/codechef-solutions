#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin>>t;
	while(t--)
	{
	    int n,m,k;
	    cin>>n>>m>>k;
	    if(n>m)
	    {
	        swap(n,m);
	    }
	    if(n==1 && m<=2)
	    {
	        cout<<"0"<<"\n";
	    }
	    else if(n==1 && m>2)
	    {
	        cout<<k<<"\n";
	    }
	    else
	    {
	        cout<<ceil(k/2.0)<<"\n";
	    }
	}
	return 0;
}
