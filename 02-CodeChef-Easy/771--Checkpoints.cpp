#include <bits/stdc++.h>
using namespace std;
int main() {
	long long int t;std::cin >> t;
	while(t--){
	    long long int n,c;std::cin >> n>>c;
	    std::map< pair<long long int,long long int>, vector<long long int>  >hey;
	    for(long long int i=0;i<n;i++){
	        long long int x,y;std::cin >> x>>y;
	        hey[{x-y , ((x%c)+c)%c}].push_back(x);
	    }
	    long long int answer=0;
	    for(auto it=hey.begin() ; it!=hey.end() ; it++) {
	        sort(it->second.begin() ,it->second.end() );
	        long long int s=it->second.size();
	       // cout<<"size "<<s;
	       //if(s%2==1){
	        long long int p = it->second[s/2];
	        //cout<<"mid "<<p;
	        for(int i=0;i<s;i++){
	            answer+=(abs(it->second[i] - p)/c);
	        }
	       
	       //else{
	       //     long long int a1=0;
	       //     int p = it->second[s/2];
	       //         //cout<<"mid "<<p;
	       //     for(int i=0;i<s;i++){
	       //         a1+=(abs(it->second[i] - p)/c);
	       //     }
	       //     long long int a2=0;
	       //     p=it->second[(s/2)+1];
	       //     for(int i=0;i<s;i++){
	       //         a2+=(abs(it->second[i] - p)/c);
	       //     }
	       //     if(a1>a2){
	       //         a1=a2;
	       //     }
	       //     answer+=a1;
	       //}
	    }
	    std::cout << hey.size() <<" "<<answer<< std::endl;
	    }
    
	return 0;
}
