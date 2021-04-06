	#include<bits/stdc++.h>
	using namespace std;
	typedef long long int ll;
	typedef set<ll>::iterator iets;
	typedef vector<ll>::iterator ietv;
	typedef vector<ll> V;
	 
	#define mod 10000000007
	const ll INF=1000000000000000000;
	typedef pair<ll , ll> pi;
	int main()
	{
	    ios_base::sync_with_stdio(false);
	    cin.tie(NULL);
	    int t=1;
	   cin>>t;
	    while(t--)
	    {
	    	ll i,y,h,j,k,r=0,l=0,n,m,x=0,o=0,cnt1=INT_MAX,cnt2=0,cnt3=INT_MIN,cnt4=0,min1=INT_MIN;
	    	cin>>n>>k;
	    	string s;
	    	cin>>s;
	    	ll a[n]={0},b[n]={0};
	    	for(i=2;i<n;i++){
	    			
	    		if(s[i]==s[i-1]||s[i]==s[i-2]||s[i-1]==s[i-2])
	    			a[i]=1;
	    		if(i==2)
	    			b[2]=a[2];
	    		if(i>2)
	    			b[i]=b[i-1]+a[i];
	    	}
	    	b[0]=b[1]=0;
	    	for(i=0;i<k;i++){
	    		cin>>x>>y;
	    		if(y-x<2)
	    			cout<<"NO\n";
	    		else if(b[y-1]-b[x]>0){
	    			cout<<"YES\n";
	    		}
	    		else
	    			cout<<"NO\n";
	    	}


	    }
		
	}