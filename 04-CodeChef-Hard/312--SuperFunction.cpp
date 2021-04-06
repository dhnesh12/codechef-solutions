#include<iostream>
#include<cmath>
using namespace std;
int gcd(int a, int b)
{
	return b==0?a:gcd(b,a%b);
}
bool coprime(int c,int d)
{
	if(gcd(c,d)==1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
int main()
{
	int N,K,M;
	cin>>N>>K>>M;
	int i=1;
	long long sum=0;
	while(i<N)
	{
		if(coprime(N,i))
		{
			sum=sum+pow(i,K);
			
		}
		i++;
	}
	cout<<sum;
	
	return 0;
}