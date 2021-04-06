#include <bits/stdc++.h>
using namespace std;

int n, m, k[2];
string v[2][1005], asktp[2] = {"A", "B"}, resp[2];
map<string, bool> inset[2];
map<string, set<string> >adj[2];
set<string> poss[2];

int main(){
	cin >> n >> m >> k[0] >> k[1];
	for(int i = 0; i < 2; i ++){
		for(int j = 0; j < n; j ++){
			cin >> v[i][j];
			inset[i][v[i][j]] = (j < k[i]);
			poss[i].insert(v[i][j]);
		}
		string u, vv;
		for(int j = 0; j < m; j ++){
			cin >> u >> vv;
			adj[i][u].insert(vv);
			adj[i][vv].insert(u);
		}
	}

	for(;poss[0].size();){
		int sz = poss[0].size();
		resp[0].clear(); resp[1].clear();
		for(string s : poss[0])
			if(inset[0][s] && adj[0][s].size() <= sz / 2)
				resp[0] = s;
		for(string s : poss[1])
			if(inset[1][s] && adj[1][s].size() > sz / 2)
				resp[1] = s;

		bool you = 0;
		for(int i = 0; i < 2; i ++) if(resp[i].size()){
			you = 1;
			cout << asktp[i] << " " << resp[i] << endl;
			cin >> resp[1 - i];

			if(inset[0][resp[0]] && inset[1][resp[1]]){
				cout << "C Yes" << endl;
				exit(0);
			}

			for(int j = 0; j < 2; j ++){
				set<string> nw; nw.clear();
				for(string s : poss[j]){
					if(i == 0 && adj[j][resp[j]].count(s) != 0)
						nw.insert(s);
					else if(i == 1 && adj[j][resp[j]].count(s) == 0)
						nw.insert(s);
				}

				poss[j] = nw;
				for(string u : nw){
					set<string> tmp;
					for(string v : adj[j][u])
						if(nw.count(v)) tmp.insert(v);
					adj[j][u] = tmp;
				}
			}

			break;
		}

		if(!you){
			cout << "C No" << endl;
			exit(0);
		}
	}

	cout << "C No" << endl;
	exit(0);
}