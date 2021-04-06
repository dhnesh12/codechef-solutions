#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long int lli;

void fast_io(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
}

int main(){

	fast_io();
	//code starts here

	int tc;
	cin >> tc;
	
	while(tc--){
		
		int n, k;
		cin >> n >> k;
		
		//for subtask k = 0;
		for(int i = 0; i < k; i++){
			int x;
			cin >> x;
		}
		
		lli sum = (n * (n+1))/2;
		sum++;
		
		if(sum%2==0){
			cout << "Mom" << endl;
		} else {
			cout << "Chef" << endl;
		}
		
	}

	return 0;

}

