#include<bits/stdc++.h>

#define all(c) c.begin(),c.end()
#define loop(T, a, null_ref) for (int(T) = (a); (a) < (null_ref); ++(a)) 

using namespace std;
using ll = long long;

typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll,ll> pll;

long long INFF = 1000000000000000005LL; 
int INF = 1000000005; 

int sieveprime(int n){ 
    vector<bool> prime(n+1, 1);
    for (int p=2; p*p<=n; p++){ 
        if (prime[p] == 1){
            for (int i=p*p; i<=n; i += p) 
                prime[i] = 0; 
        } 
    } 

	int pr=0;
    for (int p=2; p<=n; p++){
        if (prime[p]){
            pr++;
        }
    }
	return pr;
}


int main(){
    int t;
    ll n,m;
    cin>>m>>n;
    cout<<sieveprime(m+n);
}