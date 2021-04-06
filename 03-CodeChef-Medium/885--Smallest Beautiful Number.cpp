#include <bits/stdc++.h>
#define int long long
#define For(i,a,b) for (int i = a; i <= (b); i++)
#define For2(i,a,b) for (int i = a; i >= (b); i--)
#define Test(x) cout << #x << ": " << x << endl;
using namespace std;
string tostr(int a) {
	string F;
	stringstream f;
	f << a << endl;
	f >> F;
	return F;
}
string Min(string a, string b) {
	if (a.length() > b.length()) return b;
	else if (a.length() < b.length()) return a;
	else {
		if (a < b) return a;
		else return b;
	}
}
string Sort(string s) {
	sort(s.begin(), s.end());
	return s;
}
int closestSCP(int a) {
	int i = 0;
	while (++i) {
		if (i * i > a) break;
	}
	return i * i;
}
string f[200005][31];
signed main() {
    cin.tie(0)->sync_with_stdio(0); 
	string def = "999999999999999999999999999999999999999999999999999";
	For(i,1,80000)
		For(j,1,30) f[i][j] = def;
	For(i,2,9) f[i * i][1] = tostr(i);
	For(cs,2,30) {
		For(i,cs,80000) {
			f[i][cs] = def;
			For(j,2,9) {
				if (i - j * j <= 0) break;
				if (f[i - j * j][cs - 1] == def) continue;
				f[i][cs] = Min(f[i][cs], Sort(f[i - j * j][cs - 1] + tostr(j)));
			}
		}
	}
	int t,n;
	cin >> t;
	while (t--) {
		cin >> n;
		//cout << n << " : ";
		double F = sqrt(n);
		if (F == (int)F) {
			For(i,1,n) cout << "1";
			cout << endl;
			continue;
		}
		int P = closestSCP(n);
		int ff = 0;
		string minf,ck;
		For(i,1,n + 1) minf += "1";
		ck = minf;
		For(i,1,n) {
			ff = 0;
			string s = "";
			P = closestSCP(n);
			while (ff <= 10) {
				ff++;
				s = "";
				int p = P - n;
				if (f[p + i][i] != def) {
					For(j,1,n - i) s += "1";
					s += f[p + i][i];
					minf = Min(minf,s);
				}
				P = closestSCP(P);
			}
			if (minf == ck) continue;
			else {
				cout << minf << endl; 
				goto After;
			}
		}
		After: cout << "";
	}
}