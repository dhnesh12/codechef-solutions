#include <bits/stdc++.h>
using namespace std;
int day (string s){
    if (s == "sunday"){return 0;} else if (s == "monday"){return 1;} else if (s == "tuesday"){return 2;}
    else if (s == "wednesday"){return 3;}else if(s == "thursday"){return 4;}else if (s == "friday"){return 5;}
    else if (s == "saturday"){return 6;}}
int func (string s, string e){int a = day(s);int b = day(e);if (a <= b){return (b-a)+1;}else{return (b-a)+8;}}
int main(){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); int t, l, r; string s, e; cin >> t;
	while (t--){
	    cin >> s >> e >> l >> r; int c = 0, k; int i = func (s,e);
	    while (i <= r){if (i >= l && i <= r){c++; k = i;} i += 7;} if (c > 1){cout << "many" << endl;}
        else if (c == 0){cout << "impossible" << endl;} else{cout << k << endl;}}}