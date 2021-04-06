#include <iostream>
using namespace std;
int gcd(int a,int b){
 int temp;
 if(a<b){
    temp = a;
    a = b;
    b = temp;
 }
 while(b){
    temp = a%b;
    a = b;
    b = temp;
 }
 return a;
}
int main() {
	int t,n,a,k;
	cin>>t;
	while(t--){
	   cin>>n>>a>>k;
	 int x,dn,dd,y;
	 x = (180*(n-2)-(n*a));
	 dn = x;
	 dd = (n*(n-1))/2;
	 dn = (a*dd + dn*(k-1));
	 y = gcd(dn,dd);
	 cout<<(dn/y)<<" "<<(dd/y)<<endl;
	}
	return 0;
}
