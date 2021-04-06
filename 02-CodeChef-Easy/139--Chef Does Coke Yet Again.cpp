#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin>>tc;
    while(tc--)
    {
        int n,q,k,l,r;
        cin>>n>>q>>k>>l>>r;

        vector<int> s[q+2];
        vector<int> e[q+2];

        for(int i=0; i<n; i++)
        {
            int c, p;
            cin>>c>>p;
            if(c==k)
            {
                if(l<=c&&r>=c)
                {
                    s[0].push_back(p);
                    e[q+1].push_back(p);
                }
            }
            else if(c>k)
            {
                if(l<=c&&r>=k)
                {
                    if(r>=c) s[0].push_back(p);
                    else s[min(q+1,c-r)].push_back(p);

                    if(l<=k) e[q+1].push_back(p);
                    else e[min(q+1,c-l)].push_back(p);
                }
            }
            else
            {
                if(r>=c&&l<=k)
                {
                    if(l<=c) s[0].push_back(p);
                    else s[min(q+1,l-c)].push_back(p);

                    if(r>=k) e[q+1].push_back(p);
                    else e[min(q+1,r-c)].push_back(p);
                }
            }
        }

        int ans[q+1];
        multiset<int> temp;
        for(int i=0; i<=q+1; i++)
        {
            for(auto it:s[i])
            {
                temp.insert(it);
            }

            if(temp.size()>0) ans[i]=(*(temp.begin()));
            else ans[i]=-1;

            for(auto it:e[i])
            {
                temp.erase(temp.find(it));
            }
        }

        for(int i=1; i<=q; i++) cout<<ans[i]<<' ';
        cout<<'\n';
    }

    return 0;
}