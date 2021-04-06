#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	long long int test;
	cin>>test;
	for(int t=0;t<test;t++)
	{
	    long long int n;
	    cin>>n;
	    int x=sqrt(n);
	    int y=n/x;
	    int k=n%x;
	    for(int i=1;i<=x;i++)
	    {
	        cout<<"X";
	        if(i==k)
	        cout<<"D";
	    }
	    while(y--)
	    cout<<"D";
	    cout<<endl;
	}
	return 0;
}
/*
 * COME ON DUDE .... DONT GET UP UNTIL U GET THE SOLUTION
 * GIVING UP NOT GONNA HELP .. JUST GET YOUR ASS TO WORK ALREADY ..
 * AND FOR FUCKING SAKE ... DONT PANIC !!
*/