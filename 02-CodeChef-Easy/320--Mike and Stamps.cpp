#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<limits.h>
#include<list>
using namespace std;
 
/*printing definitions*/
#define pi(x) printf("%d\n",(x))
#define pii(x,y) printf("%d %d\n",(x),(y))
#define pl(x) printf("%lld\n",(x))
#define pll(x,y) printf("%lld %lld\n",(x),(y))
#define pil(x,y) printf("%d %lld\n",(x),(y))
#define pli(x,y) printf("%lld %d\n",(x),(y))
#define plf(x) printf("%lf\n",(x))
#define plflf(x,y) printf("%lf %lf\n",(x),(y))
 
/*scanning definitions*/
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d %d",&x,&y)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld %lld",&x,&y)
#define sil(x,y) scanf("%d %lld",&x,&y)
#define sli(x,y) scanf("%lld %d",&x,&y)
#define slf(x) scanf("%lf",&x)
#define slflf(x,y) scanf("%lf %lf",&x,&y)
 
/*fast i/p definitions*/
#define getcx getchar_unlocked
#ifndef ONLINE_JUDGE
    #define getcx getchar
#endif       
//  CREATED BY: ATUL SEHGAL
inline int in()
{
   int n=0;
   int ch=getcx();int sign=1;
   while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}
 
   while(  ch >= '0' && ch <= '9' )
           n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
   return n*sign;
}
int a[21][20001],adj[21][21],m,s[21];
int clique(int s[],int l)
{
    int i,j,deg[l],mini;
    while(1)
    {
        int minn=l+5,maxx=0;
        memset(deg,0,sizeof(deg));
        for(i=0;i<l;i++)
        {
            for(j=0;j<l;j++)
            {
                if(adj[s[i]][s[j]] && i!=j)
                {
                    deg[i]++;
    //                cout<<"i="<<s[i]<<" j="<<s[j]<<endl;
                }
            }
        
        }
    /*    cout<<"deg==>"<<endl;
        for(i=0;i<l;i++)
            cout<<deg[i]<<" ";
        cout<<endl;
     */   for(i=0;i<l;i++)
        {
            if(deg[i]<minn)
                minn=deg[i],mini=i;
            if(deg[i]>maxx)
                maxx=deg[i];
        }
    //    cout<<"min="<<minn<<" max="<<maxx<<endl;
     //   system("pause");
        if(minn==maxx)
            return l;
        else
        {
            l--;
            for(i=1;i<mini;i++)
                s[i]=s[i];
            for(;i<=l;i++)
                s[i]=s[i+1];
        }
    }
}
int main()
{
	int t,i,j,k,n,maxx=0,f;
	n=in(); m=in();
	for(i=0;i<m;i++)
    {
        a[i][0]=in();
        for(j=1;j<=a[i][0];j++)
            a[i][j]=in();
    }
    for(t=0;t<m;t++)
    {
        for(i=t+1;i<m;i++)
        {
            f=0;j=k=1;
            while(j<=a[i][0] && k<=a[t][0])
            {
                if(a[i][j]==a[t][k])
                {
                    f=1;
                    break;
                }
                else if(a[i][j]>a[t][k])
                    k++;
                else
                    j++;
            }
            if(f==0)
                adj[i][t]=1,adj[t][i]=1;
        }
    }
  /*  for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
            cout<<adj[i][j]<<" ";
        cout<<endl;
    }
  */  for(i=0;i<m;i++)
    {
        int s[21]={i},len=1;
        for(j=0;j<m;j++)
            if(adj[i][j])
                s[len++]=j;
   //     cout<<"len="<<len<<endl;
        maxx=max(maxx,clique(s,len));
    }
    pi(maxx);
	return 0;
}