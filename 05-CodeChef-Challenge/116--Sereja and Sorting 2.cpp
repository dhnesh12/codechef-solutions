#include<bits/stdc++.h>
using namespace std;
int a[10005];
int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> a[i];
    vector< pair<int,int> > v;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int id=i;
        for(int j=i+1;j<=n;j++)
        {
            if(a[id]>a[j])
                id=j;
        }

        if(id!=i)
        {
            reverse(a+i,a+id+1);
            ans++;
            v.emplace_back(i,id);
        }
    }

    cout << ans  << endl;
    for(int i=0;i<ans;i++)
        cout << v[i].first << " " << v[i].second << endl;
}
