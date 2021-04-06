#include <iostream>
# include <cmath>
using namespace std;
int dist(int a1,int a2,int b1,int b2){
    return pow(a1-b1,2)+pow(a2-b2,2);
}
int main() {
	long int n,count=0;
	cin >> n;
	while(n--){
	    int x1,y1,x2,y2,x3,y3;
	    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	    int s1=dist(x1,y1,x2,y2),s2=dist(x2,y2,x3,y3),s3=dist(x1,y1,x3,y3);
	    if(s1==s2+s3 || s2==s1+s3 || s3==s1+s2){
	        count++;
	    }
	}
	cout<<count;
	return 0;
}
