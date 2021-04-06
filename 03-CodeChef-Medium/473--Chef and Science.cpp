#include <bits/stdc++.h>
using namespace std;
#define boost ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long int
#define f(i,x,n) for(int i=x;i<n;i++)
#define pb push_back
#define mod 1000000007


int main(){
    boost
    int n;
    cin>>n;
    int arr[n];
    f(i,0,n) cin>>arr[i];
    
    int m; cin>>m;
    while(m--){
        int l,v,k; cin>>l>>v>>k;
        
        string s="";
        f(i,l,n+1){
            if(ceil((double)(i-l)/v)==floor((double)(i-l)/v))
             s+=to_string(arr[i-1]);
        }
        
        
        if(s.length()<k) cout<<"So sad\n";
        else cout<<s[k-1]<<endl;
    }
    
    return 0;
}
