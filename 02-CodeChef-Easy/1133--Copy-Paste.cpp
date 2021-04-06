#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int a[n];
        int h[1000001]={0};
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            h[a[i]]++;
        }
        int count=0;
        for(int i=0;i<1000001;i++){
            if(h[i]>0)
            count++;
        }
        cout<<count<<endl;
    }
    
    return 0;
}
