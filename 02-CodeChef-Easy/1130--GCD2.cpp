#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		cpp_int a , b;
		cin >> a >> b;
		cout << __gcd(a, b) << "\n";
	}
}