#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin>>T;
    while(T--)
    {
        int d;
        cin>>d;
        cout<<2*d<<endl;
        for(int i=0;i<d;i++)
        cout<<'a';
        for(int i=0;i<d;i++)
        cout<<'b';
        cout<<endl;
    }
	return 0;
}
