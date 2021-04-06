#include <iostream>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b)
{
    if(a==0)return b;
    return gcd(b%a,a);
}

int main() {
/*	while(1)
	{
	    ll d=0,nm=0,nh=0,vm=0,vh=0,kd=0,kv=0,x=0;
	    cin>>d>>nm>>nh>>vm>>vh;
	    if(d+nm+nh+vm+vh==0)
	    break;
	    if(vm>vh)
        {
            kd=d;
            kv=vm;
        }
        else if(nh>=nm)
        {
            kd=d;
            kv=max(vm,vh);
        }
        else
        {
            x=d*(vm+vh)/((2*nm*vm)+nh*(vh-vm));

            kd=nh*x*(vm-vh)+d*vh;

            kv=vh*vm;

        }
        ll t = gcd(kd,kv);
        kd/=t;
        kv/=t;
        cout<<kd<<"/"<<kv<<" ";
        cout<<"\n";
	}
	return 0;*/
	while(1)
	{

	ll dis,man,nh,sm,sh,kd,kv;
	
	cin>>dis>>man>>nh>>sm>>sh;
	if(dis+man+nh+sm+sh==0)break;
    
    if(sm>=sh)
    {
    	kd=dis;
    	kv=sm;
    }
    else if(man<=nh)
    {
    	kd=dis;
    	kv=max(sm,sh);
    	
    }
    else
    {
         kd=(dis)*(2*man*sh-nh*sh+nh*sm);
         kv=(sh)*(2*man*sm+nh*(sh-sm));


    }
    ll t=gcd(kd,kv);
    kd/=t,kv/=t;
    cout<<kd<<"/"<<kv<<" ";
    cout<<"\n";


}
}
	

