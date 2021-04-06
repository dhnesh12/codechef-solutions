#include<bits/stdc++.h>
#define ll long long int
#define m 1000000007
int arr1[1000001]={1};

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //freopen("input.txt","r",stdin);
    int n,t;

    cin>>t;

    ll var =1;
    for(int i=1;i<1000001;i++)
    {
        var = (var *i)%m;
        arr1[i] = (arr1[i-1]*var)%m;
    }
    while(t--)
    {
        cin>>n;
        cout<<arr1[n]<<"\n";
    }

    return 0;
}