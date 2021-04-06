#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
   cin>>t;
   while(t--)
   {
       int n,m,q;
       cin>>n>>m>>q;
       int size1=10002;
       int row[n]={0};
       int col[m]={0};
       int r,c;
       for(int i=0;i<q;i++)
       {
        cin>>r>>c;
        row[r-1]++;
        col[c-1]++;
       }
       int odd=0;
       for(int i=0;i<n;i++)
       {
        //   cout<<col[i]<<" ";
           if(row[i]%2==1)
            odd++;
       }
//cout<<odd;
       long long int ans=0;
       for(int i=0;i<m;i++)
       {
           if(col[i]%2==1)
           {
               ans=ans+(n-odd);
           }
           else
            ans=ans+odd;
       }

       cout<<ans<<endl;
   }


    return 0;
}
