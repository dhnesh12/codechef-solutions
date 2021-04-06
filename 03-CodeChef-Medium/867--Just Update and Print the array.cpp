#include<bits/stdc++.h>
using namespace std;
int arr[350][100705];
long long ans[100005];
main()
{
	int t,p,m,n;
	int r;
    scanf("%d%d",&t,&p);
    for(int i = 0;i < p;i++)
    {
        scanf("%d%d",&m,&n);
        // scanf("%lld",&r);
		swap(m,n);
        if(n<350)
        arr[n][m]+=1;
        else
        {
            for(int j = m;j <= t;j+=n)
            {
                ans[j]+=1;
            }
        }
    }
	for(int i = 1;i < 350;i++)
	{
		for(int j = 1;j <= t;j++)
		{
			arr[i][j+i]+=arr[i][j];
			ans[j]+=arr[i][j];
		}
	}
	for(int i = 1;i <= t;i++)
	{
		printf("%d ",ans[i]);
	}
}
