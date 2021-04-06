#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() 
{
    int t;
    cin>>t;
    while(t--)
    {
    int n;
	double p;
	cin>>n>>p;
	double z = 1000000000;
	double x= z*((pow(-p,n)-1)/((-p)-1));
	double y= z-x;
printf("%f %f\n",x,y);
    }
}