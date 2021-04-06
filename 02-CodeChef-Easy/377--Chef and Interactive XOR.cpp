#include<iostream>
using namespace std;
#define ll long long int
int main()
{
int t; cin>>t;
while(t--)
{
ll n; cin>>n;
	ll a[n+1];
	
	ll rem=n%4+4,c=(n-rem)/4;
	ll i=1;
	while(c--)
	{
		ll t1,t2,t3,t4;
		cout<<1<<" "<<i<<" "<<i+1<<" "<<i+2<<endl;
		cin>>t1;
		cout<<1<<" "<<i+1<<" "<<i+2<<" "<<i+3<<endl;
		cin>>t2;
		cout<<1<<" "<<i+2<<" "<<i+3<<" "<<i<<endl;
		cin>>t3;
		cout<<1<<" "<<i+3<<" "<<i<<" "<<i+1<<endl;
		cin>>t4;
		
		ll total=(t1^t2^t3^t4);
		a[i]=t2^total;
		a[i+1]=t3^total;
		a[i+2]=t4^total;
		a[i+3]=t1^total;
		
		i+=4;
		
		
	}
	
	if(rem==4){
			ll t1,t2,t3,t4;
		cout<<1<<" "<<i<<" "<<i+1<<" "<<i+2<<endl;
		cin>>t1;
		cout<<1<<" "<<i+1<<" "<<i+2<<" "<<i+3<<endl;
		cin>>t2;
		cout<<1<<" "<<i+2<<" "<<i+3<<" "<<i<<endl;
		cin>>t3;
		cout<<1<<" "<<i+3<<" "<<i<<" "<<i+1<<endl;
		cin>>t4;
		
		ll total=(t1^t2^t3^t4);
		a[i]=t2^total;
		a[i+1]=t3^total;
		a[i+2]=t4^total;
		a[i+3]=t1^total;
	}
	else if(rem==5){
		ll t1,t2,t3,t4,t5;
		cout<<1<<" "<<i<<" "<<i+1<<" "<<i+2<<endl;
		cin>>t1;
		cout<<1<<" "<<i+1<<" "<<i+2<<" "<<i+3<<endl;
		cin>>t2;
		cout<<1<<" "<<i+2<<" "<<i+3<<" "<<i+4<<endl;
		cin>>t3;
		cout<<1<<" "<<i+3<<" "<<i+4<<" "<<i<<endl;
		cin>>t4;
		cout<<1<<" "<<i+4<<" "<<i<<" "<<i+1<<endl;
		cin>>t5;
		
		ll total=(t1^t2^t3^t4^t5);
		a[i]=t1^t4^total;
		a[i+1]=t2^t5^total;
		a[i+2]=t1^t3^total;
		a[i+3]=t2^t4^total;
		a[i+4]=t3^t5^total;
	}
	else if(rem==6){
			ll t1,t2,t3,t4,t5,t6;
		cout<<1<<" "<<i<<" "<<i+1<<" "<<i+2<<endl;
		cin>>t1;
		cout<<1<<" "<<i<<" "<<i+3<<" "<<i+4<<endl;
		cin>>t2;
		cout<<1<<" "<<i<<" "<<i+4<<" "<<i+5<<endl;
		cin>>t3;
		cout<<1<<" "<<i+1<<" "<<i+3<<" "<<i+5<<endl;
		cin>>t4;
		cout<<1<<" "<<i+1<<" "<<i+4<<" "<<i+2<<endl;
		cin>>t5;
	   	cout<<1<<" "<<i+2<<" "<<i+3<<" "<<i+5<<endl;
		cin>>t6;
		
		ll total=t1^t2^t3^t4^t5^t6;
		
		a[i+4]=t1^t2^t3^total;
		a[i+1]=t1^t4^a[i+4]^total;
		a[i+5]=t2^t5^a[i+4]^total;
		a[i+3]=t3^t5^a[i+4]^total;
		a[i]=t4^t5^a[i+1]^total;
	    a[i+2]=t5^t6^a[i]^total;
	}
	else if(rem==7){
			ll t1,t2,t3,t4,t5,t6,t7;
		cout<<1<<" "<<i<<" "<<i+1<<" "<<i+2<<endl;
		cin>>t1;
		cout<<1<<" "<<i+1<<" "<<i+2<<" "<<i+3<<endl;
		cin>>t2;
		cout<<1<<" "<<i+2<<" "<<i+3<<" "<<i+4<<endl;
		cin>>t3;
		cout<<1<<" "<<i+3<<" "<<i+4<<" "<<i+5<<endl;
		cin>>t4;
		cout<<1<<" "<<i+4<<" "<<i+5<<" "<<i+6<<endl;
		cin>>t5;
		cout<<1<<" "<<i+5<<" "<<i+6<<" "<<i<<endl;
		cin>>t6;
		cout<<1<<" "<<i+6<<" "<<i<<" "<<i+1<<endl;
		cin>>t7;
		
		ll total=t1^t2^t3^t4^t5^t6^t7;
		
		a[i]=t2^t5^total;
		a[i+1]=t3^t6^total;
		a[i+2]=t4^t7^total;
		a[i+3]=t5^t1^total;
		a[i+4]=t6^t2^total;
	   	a[i+5]=t7^t3^total;
		a[i+6]=t1^t4^total;
	}
	
	
	
	
	cout<<2<<" ";
	for(i=1;i<=n;i++)
       cout<<a[i]<<" ";
       cout<<endl;
       
       ll z; cin>>z;
       if(z==-1)
       return 0;
    
}
}


