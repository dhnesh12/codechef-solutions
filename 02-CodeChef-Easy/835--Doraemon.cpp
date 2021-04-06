#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int n,m;
	    cin>>n>>m;
	    
	    int arr[n][m];
	    
	    for(int i=0;i<n;i++)
	    
	    {   for(int j=0;j<m;j++)
	       cin>>arr[i][j];
	    }
	    int u,v,w,x;
	     int ans=m*n;
	       for(int i=1;i<n-1;i++)
	       {
	        for(int j=1;j<m-1;j++)
	           {
	             u=j-1;
	             v=j+1;
	             w=i-1;
	             x=i+1;
	            int cnt=0;
	           while(u>=0&&v<m&&w>=0&&x<n&&arr[i][u]==arr[i][v]&&arr[w][j]==arr[x][j])
	              {
	                  w--;
	                  u--;
	                  x++;
	                  v++;
	                  cnt++;
	              }ans+=cnt;
	              
	          }
	           
	       }cout<<ans<<"\n";
	}
	return 0;
}
