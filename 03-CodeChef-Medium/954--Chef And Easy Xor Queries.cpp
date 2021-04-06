#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n{0}, q{0};
	cin >>n >> q;
	int a[n];
	for(int i  = 0 ; i< n; i++)
	    cin >> a[i];
	int type{0}, index{0}, num{0};
	for(int i = 0; i < q; i++){
	    cin >> type >> index >> num;
	    if(type == 1){
	        a[index - 1] = num;
	    }
	    else{
	        int ans{0};
	        int x{0};
	        for(int j = 0; j < index; j++){
	            x = x ^ a[j];
	            if(x == num)
	                ans++;
	        }
	        cout << ans << endl;
	    }
	}
	return 0;
}
