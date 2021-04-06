#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t-->0)
    {
      int n,k;
      vector <int> v;
      cin>>n>>k;
      for(int i=0;i<n;i++){
        int a;
        cin>>a;
        v.push_back(a);
      }
      int sum=0;
      for(vector<int>::iterator it=v.begin();it<v.end();it++)
      {
        sum+=*it;
      }
      for(int j=0;j<k;j++)
      {
        v.push_back(sum+1);
        sum=sum+(sum+1);
      }
      int ans=v.back();
      if(ans%2==0)
        cout<<"even"<<endl;
      else 
        cout<<"odd"<<endl;
    }
    return 0;
}