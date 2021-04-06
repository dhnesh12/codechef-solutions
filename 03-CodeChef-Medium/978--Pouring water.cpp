#include <bits/stdc++.h>
using namespace std;

int gcd(int a ,int b){
    if(a == 0 ) return b ;
    else return gcd(b%a,a);
}

int steps(int a,int b,int c){
    //always store in a and the push to b and empty b
    int steps = 0;
    int x = 0 , y = 0;
    bool flag = true;
    while(flag){
        if(x  == 0){
            x = a; // fill vessel x
            steps++;
        }
        else if( y == b){
            y = 0; // empty the vessel y
            steps ++;            
        }
        else if( x>0 && y<b){
            //transfer from vessel x to y
             int transfer = min(b-y,x);
             y += transfer;
             x -= transfer;
             steps++;
        }
        if( x == c || y == c) flag = false;
    }
    return steps;
}

int main() {

	int t;
	cin>>t;

	while(t--){
	    
	    int a , b, c;
	    
	    cin>>a;
	    cin>>b;
	    cin>>c;
	    
	    int ans ;
	    if( (c > a && c > b) || ( c%gcd(a,b) != 0 ) ) ans = -1 ;
	    else ans = min(steps(a,b,c),steps(b,a,c));
	    cout<<ans<<endl;
	}

	return 0;
    
}
