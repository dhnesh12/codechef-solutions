#include <iostream>
using namespace std;

long long modExp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    long long toMultiply = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * toMultiply) % modulus;
        }
        exponent = exponent / 2;
        toMultiply = (toMultiply * toMultiply) % modulus;
    }
    return result;
}

int main() {
	// your code goes here
	int nTests, nElements, input, maxElement, frequency;
	cin >> nTests;
	for (int i=0; i<nTests; i++) {
	    maxElement = -2147483648;
	    frequency = 0;
	    cin >> nElements;
	    for (int j=0; j<nElements; j++) {
	        cin >> input;
	        if (input == maxElement) {
	            frequency++;
	        }
	        else if (input > maxElement) {
	            maxElement = input;
	            frequency = 1;
	        }
	    }
	    cout << modExp(2, frequency, 1000000007) - 1 << endl;
	}
	return 0;
}

// (2**(frequency of maximum element)-1)mod(10**9 + 7)