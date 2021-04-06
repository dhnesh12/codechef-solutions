#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main()
{
    int q;
    cin>>q;
    while(q--)
    {
        int n,l,vc;
        cin>>n>>l>>vc;
        int x[n],v[n];
        for(int i=0;i<n;i++) cin>>x[i];
        for(int i=0;i<n;i++) cin>>v[i];
        double ll=0,rr=l;
        for(int j=0;j<100;j++)
        {
            double t=(ll+rr)/2.0;
            bool pos=0;
            vector<pair<double,int> > now(2,make_pair(0.0,0));
            for(int i=0;i<n;i++)
            {
                double temp=(double)x[i]+t*(double)v[i];
                if(now[0]==make_pair(0.0,0)) now[0]=make_pair(temp,i);
                else if(now[1]==make_pair(0.0,0))
                {
                    now[1]=make_pair(temp,i);
                    if(now[0].first<now[1].first) swap(now[0],now[1]);
                }
                else if(temp>now[0].first)
                {
                    swap(now[0],now[1]);
                    now[0]=make_pair(temp,i);
                }
                else if(temp>now[1].first) now[1]=make_pair(temp,i);
            }
            for(int i=0;i<n;i++)
            {
                double req=(double)x[i]+(double)l-t*(double)v[i];
                if(now[(i==now[0].second)?1:0].first>=req) pos=1;
            }
            if(pos) rr=t;
            else ll=t;
        }
        double res=rr;
        for(int i=0;i<n;i++)
        {
            if(v[i]<vc) continue;
            double ds=(double)min(x[i],l-x[i]);
            res=min(res,ds/(double)(v[i]-vc));
        }
        printf("%.9f\n",res);
    }
    return 0;
}