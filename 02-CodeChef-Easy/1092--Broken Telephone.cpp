#include<bits/stdc++.h>
using namespace std;

void solve()
{
    vector<int> v;
    int n,cnt=0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        long long int x;
        cin>>x;
        v.push_back(x);
    }
    int flag = 0;
    for(int i=0; i<n-1; i++)
    {
        if(v[i] - v[i+1] != 0 && flag == 0)
        {
            cnt+=2;
            flag = 1;
        }
        else if(v[i] - v[i+1] != 0 && flag == 1)
        {
            cnt++;
        }
        else if(v[i] - v[i+1] == 0)
            flag = 0;
    }
    cout<<cnt<<endl;
}

int main()
{
   int t;
   cin>>t;
   while(t--)
    solve();
}
