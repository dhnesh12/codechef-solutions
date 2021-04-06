//  to compile code in terminal 
//  g++ code.cpp -o obj

//  to output code in terminal
//  ./obj

// to stop a program use ctrl+c

#include <bits/stdc++.h>
#define int long long
using namespace std;
//const int INF = 1e18 ; // infinite
const int32_t M=1e9 + 7 ; 
 

 
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};


bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

void solve()
{  	
	u64 n;
	cin>>n;
	while(1){
		if(MillerRabin(n))
			{
				cout<<n<<endl;
				break;
			}
			n--;
	}
}
 

int32_t main(){
	#ifndef ONLINE_JUDGE
    #endif
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(NULL); // increases speed of cin and cout
     
// freopen("input.txt", "r", stdin); // for reading input form file name input.txt
// don't output in a file to prevent cases of infinte loop 
    
     int t; 
     //t=1;
	 cin>>t; 	
     while(t--) 
		 {solve();}
		 
	 return 0;
}



