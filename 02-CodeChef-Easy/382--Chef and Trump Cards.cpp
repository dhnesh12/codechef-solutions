#include <iostream>
#include <vector>
#define mod 1000000007
#define endl "\n"

using namespace std;

// A function to calculate the power for a 'base' with exponent 'pow'. It returns the 'result' modulo 'mod'
long long fpow(long long base, long long pow) {

	base = base % mod;
	long long result = 1;
	while(pow > 0) {
    	if(pow & 1)
       		result = (result * base) % mod;
    	base = (base * base) % mod;
    	pow = pow / 2;
	}
	return result;
}

long long modInverse(long long n) {
    return fpow(n , mod - 2);
}

// Returns nCr % mod using Fermat's little theorem
long long nCr(long long n , long long r) {

	// A vector to store the factorial values
    vector <long long> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % mod;

    return (fac[n] * modInverse(fac[r]) % mod * modInverse(fac[n - r]) % mod) % mod;
}

// Driver function
int main() {

	long long t;
	cin >> t;

	while(t--) {
		long long n;
		cin >> n;

		vector <long long> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];

		long long max_element = 0;
		long long cnt = 0;

		// To find the maximum element in the vector
		for(int i = 0; i < n; i++) 
			max_element = max(max_element , a[i]);

		// To count the occurence of maximum element in the vector
		for(int i = 0; i < n; i++)
			if(max_element == a[i])
				cnt++;

		long long ans = 0;

		// If the occurence of maximum element is odd
		if(cnt & 1)
			ans = fpow(2 , n);

		// If the occurence of the maximum element is even
		else 
			ans = (fpow(2 , n) - (fpow(2 , n - cnt) * nCr(cnt , cnt / 2)) % mod + mod) % mod;

		cout << ans << endl;
	}

	return 0;
}