#include <bits/stdc++.h>
using namespace std;

double series_sum(function<double(int)> f, int n){    

double sum = 0; 

for(int i=0; i<=n; i+=2) 

sum = sum + f(i); 

return sum;

}

int main(){ 
int i,t,n,prv,a,f,x,y,prvMv,mx,si,vi,pi;
bool incOps,decOps;
cin>>t;
string st;
while(t--)
{
	cin>>n;
	mx=0;
	while(n--)
	{
		cin>>si>>pi>>vi;
		if(pi%(si+1)==0)
		mx=max(mx,(pi*vi)/(si+1));
		else mx=max(mx,(pi/(si+1))*vi);
	}
	cout<<mx<<endl;
}
	 return 0;  	
}
