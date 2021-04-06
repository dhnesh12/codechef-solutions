#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 1987654321
#define IINF 87654321987654321
#define MOD 1000000007

const int MAXK = 19;

struct Node {
	bool isEnd;
	ll dp[MAXK];
	Node *nxt[10], *f, *o;
	Node() : isEnd(false), f(NULL), o(NULL) {
		for(int i = 0; i < 10; i++) nxt[i] = NULL;
		memset(dp, 0, sizeof dp);
	}
} *root;

void buildTrie(vector<string> &p) {
	root = new Node();
	int n = (int)p.size();
	for(int i = 0; i < n; i++) {
		Node *cur = root;
		for(char c : p[i]) {
			int x = c - '0';
			if(!cur->nxt[x]) cur->nxt[x] = new Node();
			cur = cur->nxt[x];
		}
		cur->isEnd = true;
	}

	queue<Node*> que;
	for(int i = 0; i < 10; i++) if(root->nxt[i]) {
		root->nxt[i]->f = root;
		que.push(root->nxt[i]);
	}
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		if(q->isEnd) q->o = q;
		else q->o = q->f->o;
		for(int i = 0; i < 10; i++) if(q->nxt[i]) {
			Node *t = q->nxt[i];
			t->f = q->f;
			while(t->f != root && !t->f->nxt[i]) t->f = t->f->f;
			if(t->f->nxt[i]) t->f = t->f->nxt[i];
			que.push(t);
		}
	}
}


inline Node* go(Node *t, int x) {
	while(t != root && !t->nxt[x]) t = t->f;
	if(t->nxt[x]) t = t->nxt[x];
	return t;
}


ll pow_10[MAXK];
void calcDP() {
	pow_10[0] = 1;
	for(int i = 1; i < MAXK; i++)
		pow_10[i] = pow_10[i-1] * 10;

	vector<Node*> order;
	queue<Node*> que;
	que.push(root);
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		order.push_back(q);
		for(int i = 0; i < 10; i++)
			if(q->nxt[i]) que.push(q->nxt[i]);
	}
	reverse(order.begin(), order.end());

	for(auto t : order) {
		if(t->o) {
			for(int k = 0; k < MAXK; k++)
				t->dp[k] = pow_10[k];
		}
	}
	for(int k = 1; k < MAXK; k++) {
		for(auto t : order) if(!t->o) {
			t->dp[k] = 0;
			for(int i = 0; i < 10; i++)
				t->dp[k] += go(t, i)->dp[k-1];
		}
	}
}


inline ll toInt(vector<int> v) {
	ll res = 0;
	reverse(v.begin(), v.end());
	for(auto e : v) {
		res *= 10;
		res += e;
	}
	return res;
}

ll favNum(ll m) {
	vector<int> v;
	while(m) {
		v.push_back(m%10);
		m /= 10;
	}

	ll cnt = 0;
	Node *cur = root;
	for(int d = (int)v.size()-1; d >= 0; d--) {
		for(int i = 0; i < v[d]; i++)
			cnt += go(cur, i)->dp[d];
		cur = go(cur, v[d]);
		if(cur->o) {
			cnt += (toInt(vector<int>(v.begin(), v.begin()+d)) + 1);
			break;
		}
	}
	return cnt;
}

inline ll query(ll l, ll r) {
	return favNum(r) - favNum(l-1);
}


string curStr = "";
void dfs(Node *cur) {
	cout << curStr << ": ";
	for(int i = 0; i < 5; i++) cout << cur->dp[i] << " ";
	cout << endl;
	
	for(int i = 0; i < 10; i++) if(cur->nxt[i]) {
		curStr += to_string(i);
		dfs(cur->nxt[i]);
		curStr.pop_back();
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll l, r, k, n;
	cin >> l >> r >> k >> n;
	vector<string> p(n);
	rep(i, n) cin >> p[i];
	buildTrie(p);
	calcDP();

	ll low = l, high = r, res = -1;
	while(low <= high) {
		ll mid = (low + high) / 2;
		if(query(l, mid) >= k) {
			res = mid;
			high = mid-1;
		} else {
			low = mid+1;
		}
	}
	if(res == -1) cout << "no such number" << endl;
	else cout << res << endl;
}