

#include<bits/stdc++.h>
using namespace std;

int solve(vector<int>v, int d)
{
    sort(v.begin(), v.end());
    
    int i=0;
    int n=v.size();
    int res=0;
    while(i<n-1)
    {
        if(v[i+1]-v[i]<=d){
            res++;
            i=i+2;
        }
        
        else
            i++;
            
    }
    
    return res;
}
int main()
{
    
    int n,d;
    cin>>n>>d;
    
    vector<int>v;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        v.push_back(temp);
    }
    
    cout<<solve(v,d);
}