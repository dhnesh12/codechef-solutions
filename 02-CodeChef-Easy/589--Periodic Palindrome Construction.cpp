#include <iostream>
using namespace std;

int main() {
	
	int t , length , period;
	cin >> t;
	
	while(t--){
	    
	    cin >> length >> period ;
	    
	    if( length < 3 || (length%period != 0) || period < 3)
	        cout << "impossible" << endl;
	   else{
	       
	       int n = length/period;
	       
	       for(int i = 0 ; i < n ; i++){
	           
	           cout << "a";
	           for(int j = 0 ; j < period - 2 ; j++)
	            cout << "b";
	           cout << "a";
	           
	       }
	       cout << endl;
	   }
	    
	}
	
	
	return 0;
}
