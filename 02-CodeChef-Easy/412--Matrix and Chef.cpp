#include <iostream>
#include <bits/stdc++.h>

#define fio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define mod 1000000007
#define ll long long
#define pb push_back
#define mp make_pair
#define gcd __gcd
#define F first
#define S second
#define PI 3.14159265358979323

using namespace std;




int main() {

fio;
int TC=1;
//cin>>TC;
    while(TC--){
        ll n,q;
        cin>>n>>q;
        ll a[n+2]={0},b[n+2][n+2];

        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                cin>>b[i][j];
            }
        }
        //cout<<n<<" "<<q<<" \n";/*

        for(ll i=1;i<=n;i++){
            for(ll j=i+1;j<=n;j++){
                if(abs(a[i]-a[j])!=b[i][j]){
                    ll can1=a[i]+b[i][j];
                    ll can2=a[i]-b[i][j];

                    if(abs(can1)<abs(can2)) a[j]=can1;
                    else if(abs(can1)>abs(can2)) a[j]=can2;
                    else a[j]=-abs(can1);
                }
            }
        }
        for(ll i=1;i<=n;i++) cout<<a[i]<<" ";
        cout<<"\n";

        while(q--){
            ll p;
            cin>>p;
            for(ll i=1;i<=n;i++){
                cin>>b[p][i];
                b[i][p]=b[p][i];
            }

            for(ll i=1;i<=n;i++){
                for(ll j=i+1;j<=n;j++){
                    if(abs(a[i]-a[j])!=b[i][j]){
                        ll can1=a[i]+b[i][j];
                        ll can2=a[i]-b[i][j];

                        if(abs(can1)<abs(can2)) a[j]=can1;
                        else if(abs(can1)>abs(can2)) a[j]=can2;
                        else a[j]=-abs(can1);
                    }
                }
            }
            for(ll i=1;i<=n;i++) cout<<a[i]<<" ";
            cout<<"\n";
        }


    }
return 0;
}



/*

3 2
0 1 2
1 0 1
2 1 0
1
0 4 3
2
4 0 7

*/
