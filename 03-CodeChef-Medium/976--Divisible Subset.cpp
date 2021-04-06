#include<bits/stdc++.h>
using namespace std;

/*void solve(int arr[],int n)
{
     unordered_map<int,int> mp;
   mp[0]=-1;
    int t,sum=0;
for(int i=0;i<n;i++)
{
    sum=sum+arr[i];
    t=(sum)%n;
    if(mp.find(t)!=mp.end())
    {
        int j=mp[t];
        cout<<i-j<<endl;
        for(int k=j+1;k<=i;k++){
        cout<<k+1<<" ";
      }
      return;
    }
    mp[t]=i;
}
cout<<-1<<endl;
}*/
void solve(int arr[],int n){
   unordered_map<int,int> mp;
   mp[0]=-1;
   int sum=0,t=0;
   for(int i=0;i<n;i++){
    sum=(sum+arr[i]);
    t=(sum)%n;
    sum=t;
    if(mp.find(t)!=mp.end()){
      int j=mp[t];
      cout<<i-j<<endl;
      for(int k=j+1;k<=i;k++){
        cout<<k+1<<" ";
      }
      return;
    }
    mp[t]=i;
   }
   cout<<-1<<endl;
}
int main()
{
    int t;
    cin>>t;
while(t--)
{
int n;
cin>>n;
int arr[n];
for(int i=0;i<n;i++)
{
    cin>>arr[i];

}
solve(arr,n);
cout<<endl;
}
}
