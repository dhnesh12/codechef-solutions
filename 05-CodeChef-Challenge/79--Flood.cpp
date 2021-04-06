#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<fstream>
#include<bitset>
 
int a[200][200];
int b[200][200];
int water[40000];
int ans[40000];
 
using namespace std;
 
int t,n,m;
 
ifstream in;
ofstream out;
 
void visit(int k,int x,int y)
{
    
    b[x][y]=k;
    if(x<m-1 && a[x+1][y]==-1 && b[x+1][y]==0)
    {
           
           visit(k,x+1,y);
           if(y<n-1 && a[x+1][y+1]==-1 && b[x+1][y+1]==0)
           visit(k,x+1,y+1);
    }
    if(y<n-1 && a[x][y+1]==-1 && b[x][y+1]==0)
    {
             visit(k,x,y+1);
    }
    if(x>0 && a[x-1][y]==-1 && b[x-1][y]==0)
    {
           
           visit(k,x-1,y);
           if(y>0 && a[x-1][y-1]==-1 && b[x-1][y-1]==0)
           visit(k,x-1,y-1);
    }
    if(y>0 && a[x][y-1]==-1 && b[x][y-1]==0)
    {
             visit(k,x,y-1);
    }
}
 
void display(int arr[200][200])
{
     for(int i=0;i<m;i++)
     {
             for(int j=0;j<n;j++)
             cout<<arr[i][j]<<" ";
             cout<<endl;
     }
}
int main()
{
   //in.open("input.txt");
   //out.open("output.txt");
   //in>>t;
   scanf("%d",&t);
   
   
   for(int prob=0;prob<t;prob++)
   {
           //in>>m>>n;
           scanf("%d %d",&m,&n);
           long long unsigned int mud=0,num=0;
           int mark=1;
           for(int i=0;i<m;i++)
           for(int j=0;j<n;j++)
           {
                   //in>>a[i][j];
                   scanf("%d",&a[i][j]);
                   b[i][j]=0;
                   if(a[i][j]>=0)
                   {
                                 num++;
                                 mud+=a[i][j];
                   }
                   
                            
           }
           for(int i=0;i<m;i++)
           for(int j=0;j<n;j++)
           if(b[i][j]==0 && a[i][j]==-1)
           visit(mark++,i,j);
           //display(b);
           
           if(mark>2){
           printf("%lld\n%lld\n",mud,num);
           for(int i=0;i<m;i++)
           for(int j=0;j<n;j++)
           {
                   if(a[i][j]>=0)
                   printf("%d %d\n",i+1,j+1);
           }}
           else
           printf("%d\n%d\n",0,0);
   }
 
   system("pause");
   return 0;
 
}
