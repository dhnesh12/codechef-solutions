#include <bits/stdc++.h>
using namespace std;

map <int,int> freqArray;

int main() {
	int T, n;
	cin>>T;
	while(T--){
	    cin>>n;
	    int stickArray[n];
	    for(int i=0; i<n; i++){
	        cin>>stickArray[i];
	    }
	    
	    freqArray.clear(); //re-setting the map after every test case
	    
	    for(int i=0; i<n;i++){
	        freqArray[stickArray[i]]++; //building frequency array
	    }
    
        // loop to find the no of duplicate elements
	    int count1 = 0;
	    for(auto x : freqArray){ 
            if (freqArray[x.first] > 1){
                count1++;
            } 
        }
    
        if(count1 > 1){
            // finding 1st  and 2nd largest duplicates
            int maxi1 = -1; //Guard Variable
            int maxi2 = -1; //Guard Variable
            int maxi3 = -1;
            for(auto x : freqArray){ 
                if(freqArray[x.first] > 1){
                    if(x.first > maxi1){
                        maxi2 = maxi1;
                        maxi1 = x.first;
                    }
                    else if(x.first > maxi2 && x.first != maxi1){
                        maxi2 = x.first;
                    }
                }
                if(freqArray[x.first] > 3){
                    maxi3 = max(maxi3, x.first);
                }
            }
            // Printing area of rectangle
            cout<<max((maxi1*maxi2),(maxi3*maxi3))<<"\n";
        }
        else if(count1 == 1){
            //Square case
            int side; 
            int sflag = 0;
            for(auto x : freqArray){ 
                if (freqArray[x.first] > 3){
                    side = x.first;
                    sflag = 1;
                }
            }
            if(sflag == 1){
                cout<<(side*side)<<"\n";
            }
            else{
                cout<<"-1"<<"\n";
            }
        }
        else{
            cout<<"-1"<<"\n";
        }
	}
	return 0;
}
