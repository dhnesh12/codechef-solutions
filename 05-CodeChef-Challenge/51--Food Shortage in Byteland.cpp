#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	for(int testcase = 1;testcase <= t;testcase++){
		int n, m;
		cin >> n >> m;
		int x[n], y[n], a[n], b[n], c[n];
		for(int i = 0; i < n; i++){
			cin >> x[i] >> y[i] >> a[i] >> b[i] >> c[i];
		}
		int p, q;
		cin >> p >> q;
		bool okay = 0;
		int distance = 2 * (abs(p - x[0]) + abs(q - y[0])) + c[0];
		if(distance <= m)
			okay = 1;
		int shops = 0;
		int minutes = c[0];
		cout << testcase << endl;
		if(okay)
			cout << shops + 1 << " " << minutes << endl;
		cout << "0 0\n";
	}
}