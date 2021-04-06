#include <iostream>
using namespace std;

bool chk(int a1,int a2,int c1,int c2)
{
    if(a1>a2)
    return c1>c2;
    else if(a1<a2)
    return c1<c2;
    else if(a1==a2)
    return c1==c2;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int a1,a2,a3,c1,c2,c3;
	    cin>>a1>>a2>>a3>>c1>>c2>>c3;
	    bool ans = true;
	    if(!(chk(a1,a2,c1,c2)))  ans = false;
	    if(!(chk(a1,a3,c1,c3)))  ans = false;
	    if(!(chk(a3,a2,c3,c2)))  ans = false;
	    
	    if(ans)
	    cout<<"FAIR"<<endl;
	    else
	    cout<<"NOT FAIR"<<endl;
	}
	return 0;
}
