#include<stdio.h>
#define S 8
#define M 21945
 
void dfs(int i,int j,int c);
int power(int x,int y);
 
int napkin[S][S];
int region[S][S];
char input[10];
 
int top,bottom,left,right;
 
int main()
{
    int testCases,t;
    int n,i,j,c,count;
    scanf("%d",&testCases);
    for(t=1;t<=testCases;t++)
    {
        scanf("%d",&n);
        for(i=0;i<S;i++)
        {
            scanf("%s",input);
            for(j=0;j<S;j++)
            {
                napkin[i][j] = input[j]-'0';
                region[i][j] = 0;
            }       
        }
        c=0;
        count = 0;
        for(i=0;i<S;i++)
        {
            for(j=0;j<S;j++)
            {
                if(napkin[i][j]==1 && region[i][j]==0)
                {
                    dfs(i,j,++c);
                    if(top==0 && bottom==0 && left==0 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-3)*power(2,n-3))%M;
                    }
                    else if(top==0 && bottom==0 && left==0 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4)*power(2,n-3))%M;
                    }
                    else if(top==0 && bottom==0 && left==1 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,2*n-7) + power(2,n-3))%M;
                    }
                    else if(top==0 && bottom==0 && left==1 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-3))%M;
                    }
                    else if(top==0 && bottom==1 && left==0 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4)*power(2,n-3))%M;
                    }
                    else if(top==0 && bottom==1 && left==0 && right==1)
                    {
                        if(n==3)
                            count = (count+1)%M;
                        else
                        count = (count + power(2,n-4)*power(2,n-4))%M;
                    }
                    else if(top==0 && bottom==1 && left==1 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,2*n-8) + power(2,n-4))%M;
                    }
                    else if(top==0 && bottom==1 && left==1 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4))%M;
                    }
                    else if(top==1 && bottom==0 && left==0 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,2*n-7)+power(2,n-3))%M;
                    }
                    else if(top==1 && bottom==0 && left==0 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,2*n-8) + power(2,n-4))%M;
                    }
                    else if(top==1 && bottom==0 && left==1 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,2*n-8) + power(2,n-3) + 1)%M;
                    }
                    else if(top==1 && bottom==0 && left==1 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4) + 1)%M;
                    }
                    else if(top==1 && bottom==1 && left==0 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-3))%M;
                    }
                    else if(top==1 && bottom==1 && left==0 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4))%M;
                    }
                    else if(top==1 && bottom==1 && left==1 && right==0)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count + power(2,n-4) + 1)%M;
                    }
                    else if(top==1 && bottom==1 && left==1 && right==1)
                    {
                        if(n==3)
                           count = (count+1)%M;
                        else
                        count = (count+1)%M;
                    }
                    top = 0; bottom = 0; left = 0; right = 0;
                }    
            }    
        }
       printf("%d\n",count);            
    }
    return 0;    
} 
 
void dfs(int i,int j,int c)
{
    region[i][j] = c;
    if(i==0) top = 1;
    if(i==S-1) bottom = 1;
    if(j==0) left = 1;
    if(j==S-1) right = 1;
    
    
    if(i<S-1)
    {
        if(napkin[i+1][j]==1 && region[i+1][j]==0)
            dfs(i+1,j,c);
    } 
    if(j<S-1)
    {
        if(napkin[i][j+1]==1 && region[i][j+1]==0)
            dfs(i,j+1,c);
    }
    if(i>0)
    {
        if(napkin[i-1][j]==1 && region[i-1][j]==0)
            dfs(i-1,j,c);
    } 
    if(j>0)
    {
        if(napkin[i][j-1]==1 && region[i][j-1]==0)
            dfs(i,j-1,c);
    }    
} 
 
int power(int x,int y)
{
    int final = 1;
    int t = x;
    while(y>0)
    {
        if(y%2==1)
        {
            final = (final * t)%M;
        }
        t = (t * t) % M;
        y/=2;    
    }
    return final;    
}