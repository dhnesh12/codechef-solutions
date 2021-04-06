#include <iostream>
using namespace std;
#define loni long long
loni we,je,t,n,m,k,temp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k;
        loni lst[n+1][k+1];
        for( we=0;we<n;we++)
        {
            for( je =0;je<k;je++)
            
                cin>>lst[we][je];
                
                
            
        }
        for (we=0;we<n;we++)
        {
            temp = rand() % m+1;
            cout<<temp<<" ";
        }
        cout<<endl;
    }
    return 0;
}