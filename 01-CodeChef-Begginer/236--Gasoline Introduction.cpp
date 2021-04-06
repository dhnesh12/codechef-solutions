#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int f[n];
	    bool check = true;
	    int total = 0;
	    for(int i=0;i<n;i++){
	        cin>>f[i];
	        total += f[i];
	        if(f[i] == 0)
	            check = false;
	    }
	    int count =0,i=0,current=f[0];
	    if(check){
	        cout<<total<<endl;
	    }
	    else{
	        while(current>0){
	            i++;
	            if(i<n){
	                count++;
	                current += f[i];
	                current--;
	            }
	            else{
	                count += current;
	                break;
	            }
	        }
	        cout<<count<<endl;
	    }
	}
	return 0;
}
