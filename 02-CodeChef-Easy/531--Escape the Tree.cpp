#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin >> t;
	while(t--){
	    int h;
	    cin >> h;
	    bool flag = false;
	    int x = 2;
	    int q1, q2, q3;
	   cout << 2 << " " << 1 << " " << h << "\n";
	   fflush(stdout);
	   cin >> q2;
	   cout << 1 << " " << q2 << "\n";
	   fflush(stdout);
	   cin >> q1;
	   x = q2;
	   if(q1 == 0){
	       cout << 3 << " " << x << "\n";
	       fflush(stdout);
	       cin >> q3;
	       if(q3 == 1){
	           continue;
	       }
	   }
	   
	    while(!flag){
	        cout << 2 << " " << x << " " << q1 << "\n";
	        fflush(stdout);
	        cin >> q2;
	        if(q1 == 2){
	            flag = true;
	            break;
	        }
	        cout << 1 << " " << q2 << "\n";
	        fflush(stdout);
	        cin >> q1;
	        if(q1 == 0){
	            flag = true;
	            continue;
	        }
	        x = q2;
	    }
	    cout << 3 << " " << q2 << "\n";
	    fflush(stdout);
	    cin >> q3;
	}
	return 0;
}
