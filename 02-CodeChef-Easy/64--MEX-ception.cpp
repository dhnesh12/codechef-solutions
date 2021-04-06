#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int n,m;
	    cin>>n>>m;
	    if(n==m && n==1)
	    {
	        cout<<1<<endl;
	        continue;
	    }
	    bool flag=false;
	    if(n>m)
	    {
	        swap(n,m);
	        flag=true;
	    }
	    vector<vector<int>> v (n,vector<int>(m,0));
	    for(int i=0;i<n;i++)
	        for(int j=0;j<m;j++)
	            v[i][j]=(j-i+m)%m;
	    for(int i=0,j=n+1;i<n && j<m;i++,j++)
	    v[i][(j+i)%m]=0;
	    if(n==m)
	    {
	        for(int j=0;j<m;j++)
	         v[0][j]=n+1;
	    }
	    if(n==1)
	    for(int j=0;j<m;j++) v[0][j]=!j;
	    
	    if(flag)
	    {
	        vector<vector<int>> b(m,vector<int>(n));
	        for(int i=0;i<n;i++)
	            for(int j=0;j<m;j++)
	                b[j][i]=v[i][j];
            v=b;
            swap(n,m);
	    }
	    for(int i=0;i<n;i++){
	        for(int j=0;j<m;j++){
	            printf("%d ",v[i][j]);
	        }
	        cout<<"\n";
	    }
	}
	return 0;
}
