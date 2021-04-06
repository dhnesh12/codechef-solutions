#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int t;
	cin>>t;
	while(t--)
	{
	    int vx,vy,dx,dy,n;
	    cin>>n;
	    int dir[n];
	    for(int i=0;i<n;i++)
	    {
	        cin>>vx>>vy>>dx>>dy>>dir[i];
	    }
	    int time=1;
	    for(int i=0;i<n;i++)
	    {
	        string op;
	        cin>>op;
	        if(op=="REVERSE")
	        {
	            int temp=rand() % n+1;
	            cout<<temp<<" "<<time++<<endl;
	        }
	        else
	        {
	            int ran=rand() % n+1;
	            dir[ran-1]++;
	            cout<<ran<<" "<<(dir[ran-1]%4)<<" "<<time++<<endl;
	        }
	    }
	    
	}
	return 0;
}
