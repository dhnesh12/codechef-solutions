#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int main()
{
	ll t;
	cin>>t;
	while(t--)
	{
		double a;
		cin>>a;
		ll i,j,l;
		ll hr,min;
		double x,m,er=1/120;
		ll flag=0;
		for(i=1;i<=12;i++)
		{
			x=i*30;
			if(x>180)
			{
				flag=1;
				x=360-x;
			}
			x=x-a;
			m=x/5.5;
			if(m<0)
			m=m+60;
			if(flag==1)
			m=60-m;
			
			if(m-floor(m)<=er || ceil(m)-m<=er)
			{	
			
				l=i;
				if(m==60)
				m=0;
				if(i==12)
				l=0;
				
				if(m<10 &&l<10)
				{
					cout<<0<<l<<":"<<0<<m<<endl;
				}
				else if(l<10)
				{
					cout<<0<<l<<":"<<m<<endl;
				}
				else if(m<10)
				{
					cout<<l<<":"<<0<<m<<endl;
				}
				else
				cout<<l<<":"<<m<<endl;
				
				flag=0;
			}		
			
		}
	}
}