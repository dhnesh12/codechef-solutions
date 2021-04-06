#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main() {
   ll n,d;
  cin>>n>>d;
    vector<vector<ll>>v;
  
    for(int i=0;i<n;i++)
    {
        vector<ll> temp;
      for(int j=0;j<d;j++)
      {
          int a;
          cin>>a;
         temp.push_back(a);
      }
        v.push_back(temp);
    }
    
    
     int **mat=new int*[n];
    for(int i=0;i<n;i++)
    {
        mat[i]=new int[n];
        for(int j=0;j<n;j++)
        {
            mat[i][j]=0;
        }
    }
    
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int sum=0;
            for(int k=0;k<d;k++)
            {
              sum+=abs(v[i][k]-v[j][k]);  
            }
            mat[i][j]=sum;
            mat[j][i]=sum;
        }
    }
    
    
    int parent[n];
   int weight[n];
   bool visited[n];
   for(int i=0;i<n;i++)
   {
       visited[i]=false;
   }
   //  for(int i=0;i<v;i++)
   // {
   //     parent[i]=-1;
   // }
   for(int i=0;i<n;i++)
   {
      if(i==0)
      weight[i]=0;
      else
      weight[i]=INT_MIN;
   }
   
   for(int i=0;i<n;i++)
   {
      int max=INT_MIN; 
      int temp;
       for(int j=0;j<n;j++)
       {
           if(visited[j]==true)
             continue;
           if(max<weight[j])
           {
               max=weight[j];
               temp=j;
           }
       }
       visited[temp]=true;
       for(int j=0;j<n;j++)
       {
          if(visited[j]==false && mat[temp][j]>0)
          {
              if(mat[temp][j]>weight[j])
              {
                  weight[j]=mat[temp][j];
                  parent[j]=temp;   
              }
              
          }
       }
      
   }
    ll sum=0;
       for(int i=1;i<n;i++)
       {
           // if(parent[i]!=-1 && weight[i]!=INT_MAX)
           sum+=weight[i];
       }
    
    cout<<sum<<endl;
}
