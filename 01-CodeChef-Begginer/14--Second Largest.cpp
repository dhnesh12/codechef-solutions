#include <bits/stdc++.h>
#include<math.h>
using namespace std;
long max(long a , long b){
    if(a>b){
        return a;
    }
    return b;
}
long min(long n , long m){
    if(n<m){
        return n;
    }
    return m;
}
int main() {
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
	long long  a,b,c;
	cin>>a>>b>>c;
	long long maxN ,minN;
	long long sum = a + b + c ;
	maxN = max(max(a,b),max(b,c));
	minN = min(min(a,b),min(c,c));
	
	long long res = sum - maxN - minN ;
	cout<<res<<endl;
}
	return 0;
}
