#include <bits/stdc++.h>
using namespace std;
#define lint long long int
lint dp[20][504][2][(1<<9)+10];
lint k;
vector<lint> v;
lint fun(lint pos,lint mod,bool tight,lint mask,lint last){
    if(pos == v.size()){
        lint c = 0;
        for(lint i = 1 ; i < 10 ; i++)
           if(i != 5 and (mask&(1<<(i-1))))
              if(mod%i == 0)
                c++;
        if((mask&(1<<(4))) && last%5 == 0) c++;
        return (c >= k);
    }
    if(dp[pos][mod][tight][mask] != -1) return dp[pos][mod][tight][mask];
    lint ans = 0;
    lint e = tight ? v[pos] : 9;
    for(lint i = 0 ; i <= e ; i++){
        if(i == 0){
            ans += fun(pos+1,(mod*10)%504,(tight&(i==e)),(mask),0);
        }
        else{
            ans += fun(pos+1,(mod*10+i)%504,(tight&(i==e)),(mask|(1<<i-1)),i);
        }
    }
    return dp[pos][mod][tight][mask] = ans;
}
lint make_vector(lint n){
    v.clear();
    if(n == 0){
        v.push_back(n);
    }
    else{
        while(n){
            v.push_back(n%10);
            n /= 10;
        }
    }
    memset(dp,-1,sizeof(dp));
    reverse(v.begin(),v.end());
    return fun(0,0,1,0,0);
}

int main() {
	// your code goes here
	lint t;
	cin>>t;
	while(t--){
	    lint l,r;
	    cin>>l>>r>>k;
	    lint ans = make_vector(r) - make_vector(l-1);
	    cout<<ans<<"\n";
	}
	return 0;
}
