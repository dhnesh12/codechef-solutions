#include <bits/stdc++.h>
using namespace std;
int main() 
{
    long long  n,m;
    long long h;
    cin>>n>>m>>h;
    long long  t[h],c[h];
    long long i;
    pair<long long,long long>p;
    vector<pair<long long,long long>>v;
    for(i=0;i<h;i++){
    cin>>t[i]>>c[i];
    p=make_pair(c[i],t[i]);
    v.push_back(p);}
    long long  min_cost=0;
    long long  sum=0;
    for(i=0;i<h;i++)
    sum=sum+t[i];
    if(sum<(n*m))
    cout<<"Impossible"<<endl;
    else
    {
        sum=(n*m);
        sort(v.begin(),v.end());
        for(i=0;i<v.size();i++)
        {
            if(sum>0)
            {
                if(sum>=v[i].second)
                {
                    min_cost=min_cost+(v[i].first*v[i].second);
                    sum=sum-v[i].second;
                }
                else
                {
                    min_cost=min_cost+(v[i].first*sum);
                    sum=0;
                }
            }
            else
            break;
        }
        cout<<min_cost<<endl;
    }
}
