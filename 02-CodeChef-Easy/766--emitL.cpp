#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;std::cin >> t;
	while(t--){
	    string s;std::cin >> s;
	    unordered_map<char,int>tejus;
	    for(int i=0;i<s.length();i++){
	        tejus[s[i]]++;
	    }
	    if(tejus['L']>=2 && tejus['T']>=2 && tejus['I']>=2 && tejus['M']>=2 && tejus['E']>=1){
	        if(s.length()==9){
	        cout<<"YES\n";}
	        else if(tejus['E']>=2){
	            std::cout << "YES" << std::endl;
	        }
	        else{
	            std::cout << "NO" << std::endl;
	        }
	    }
	    else{
	        cout<<"NO\n";
	    }
	}
	return 0;
}
