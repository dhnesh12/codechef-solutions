#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define fn(i,n) for(int i=0;i<n;i++)
#define ll long long
 
int main()
{
ios_base::sync_with_stdio(0);
cin.tie(NULL);
cout.tie(NULL);	
int T;
//cout<<"give test"<<endl;
cin>>T;
while(T--)
{
	
ll x;
///cout<<"give eliminated num"<<endl;
cin>>x;
ll N;
//cout<<"give the big number"<<endl;
cin>>N;
ll checksum=N*(N+1);
checksum=checksum/2;
if((checksum%2==0&&x%2==1)||(checksum%2==1&&x%2==0))
{
		cout<<"impossible"<<endl;
}
 
else 
{
ll arr[N+1];
arr[0]=0;
 
for(ll i=1;i<=N;i++)
{
	arr[i]=i;
}
 
arr[x]=0;
ll elisum=checksum-x;
elisum=elisum/2;
//cout<<"sum to be elimnnated is"<<elisum<<endl;
ll revindex=N;
ll impans=0;
while(elisum>0)
{
	ll checksum;
	
	if(elisum>=arr[revindex])
	{
		
	elisum=elisum-arr[revindex];
	arr[revindex]=0;
	revindex=revindex-1;
	//cout<<"updated elisum is"<<elisum<<endl;
	if(elisum==x)
	{
		//cout<<"here here"<<endl;
		arr[revindex+1]=revindex+1;
		checksum=elisum+arr[revindex+1];
		//cout<<"here checksum is"<<checksum;
	}
	}
 
	else
	{
	if(elisum!=x)
	{
	//cout<<"elisum not equal to x and its value is"<<elisum<<endl;
	ll check=elisum;
		elisum=elisum-arr[elisum];
		arr[check]=0;	
    }
	else //elsium=x;
	{
	arr[revindex+1]=revindex+1;
	//cout<<"else checksum is"<<checksum<<endl;
	checksum=checksum-arr[revindex];
	arr[revindex]=0;
	arr[checksum]=0;
	if(checksum<1||revindex+1>N)
	{
		impans=1;
	//cout<<"here"<<endl;
	}
	elisum=0;
	}
	}
}
//cout<<"answer is"<<endl;
//for(ll i=1;i<=N;i++)
//{
	////cout<<arr[i];
//}
//cout<<"matching"<<endl;
if(impans!=1)
{
 
for(ll i=1;i<=N;i++)
{
	if(i==x)
	cout<<"2";
	else if(arr[i]!=0)
	cout<<"1";
	else
	cout<<"0";
}
}
else
cout<<"impossible";
cout<<endl;
}
}
return 0;
}