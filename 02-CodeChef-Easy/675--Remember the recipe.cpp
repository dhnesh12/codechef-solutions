#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin>>n;
    string s[n];
    long long int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>s[i]>>a[i];
    }
    int q;
    cin>>q;
    string b;
    long long int ans=0;
    while(q--)
    {  int t=-1;
    ans=0;
    cin.ignore();
        cin>>b;
        for(int i=0;i<n;i++)
        { bool check=0;
            for(int j=0;b[j]!='\0';j++)
            {
                if(s[i][j]!=b[j])
                {
                    check=1;
                    break;
                }
            }
            if(check==0)
            {
                if(ans<a[i] || ans==0)
                {
                    ans=a[i];
                    t=i;
                }
            }
        }
        if(t==-1)
        {
            cout<<"NO"<<"\n";
        }
        else
        {
        cout<<s[t]<<"\n";
        }
    }
	return 0;
}
