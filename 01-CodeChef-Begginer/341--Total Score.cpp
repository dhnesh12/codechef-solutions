#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lli long long int
#define pb push_back
#define mk make_pair
#define endl "\n"
#define loop(i,a,b) for(lli i=a;i<b;i++)
#define large 1000000007

lli str_to_int(string s){
    stringstream geek(s); 
    int x = 0; 
    geek >> x;
    return x;
}

lli lcm(lli a,lli b){
    return a*b/__gcd(a,b);
}

int main() {
    lli t=1;
    cin>>t;
    while(t--){
        lli n,k;
        cin>>n>>k;
        lli arr[k];
        for(lli i=0;i<k;i++){
            cin>>arr[i];
        }
		for(int i=0;i<10;i++){}
        while(n--){
            string s;
            cin>>s;
            lli ans=0;
            for(lli i=0;i<s.length();i++){
                if(s[i]=='1'){
                    ans+=arr[i];
                }
            }
			for(int i=0;i<10;i++){}
            cout<<ans<<endl;
        }

    }
    return 0;
}
