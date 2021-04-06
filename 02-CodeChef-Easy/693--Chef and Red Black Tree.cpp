#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl "\n"
ll mod=1000000007;
ll power(ll a,ll n)
{
    if(n==0)return 1;
    ll temp=power(a,n/2);
    temp=temp*temp%mod;
    if(n%2)temp=a*temp%mod;
    return temp;
    
}
ll inverse(ll a)
{
    return power(a,mod-2);
}
ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
void dfs(ll u,vector<ll>v[],bool vis[])
{
    vis[u]=true;
    for(ll x:v[u])
    {
        if(vis[x]==false)
        dfs(x,v,vis);
    }
}
int main() {
	// your code goes here
		                             ios::sync_with_stdio(0);
                                     cin.tie(0),cout.tie(0);
    ll q,x,y,i,j;
    char c='b',c1;
    cin>>q;
    while(q--)
    {
        string str;
        cin>>str;
        if(str=="Qi")
        {
            if(c=='b')
            c='r';
            else
            c='b';
        }
        else 
        {
            cin>>x>>y;
            
            vector<ll>vx,vy;
            while(x){vx.push_back(x);x/=2;}
            while(y){vy.push_back(y);y/=2;}
            
            j=vy.size()-1;
            for(i=vx.size()-1;i>=0;i--)
            {
                if(j>=0)
                {
                  if(vx[i]!=vy[j])
                  break;
                  j--;
                }
                else
                break;
            }
            
            i++;j++;i=i+j+1;
            if(vx.size()%2)
            c1=c;
            else
            {
              if(c=='b')
              c1='r';
              else
              c1='b';
            }
            
            if(str=="Qb")
            {
                if(c1=='b')
                {
                  cout<<(i+1)/2<<" ";  
                }
                else
                {
                    cout<<i/2<<" ";
                }
            }
            else if(str=="Qr")
            {
                if(c1=='r')
                {
                  cout<<(i+1)/2<<" ";  
                }
                else
                {
                    cout<<i/2<<" ";
                }
            }
        }
    }
	return 0;
}
