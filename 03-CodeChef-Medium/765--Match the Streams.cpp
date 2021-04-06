#include<iostream>
using namespace std;
#define ll long int
int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);
	int T;
	cin>>T;
	while(T--)
	{
		register ll N,Q;
		cin>>N>>Q;
        register ll A[N];
        register ll B[N];
        register ll C[N];
        register ll P = 0;
        for(ll i=0;i<N;i++)
        {
        	cin>>A[i]; 
        }
        for(ll i=0;i<N;i++)
        {
            C[i] = 0;
        	cin>>B[i];
        	if(B[i]==A[i]) {C[i] = 1;P++;} 
        }
        while(Q--)
        {
        	register ll x,y,z;
        	cin>>x>>y>>z;
        	register ll l,r,c;
        	l = x^P;
        	r = y^P;
        	c = z^P;
        	for(ll i=l-1;i<=r-1;i++)
        	{
               A[i] = c;

               	 if(A[i]==B[i])
                 {
                 	if(C[i]==0)
                 	{
                 		C[i] = 1;
                 		P++;
                 	}
                 }
               	  
               
               else
               {
               	if(C[i]==1)
               	{
               		C[i] = 0;
               		P--;
               	}
               }
        	}
        	cout<<P<<"\n";
        }
	}
	return 0;
}