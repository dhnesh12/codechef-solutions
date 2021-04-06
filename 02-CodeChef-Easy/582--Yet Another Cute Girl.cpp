#include <bits/stdc++.h>
#define REP(i,a,n) for(int i=a;i<n;i++)
// #define mod 1000000007
#define pb push_back
// #define ff first
// #define ss second
// #define ii pair<int,int>
// #define vi vector<int>
// #define vii vector<ii>
#define N 10000
#define ll long long int
#define endl '\n'
using namespace std;
vector<int> primes(10000,1);
void generatePrimes(){
    primes[1]=0;
    for(int i=2;i*i<10000;i++){
        if(primes[i]){
            for(int j=i*i;j<10000;j+=i)
                primes[j]=0;
        }
    }
}
int main(){
    generatePrimes();
    int t;
    cin>>t;
    while(t--){
        ll l,r,i,j;
        cin>>l>>r;
        int div[r-l+1];
        memset(div,0,sizeof(div));
        for(i=1;i*i<=r;i++){
            ll sq=i*i;
            for(j=((l-1)/i+1)*i;j<=r;j+=i){
                if(j<sq) continue;
                if(j==sq) div[j-l]+=1;
                else div[j-l]+=2;
            }
        }
        int ans=0;
        for(i=l;i<=r;i++) if(primes[div[i-l]]) ans++;
        cout<<ans<<endl;
    }
}
