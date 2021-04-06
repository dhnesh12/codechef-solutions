#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

const int TOTAL_DNAS = 1e4 + 10;
char buf[int(3e4) + 10];
char mp[200];
int query_result[4];

struct node {
	int dna_base;
	int value[4];
	int subtree_size; // BST Value, since this is an implicit treap.
	int prior;
	node *l, *r;
	static node *null;
	node () : prior(rand()), subtree_size(0) {
		memset(value, 0, sizeof (value));
		dna_base = -1;
	}
	node (int base) : dna_base(base), l(null), r(null), prior(rand()), subtree_size(1) {
		value[0] = value[1] = value[2] = value[3] = 0;
		value[base] = 1;
	}
	node (node *base) : dna_base(base->dna_base), l(base->l), r(base->r), prior(base->prior), subtree_size(base->subtree_size) {
		for (int i = 0; i < 4; i++)
			value[i] = base->value[i];
	}
	void combine() {  // Never call combine for null nodes.
		for (int i = 0; i < 4; i++)
			value[i] = l->value[i] + r->value[i];
		value[dna_base]++;
		subtree_size = 1 + l->subtree_size + r->subtree_size;
	}
	void update_base(int new_base) {
		value[dna_base]--;
		dna_base = new_base;
		value[dna_base]++;
	}
};

char mempool[256 * 1024 * 1024];
int mpos = 0;
const size_t S = sizeof (node);
#define Node (mempool + (mpos += S) - S)node

node* node::null = new node();
node *null;

node* merge(node *L, node *R) {
	if (L == null && R == null) return null;
	else if (L == null || R == null) return L == null ? new node(R) : new node(L);
	node *result;
	if (L->prior <= R->prior) {
		result = new node(L);
		result->r = merge(L->r, R);
	} else {
		result = new node(R);
		result->l = merge(L, R->l);
	}
	result->combine();
	return result;
}

void split(node *current_node, node *&L, node *&R, int up, int key) {
	if (current_node == null) return void(L = R = null);
	int current_node_idx = up + current_node->l->subtree_size + 1;
	if (current_node_idx <= key) {
		L = new node(current_node);
		split(current_node->r, L->r, R, current_node_idx, key);
		L->combine();
	} else {
		R = new node(current_node);
		split(current_node->l, L, R->l, up, key);
		R->combine();
	}
}

void query(node *current_node, int up, int node_l, int node_r, int l, int r) {
	if (current_node == null) return ;
	if (node_r < l || node_l > r) return ;
	if (node_l >= l && node_r <= r) {
		query_result[0] += current_node->value[0];
		query_result[1] += current_node->value[1];
		query_result[2] += current_node->value[2];
		query_result[3] += current_node->value[3];
		return ;
	}
	int current_node_idx = current_node->l->subtree_size + up + 1;
	if (l <= current_node_idx && current_node_idx <= r) query_result[current_node->dna_base]++;
	query(current_node->l, up, node_l, node_l + current_node->l->subtree_size - 1, l, r);
	query(current_node->r, current_node_idx, node_l + 1 + current_node->l->subtree_size, node_r, l, r);
}

node* point_update(node *current_node, int up, int idx, int new_base) {
	if (current_node == null) assert(false);
	int current_node_idx = up + 1 + current_node->l->subtree_size;
	node *result = new node(current_node);
	if (current_node_idx == idx) {
		result->update_base(new_base);
	} else if (idx < current_node_idx) {
		result->l = point_update(current_node->l, up, idx, new_base);
	} else {
		result->r = point_update(current_node->r, up + 1 + current_node->l->subtree_size, idx, new_base);
	}
	result->combine();
	return result;
}

int compute_height(node *current_node) {
	if (current_node == null) return 0;
	return max(1 + compute_height(current_node->l), 1 + compute_height(current_node->r));
}

node *dnas[TOTAL_DNAS];
int num_dnas = 0;

void initialize() {
	mp['A'] = 0; mp['G'] = 1; mp['T'] = 2; mp['C'] = 3;
	node::null->l = node::null;
	node::null->r = node::null;
	null = node::null;
}

void printer(node *current_node, int up) {
	if (current_node == null) return;
	printf("Idx: %d Value: %c Up: %d\n", up + current_node->l->subtree_size + 1, "AGCT"[current_node->dna_base], up);
	printer(current_node->l, up);
	printer(current_node->r, up + current_node->l->subtree_size + 1);
}

int main() {
#ifdef LOCAL
	freopen("big.in", "r", stdin);
#endif
	initialize();
	int n, q;
	scanf("%d", &n);
	num_dnas = n;
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		dnas[i] = null;
		int slen = strlen(buf);
		for (int ch = 0; ch < slen; ch++) {
			node *temp = new node(mp[buf[ch]]);
			dnas[i] = merge(dnas[i], temp);
			delete temp; // Since merge creates a new node.
		}
	}
	scanf("%d", &q);
	for (int qnum = 1; qnum <= q; qnum++) {
		char op[10];
		scanf("%s", op);
		if (op[0] == 'M') {
			int id, k;
			char m;
			scanf("%d %d %c", &id, &k, &m);
			dnas[id] = point_update(dnas[id], 0, k, mp[m]);
		} else if (op[1] == 'R') {
			int id1, id2, k1, k2;
			scanf("%d %d %d %d", &id1, &id2, &k1, &k2);
			node *dna1_left, *dna1_right;
			node *dna2_left, *dna2_right;
			split(dnas[id1], dna1_left, dna1_right, 0, k1);
			split(dnas[id2], dna2_left, dna2_right, 0, k2);
			dnas[++num_dnas] = merge(dna1_left, dna2_right);
			dnas[++num_dnas] = merge(dna2_left, dna1_right);
		} else {
			int id, k1, k2;
			scanf("%d %d %d", &id, &k1, &k2);
			memset(query_result, 0, sizeof (query_result));
			query(dnas[id], 0, 1, dnas[id]->subtree_size, k1, k2);
			for (int i = 0; i < 4; i++) {
				if (i) printf(" ");
				printf("%d", query_result[i]);
			}
			puts("");
		}
	}
}
