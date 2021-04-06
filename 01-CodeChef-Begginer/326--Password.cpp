#include<bits/stdc++.h>
using namespace std;
int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	int t; cin >> t;
	while(t--){
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		string s; cin >> s;
		int condition[5] = {0};
		int n = s.length();
		for(int i = 0 ; i < s.length();i++){
			if(s[i] >= 'a' && s[i] <= 'z'){
				condition[0] = 1;
			}
		     if((i != 0 && i != n - 1) && (s[i] >= 'A' && s[i] <= 'Z')){
				condition[1] = 1;
			}
			if((i != 0 && i != n - 1) && (s[i] >= '0' && s[i] <= '9') ){
				condition[2] = 1;
			}
			if((i != 0 && i != n-1) && (s[i] == '@' || s[i] == '#' || s[i] == '%' || s[i] == '&' || s[i] == '?')){
				condition[3] = 1;
			}

		}
		if(n >= 10){
		    condition[4] = 1;
		}
		if(condition[0] && condition[1] && condition[2] && condition[3] && condition[4]){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}

}