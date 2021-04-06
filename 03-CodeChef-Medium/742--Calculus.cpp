#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stdio.h>
#include <iostream>

const long long mod = 998244353;

long long ext_gcd(long long a,long long b,long long &x,long long &y){
	if(b==0){  x=1,y=0;  return a;  }
	long long d=ext_gcd(b,a%b,x,y) , temp=x;
	x=y,y=temp-a/b*y;  return d;
}

long long get_ni(long long a, long long p){
	long long x,y;
	ext_gcd(a,p,x,y);
	return (x % p + p) % p;
}

int main() {
    long long n;
    std::cin >> n;
    long long x = 2;
    for (long long i = 2; i <= n; i++) {
        x = (x + get_ni(2 * i - 1, mod) * 2) % mod;
    }
    std::cout << x << std::endl;
    return 0;
}