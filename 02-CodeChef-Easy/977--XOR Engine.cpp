#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int noe,nol,p,count=0,counteve=0,countodd=0,ele;
	    cin>>noe>>nol;
	    int arr[noe];
	    for(int i=0;i<noe;i++){
	        cin>>arr[i];
	    }
	    while(nol--){
	        cin>>p;
	       // cout<<p<<" ";
	        for(int i=0;i<noe;i++){
	            ele=arr[i]^p;
	            //cout<<ele<<" ";
	            for(int a=ele;ele>0;ele=(ele>>1)){
	               // cout<<"        "<<ele<<"  ";
	                if((ele & 1)!=0){
	                    count++;
	                }
	            }
	            
	           // cout<<count<<endl;
	            if((count & 1)==0){
	                counteve++;
	            }
	            else {countodd++;}
	            count=0;
	        }
	        
	        cout<<counteve<<" "<<countodd<<endl;
	        count=0;
	        counteve=0;
	        countodd=0;
	    }
	}
	return 0;
}
