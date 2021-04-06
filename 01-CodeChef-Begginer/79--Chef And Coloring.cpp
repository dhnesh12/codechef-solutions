#include <iostream>
using namespace std;
int max(int a,int b){
    return a>b?a:b;
}
int main() {
	// your code goes here
	int t,i;
	cin >> t;
	for(i=0;i<t;i++){
	    int n,c1=0,c2=0,c3=0,flag=0,j;
	    cin >> n;
	    char str[n];
	    cin >> str;
	    for(j=0;j<n;j++){
	        if(str[j]=='R')
	            c1++;
	        else if(str[j]=='G')
	            c2++;
	        else
	            c3++;
	    }
	    if(c1==n || c2==n || c3==n)
	        flag=0;
	    else
	        flag=n-max(c1,max(c2,c3));
	    cout << flag << endl;
	}
	return 0;
}
