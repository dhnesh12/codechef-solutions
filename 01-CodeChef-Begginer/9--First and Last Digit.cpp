#include<iostream>
#include<math.h>
using namespace std;
int get_digit(int n){
	int ttl_digit = 0;
	
	while(n != 0){
		ttl_digit++;
		n /= 10;
	}
	return ttl_digit;
}
int main(){
	int test_case, number, first_digit, last_digit;
	int result, ttl_digit;
	
	cin >> test_case;
	while(test_case != 0){
		cin >> number;
		ttl_digit = get_digit(number); // GETTING THE TOTAL DIGITS OF NUMBER
		first_digit = number / pow(10, ttl_digit - 1); // GETTING THE FIRT DIGIT OF THE NUMBER
		last_digit = number % 10; // GETTING THE LAST DIGIT OF THE NUMBER
		result = first_digit + last_digit;
		cout << result << endl;
		
		test_case--;
	}
	
	return 0;
}
/*
INPUT:
	3
	123
	1234
	12345
	
OUTPUT:
	4
	5
	6
*/