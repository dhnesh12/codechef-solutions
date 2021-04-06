#include <bits/stdc++.h>
using namespace std;

int main() {
	
	    int r,c;
	    cin>>r>>c;
	    for(int i=0; i<5; i++) {
	        cout<<"U";
	        for(int j=0; j<20*(i+1); j++) cout<<"R";
	        for(int j=0; j<20*(i+1); j++) cout<<"L";
	    }
	    cout<<endl;
	
	return 0;
}
