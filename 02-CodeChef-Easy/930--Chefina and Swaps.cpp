#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t=0;
    cin>>t;
    while(t--)
    {
        long long int n=0;
        long long int i=0,x=pow(10,10)+1,y=pow(10,10)+1;
        cin>>n;
        int cond=0;
        long long int a[n],b[n];
        unordered_map<long long int,long long int>map1,map2;
        vector<long long int>vec;
        for(i=0;i<n;i++)
        {
            cin>>a[i];
            if(x>a[i])
            {
                x=a[i];
            }
            map1[a[i]]++;
        }
        for(i=0;i<n;i++)
        {
            cin>>b[i];
            if(y>b[i])
            {
                y=b[i];
            }
            map2[b[i]]++;
        }
        long long int k=min(x,y);
        for(auto it:map1)
        {
            if( map2.find(it.first) == map2.end())
            {
                if(map2[it.first]+it.second%2!=0)
                {
                    cond=1;break;
                }
                long long int w=it.second/2;
                while(w--)
                {
                    vec.push_back(it.first);
                }
            }
            else
            {
                long long int e=abs(map1[it.first]-map2[it.first]);
                
                long long int o=(e/2);
                while(o--)
                {
                    vec.push_back(it.first);
                }
                map2.erase(it.first);
            }
        }
        if(cond==0)
        {
 
            for(auto it:map2)
            {
                if(it.second!=0)
                {
                    if(map1.find(it.first) == map1.end()  )
                    {
                        if(map1[it.first]+it.second%2!=0)
                        {
                            cond=1;break;
                        }
                        long long int w=it.second/2;
                        while(w--)
                        {
                            vec.push_back(it.first);
                        }
                    }
                    else
                    {
                        long long e=abs(map1[it.first]-map2[it.first]);
                        long long int o=ceil(e/2);
                        while(o--)
                        {
                            vec.push_back(it.first);
                        }
                    }
                }
            }
            if(cond==0)
            {
                sort(vec.begin(),vec.end());
                long long int ans=0;
                i=0;
                long long int j=vec.size()-1;
                for(i=0;i<j;i++,j--)
                {
                    long long int z=min(vec[i],vec[j]);
                    ans+=min(z,k*2);
                }
                cout<<ans<<endl;
            }
            else
            {
                cout<<"-1"<<endl;
            }
        }
        else
        {
            cout<<"-1"<<endl;
        }
    }
}