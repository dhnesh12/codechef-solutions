#include<bits/stdc++.h>
using namespace std;

#define mx 1009

int ar[mx][mx], up[mx][mx], down[mx][mx], lft[mx][mx], rgt[mx][mx];

int main()
{
    
    int t,n,m,i,j;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                scanf("%d",&ar[i][j]);
            }
        }

      
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(i==0)
                    up[i][j]=0;
                else
                    up[i][j]=min(up[i-1][j]+ar[i-1][j],0);

                if(j==0)
                    lft[i][j]=0;
                else
                    lft[i][j]=min(lft[i][j-1]+ar[i][j-1],0);
            }
        }

        for(i=n-1;i>=0;i--){
            for(j=m-1;j>=0;j--){
                if(i==n-1)
                    down[i][j]=0;
                else
                    down[i][j]=min(down[i+1][j]+ar[i+1][j],0);

                if(j==m-1)
                    rgt[i][j]=0;
                else
                    rgt[i][j]=min(rgt[i][j+1]+ar[i][j+1],0);
            }
        }

        int res=INT_MAX;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                res=min(res, ar[i][j]+up[i][j]+down[i][j]+lft[i][j]+rgt[i][j]);
            }
        }
        printf("%d\n",res);
    }

    return 0;
}
