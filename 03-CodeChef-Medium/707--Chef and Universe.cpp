#include<bits/stdc++.h>
#define loop(i,a,b) for(int i=a;i<b;i++)
#define loopb(i,a,b) for(int i=a;i>=b;i--)
#define loopm(i,a,b,step) for(int i=a;i<b;i+=step)
#define loopbm(i,a,b,step) for(int i=a;i>=b;i-=step)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define init(arr,val) memset(arr,val,sizeof(arr))
#define INF 1000000007
#define MOD 1000000007
#define BINF 1000000000000000001
#define int long long int
#define double long double
 
using namespace std;
int x,y,z,a,b,c;
 
void input()
{
	int f,g,h;
	cin>>f>>g>>h;
	cin>>a>>b>>c;
	x=min(f,min(g,h));
	z=max(f,max(g,h));
	y=f+g+h-x-z;
}
 
int soham1234()
{
	int ans=(x+y+z)*a;
	int ans1=BINF,ans2=BINF,ans3=BINF,ans4=BINF;
	if(z-(x+y)>=0)
	{
		 ans1=(x+y)*b+(z-x-y)*a;
		
	}
	else
	  {
	  	 ans1=((x+y+z)/2)*b;
	  	 ans1+=((x+y+z)%2)*a;
	  }
	 
	 ans2=x*c+(z+y-x-x)*a;
     ans3=x*c+(y-x)*b+(z-y)*a;
     int r=z-y;
	 
	 loop(i,r,min(r+1,x+1))
	 {
	   int ans5=(x-i)*c;
	   int x2=i,y2=(y-x+i),z2=(z-x+i);
 
	    if(z2-(x2+y2)>=0)
	{
		 ans5+=(x2+y2)*b+(z2-x2-y2)*a;
		
	}
	else
	  {
	  	 ans5+=((x2+y2+z2)/2)*b;
	  	 ans5+=((x2+y2+z2)%2)*a;
	  }
	  
	  ans3=min(ans3,ans5);
	 
	   
	 }
	 
	loop(i,0,min((int)2,x+1))
	 {
	   int ans5=(i)*c;
	   int x2=x-i,y2=(y-i),z2=(z-i);
 
	    if(z2-(x2+y2)>=0)
	{
		 ans5+=(x2+y2)*b+(z2-x2-y2)*a;
		
	}
	else
	  {
	  	 ans5+=((x2+y2+z2)/2)*b;
	  	 ans5+=((x2+y2+z2)%2)*a;
	  }
	  
	  ans4=min(ans4,ans5);
	 
	   
	 }
	 
	 
	 
	 
	 ans=min(ans,min(ans1,min(ans2,min(ans3,ans4))));
	 return ans;
	 
}
#undef int
int main()
{
#define int long long int
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
    	input();
    	int ans=soham1234();
    	cout<<ans<<"\n";
    	
    }
    
    return 0;
}   