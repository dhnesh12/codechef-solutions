#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <ctime>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

typedef long long int ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

// utility functions
#define ARGMAX(a, b, c, d) (((a) > (b)) ? (c) : (d))
#define ARGMIN(a, b, c, d) (((a) < (b)) ? (c) : (d))
#define VMAX(a, b) ARGMAX(a, b, a, b)
#define VMIN(a, b) ARGMIN(a, b, a, b)

// Modulo functions
#define MODULO 1000000007
#define ADDM(a, b, mod) (((1LL * (a)) + (b))%(mod))
#define ADD(a, b) ADDM(a, b, MODULO)
#define SUBM(a, b, mod) (((1LL * (a)) - (b) + (mod))%(mod))
#define SUB(a, b) SUBM(a, b, MODULO)
#define MULM(a, b, mod) (((1LL * (a)) * (b))%(mod))
#define MUL(a, b) MULM(a, b, MODULO)

unordered_map<int, int> ans;
int N;
int bfs(int state, int finalstate) {

	queue<int> q;
	q.push(state);
	ans[state] = 0;

	while(!q.empty()) {
		state = q.front();
		q.pop();

		if(state == finalstate) {
			return ans[finalstate];
		}

		// cout<<state<<endl;
		for(int i = 0; i < N - 1; i++) {
	        int count = 0;
	        for(int j = i; j < N; j++) {
	            if(state & (1<<j)) {
	                count++;
	            }
	        }
	        for(int j = N - 1; j >= i + 1; j--) {
	            if(count >= (j - i + 2)/2) {
	                int newstate = state | (((1<<(j+1)) - 1) - ((1<<i) - 1));
	                if(ans.find(newstate) == ans.end()) {
	                	ans[newstate] = ans[state] + 1;
	                	q.push(newstate);
	                }
	                break;
	            }
	            if(state & (1<<j)) {
	                count--;
	            }
	        }
	    }
	}
	return ans[finalstate];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--) {
        cin>>N;
        vi data(N, 0);
        ans.clear();
        int max = 0;
        for(int i = 0; i < N; i++) {
            cin>>data[i];
            max = VMAX(max, data[i]);
        }
        int state = 0;
        for(int i = 0; i < N; i++) {
            if(data[i] == max){
                state = state | (1 << i);    
            }
        }
        
        cout<<bfs(state, (1<<N) - 1)<<endl;
    }

	return 0;
}
