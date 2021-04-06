#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define rep(i, n) for(int i=0; i<n; i++)

#define N 111111
#define M 111111

char s[N];
int hangs[N][28], n;
int chars[M], minLen[M], maxLen[M], L[M], R[M], q[M], qptr;
int st[N<<2], flag[N<<2];
int answer[M], answerR[M];
int ul[N], ur[N];

bool cmp(int i, int j) {
	return L[i] > L[j];
}

// Segment tree
// Supports following operations
// 1) Update a range of values with x
// 2) Given a range, output the minimum value in that range.

// build. This is to initialize the data. Initially all values are set to N
void build(int cur, int s, int e) {
	if(s == e-1) {
		st[cur] = N;
		flag[cur] = -1;
		return;
	}
	build(cur<<1, s, (s+e)>>1);
	build((cur<<1)|1, (s+e)>>1, e);
	st[cur] = N;
	flag[cur] = -1;
}

// Lazy propagation to support range updates.
void resolve(int cur, bool leaf) {
	if(flag[cur] == -1) return;
	if(!leaf) {
		flag[cur<<1] = flag[cur];
		flag[(cur<<1)|1] = flag[cur];
	}
	st[cur] = flag[cur];
	flag[cur] = -1;
}

// Updates the range [S, E-1] with value.
void update(int cur, int s, int e, int S, int E, int value) {
	resolve(cur, s == e-1);
	if(s >= E || e <= S) return;
	if(s >= S && e <= E) {
		flag[cur] = value;
		resolve(cur, s == e-1);
		return;
	}
	int m = (s+e)>>1, c1 = cur << 1, c2 = c1 | 1;
	update(c1, s, m, S, E, value);
	update(c2, m, e, S, E, value);
	st[cur] = min(st[c1], st[c2]);
}

// Gives the minimum in the range [S, E-1]
int query(int cur, int s, int e, int S, int E) {
	resolve(cur, s == e-1);
	if(s >= E || e <= S) return N;
	if(s >= S && e <= E) return st[cur];
	int m = (s+e)>>1, c1 = cur << 1, c2 = c1 | 1;
	return min( query(c1, s, m, S, E), query(c2, m, e, S, E) );
}

void solve() {
	// Initialize the segment tree
	build(1, 0, n+10);

	// Sort the queries in decreasing order of L
	sort(q, q+qptr, cmp);

	int dptr = n-1;
	rep(i, qptr) {
		// As we go from right to left, we update the respective segments with i.
		// And then we query the right segement to get the answer.
		while(dptr >= L[q[i]]) {
			if(ul[dptr] != n+3)
				update(1, 0, n+10, ul[dptr], ur[dptr]+1, dptr);
			dptr--;
		}

		answer[q[i]] = query(1, 0, n+10, minLen[q[i]], maxLen[q[i]]+1);
	}

	// There is one final step, we need to check if the valid answer is crossing R
	rep(i, qptr) {
		int x = answer[q[i]];
		x += max( minLen[q[i]], ul[x]) - 1;
		if( x > R[q[i]] ) {
			answer[q[i]] = answerR[q[i]] = -1;
		} else {
			answerR[q[i]] = x;
		}
	}
}

int main() {
	scanf("%s", s);
	n = strlen(s);

	int m;
	scanf("%d", &m);

	rep(i, m) {
		scanf("%d%d%d%d%d", &chars[i], &minLen[i], &maxLen[i], &L[i], &R[i]);
	}

	rep(i, 28) hangs[n][i] = n;

	for(int i=n-1; i>=0; i--) {
		rep(j, 28) hangs[i][j] = hangs[i+1][j];
		hangs[i][ s[i]-'a' ] = i;
	}

	// hangs[i][j] contains the index of jth different char starting from i
	rep(i, n) {
		sort(hangs[i], hangs[i]+28);
	}

	// We process for each x separately. 
	for(int curChars=1; curChars<=26; curChars++) {
		qptr = 0;

		rep(i, m)
			if(chars[i] == curChars)
				q[qptr++] = i;

		rep(i, n) {
			if(hangs[i][curChars-1] == n) {
				ul[i] = n+3;
				ur[i] = n+3;
				continue;
			}
			ul[i] = hangs[i][curChars-1] - i + 1;
			ur[i] = hangs[i][curChars] - i;
			// ul[i] is the left most index such that s[i..ul[i]] has x chars
			// ur[i] is the right most index such that s[i..ur[i]] has x chars
		}

		solve();
	}

	rep(i, m) printf("%d %d\n", answer[i], answerR[i]);
}