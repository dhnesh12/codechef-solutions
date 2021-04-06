#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

const int nax = 55;
const int mod = 1e9 + 7;
string s[nax];
bool vis[nax][nax];
int n;

bool inside(int r, int c) {
	return 0 <= min(r, c) && max(r, c) < n;
}

void dfs(int r, int c, set<char> & chars, int & count_cells) {
	assert(!vis[r][c]);
	vis[r][c] = true;
	chars.insert(s[r][c]);
	++count_cells;
	for(int i = 0; i < 4; ++i) {
		int r2 = r + dx[i];
		int c2 = c + dy[i];
		if(inside(r2, c2) && !vis[r2][c2] && s[r2][c2] != '.')
			dfs(r2, c2, chars, count_cells);
	}
}

int test_case() {
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> s[i];
		for(int j = 0; j < n; ++j) // clear the array vis[][]
			vis[i][j] = false;
	}
	int answer = 1;
	for(int r = 0; r < n; ++r)
		for(int c = 0; c < n; ++c)
			if(!vis[r][c] && s[r][c] != '.') {
				set<char> chars;
				int count_cells = 0;
				dfs(r, c, chars, count_cells);
				if(count_cells == 1) {
					// this connected component is just a single cell
					// if it's a question mark, all 3 options are ok
					if(chars.count('?'))
						answer = 3LL * answer % mod; // watch out for overlow
				}
				else {
					if(chars.count('G'))
						return 0;
					if(chars.count('P') && chars.count('B'))
						return 0;
					// if there are only question marks, then they all
					// are either polar or brown bears (2 options)
					if(chars == set<char>{'?'})
						answer = 2 * answer % mod;
				}
			}
	return answer;
}

int main() {
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i)
		printf("%d\n", test_case());
}