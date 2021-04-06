#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,n,m,*p,*f,i;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        map<int,int>temp;
        map<int,int>::iterator itr;
        p=new int[n];
        f=new int[n];
        for(i=0;i<n;i++)
        {
            cin>>p[i];
            if(temp.find(p[i])==temp.end()){
                temp.insert({p[i],0});
            }
        }
        for(i=0;i<n;i++)
           cin>>f[i];
        for(i=0;i<n;i++)
        {
            temp[p[i]]+=f[i];
        }
        int Min=INT_MAX;
        for(itr=temp.begin();itr!=temp.end();itr++)
        {
            if(itr->second<Min)
                Min=itr->second;
        }
        cout<<Min<<"\n";
    }

}
