#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	// your code goes here
	int w;
	double b;
	cin>>w>>b;
	
	if(w%5 == 0) {
	    if((w+0.5) <= b) printf("%.2f",b-w-0.5);    
	}
	else printf("%.2f",b);
	
	return 0;
}
