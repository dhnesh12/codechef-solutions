#include <bits/stdc++.h>

using namespace std;



int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);    
    long long i,n,m,j,k,t,ans=0,temp=0,ma=0;
    cin>>t;
    while(t--)
    {
        cin>>n;
        temp=0;ans=0;
        long long a[n],o[1000010]={0};
        //set<pair<long long ,long long >>s;
        for(i=0;i<n;i++)
        {
            cin>>a[i];
            o[a[i]]++;
        }
        sort(a,a+n);
        for(i=0;i<n;i++)
        {
            if(a[i]==a[i+1])continue;
            for(j=i;j<n;j++)
            {
                if(a[j]==a[j+1])continue;
                if(a[i]<=o[a[j]] && a[j]<=o[a[i]])
                {
                    //if(s.find({a[i],a[j]})==s.end())
                    {
                    //s.insert({a[i],a[j]});
                      if(a[i]!=a[j])ans++;
                        ans++;
                    }
                }
            }
        }
         
       
        
        cout<<ans<<"\n";
            
    }
 return 0;   
}