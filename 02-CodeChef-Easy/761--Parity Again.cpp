#include <bits/stdc++.h>
using namespace std;
bool iseven(long long int x){
    long long int p=0;
    while(x>0){
        if(x&1>0){
            p++;
        }
        x=x>>1;
    }
    if(p%2==0){
        return true;
    }
    return false;
}
int main() {
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	long long int t;std::cin >> t;
	while(t--){
	    long long int q;std::cin >> q;
	    std::map<long long int,long long int>isit;
	    std::set<long long int>hey;
	    long long int even=0;long long int odd=0;
	    while(q--){
	        long long int x;std::cin >> x;
	        if(isit[x]==0){
	            std::set<long long int>temp ;
	            for(auto it=hey.begin() ; it!=hey.end();it++){
	                temp.insert((*it)^x);
	            }
	            temp.insert(x);
	            for(auto it=temp.begin();it!=temp.end() ; it++){
	                if(isit[*it]==0){
	                    isit[(*it)]++;
	                    if(iseven((*it))==true){
	                        even++;
	                    }
	                    else{
	                        odd++;
	                    }
	                    hey.insert((*it));
	                }
	            }
	        }
	        
	        cout<<even<<" "<<odd<<"\n";
	    }
	}
	return 0;
}
