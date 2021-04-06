#include<bits/stdc++.h>
using namespace std;
#define int long long int
int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        char a[n][m];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            cin>>a[i][j];
        }
        if(n<=3 || m<=3)
        cout<<"YES"<<endl;
        else
        {
			int cnt=0;
        map<int,int> m2,m1;
        for(int i=1;i<n-1;i++)
        {
            for(int j=1;j<m-1;j++)
            {
                if(a[i][j]=='W')
                {
                    if(a[i-1][j]=='B' && a[i+1][j]=='B' && a[i][j-1]=='B' && a[i][j+1]=='B')
                    {
						cnt++;
                        m2[j]++;
                        m2[j-1]++;
                        m2[j+1]++;
                        m1[i]++;
                        m1[i-1]++;
                        m1[i+1]++;
                    }
                }
            }
        }
        int flag=0;
        for(int i=0;i<n;i++)
        {
			for(int j=0;j<m;j++)
			{
				if(m1[i]+m2[j]>=cnt)
				{
					flag=1;
					break;
				}
			}
			if(flag)
			break;
		}
		if(flag)
		cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
    }
}
}
