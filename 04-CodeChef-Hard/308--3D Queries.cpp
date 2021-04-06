#include <bits/stdc++.h>

using namespace std;
typedef double dd;
typedef long long ll;
dd x[7777778],y[7777778],z[7777778],p[7777778],q[7777778],r[7777778];
int main()
{
	ios_base::sync_with_stdio(0); 
	cin.tie(0);
    ll n,qu,i,a,b,c,d,j;
    cin>>n>>qu;
    for(i=0;i<n;i++)
    {
        cin>>x[i]>>y[i]>>z[i];
    }
    ll co=0;
    for(i=0;i<n;i++)
    {
            for(j=0;j<n;j++)
            {
                if(i!=j)
                {
                    p[co]=x[i]-x[j];
                    q[co]=y[i]-y[j];
                    r[co]=z[i]-z[j];
                    co++;
                }
            }
    }
    //cout<<"co is"<<endl;
    while(qu--)
    {
        cin>>a>>b>>c>>d;
        //ll c=0;
        //cout<<"c is"<<c<<endl;
        dd ans=0;
        for(i=0;i<co;i++)
        {
            dd num=abs((a*p[i])+(b*q[i])+(c*r[i])+d);
            dd den=sqrt((p[i]*p[i]*p[i]*p[i])+(q[i]*q[i]*q[i]*q[i])+(r[i]*r[i]*r[i]*r[i]));
            ans=ans+((dd)num/den);
        }
        ans=ans/(n*(n-1));
        printf("%.15lf\n",ans);
    }
    return 0;
}