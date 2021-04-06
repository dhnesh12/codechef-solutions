#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using lint = long long;
typedef pair<lint, lint> pi;
const int MAXN = 1000005;

struct node_data{
	lint lazy;
	lint minv;
	node_data(){}
	node_data(lint x){ lazy = 0; minv = x; }
};

node_data operator+(node_data a, node_data b){
	return node_data(min(a.minv, b.minv));
}

/** SPLAY TREE START **/
struct node{
	node *l, *r, *p; 
	int sub;
	int idx;
	lint val;
	node_data dat;
	node(){}
	node(lint _val, int _idx){
		l = r = p = NULL;
		sub = 1;
		idx = _idx;
		val = _val;
		dat = node_data(_val);
	}
}*root;

void push(node *x){
	if(x->l){
		x->l->val += x->dat.lazy;
		x->l->dat.lazy += x->dat.lazy;
		x->l->dat.minv += x->dat.lazy;
	}
	if(x->r){
		x->r->val += x->dat.lazy;
		x->r->dat.lazy += x->dat.lazy;
		x->r->dat.minv += x->dat.lazy;
	}
	x->dat.lazy = 0;
}

void pull(node *x){
	x->sub = 1;
	x->dat = node_data(x->val);
	if(x->l){
		x->sub += x->l->sub;
		x->dat = x->l->dat + x->dat;
	}
	if(x->r){
		x->sub += x->r->sub;
		x->dat = x->dat + x->r->dat;
	}
}

void rotate(node *x){
	if(!x->p) return;
	push(x->p);  
	push(x);
	node *p = x->p;
	bool is_left = (p->l == x);
	node *b = (is_left ? x->r : x->l);
	x->p = p->p;
	if(x->p && x->p->l == p) x->p->l = x;
	if(x->p && x->p->r == p) x->p->r = x;
	if(is_left){
		if(b) b->p = p;
		p->l = b;
		p->p = x;
		x->r = p;
	}
	else{
		if(b) b->p = p;
		p->r = b;
		p->p = x;
		x->l = p;
	}
	pull(p);
	pull(x);
	if(!x->p) root = x; // IF YOU ARE SPLAY TREE
}

void splay(node *x){
	while(x->p){
		node *p = x->p;
		node *g = p->p;
		if(g){
			if((p->l == x) ^ (g->l == p)) rotate(x);
			else rotate(p);
		}
		rotate(x);
	}
}

void kth(int k){ 
	k--; // 1-based
	node *x = root;
	while(true){
		push(x);
		while(x->l && x->l->sub > k){
			x = x->l;
			push(x);
		}
		if(x->l) k -= x->l->sub;
		if(k == 0) break;
		k--;
		x = x->r;
	}
	splay(x);
}

node* split(int l, int r){ // if you modify sth : please climb up the tree
	if(r == root->sub){
		if(l == 1) return root;
		kth(l - 1);
		return root->r;
	}
	kth(r + 1);
	push(root);
	node *tmp = root;
	root->l->p = NULL;
	root = root->l;
	if(l != 1) kth(l - 1);
	tmp->l = root;
	root->p = tmp;
	root = tmp;
	pull(root);
	if(l != 1) return root->l->r;
	return root->l;
}

void del(int x){
	if(root->sub == 1){
		root = NULL;
		return;
	}
	kth(x);
	push(root);
	if(x == 1){
		root = root->r;
		root->p = NULL;
		return;
	}
	if(x == root->sub){
		root = root->l;
		root->p = NULL;
		return;
	}
	root->r->p = NULL;
	root->l->p = NULL;
	node *R = root->r;
	root = root->l; 
	node *p = root;
	push(p);
	while(p->r){
		p = p->r;
		push(p);
	}
	splay(p);
	push(root);
	root->r = R;
	R->p = root;
	pull(root);
}

/** SPLAY TREE END!! **/

struct foo{
	lint x, y, idx;
};

int main(){
	int t;
	scanf("%d",&t);
	for(int i=0; i<t; i++){
		int n; scanf("%d",&n);
		vector<foo> v(n);
		vector<lint> dap(n);
		for(int j=0; j<n; j++){
			scanf("%lld",&v[j].x);
		}
		for(int j=0; j<n; j++){
			scanf("%lld",&v[j].y);
		}
		for(int j=0; j<n; j++){
			v[j].x++;
			v[j].y -= j;
			v[j].idx = j;
		}
		root = new node(v[0].y, v[0].idx);
		for(int j=1; j<n; j++){
			node *nxt = new node(v[j].y, v[j].idx);
			nxt->l = root;
			root->p = nxt;
			pull(nxt);
			root = nxt;
		}
		lint current = 1;
		int curpos = 0;
		for(int j=0; j<n; j++){
			lint ret = 5e18;
			int csz = n - j;
			if(curpos < csz) ret = min(ret, split(curpos + 1, csz)->dat.minv - current + curpos);
			if(0 < curpos) ret = min(ret, split(1, curpos)->dat.minv - current + curpos - csz);
			ret = (max(ret, 0ll) + csz - 1) / csz;
			current += ret * csz;
			int rempos = -1;
			if(curpos < csz){
				auto ptr = split(curpos + 1, csz);
				lint thres = current - curpos;
				if(ptr->dat.minv <= thres){
					while(true){
						push(ptr);
						while(ptr->l && ptr->l->dat.minv <= thres){
							ptr = ptr->l;
							push(ptr);
						}
						if(ptr->val <= thres){
							splay(ptr);
							rempos = (root->l ? root->l->sub : 0);
							current += rempos - curpos + v[root->idx].x;
							dap[root->idx] = current;
							break;
						}
						assert(ptr->r);
						ptr = ptr->r;
					}
				}
			}
			if(rempos == -1 && curpos > 0){
				auto ptr = split(1, curpos);
				lint thres = current - curpos + csz;
				if(ptr->dat.minv <= thres){
					while(true){
						push(ptr);
						while(ptr->l && ptr->l->dat.minv <= thres){
							ptr = ptr->l;
							push(ptr);
						}
						if(ptr->val <= thres){
							splay(ptr);
							rempos = (root->l ? root->l->sub : 0);
							current += rempos - curpos + csz + v[root->idx].x;
							dap[root->idx] = current;
							break;
						}
						ptr = ptr->r;
					}
				}
			}
			assert(rempos >= 0);
			del(rempos + 1);
			if(rempos + 1 <= csz - 1){
				auto ptr = split(rempos + 1, csz - 1);
				ptr->dat.lazy++;
				ptr->dat.minv++;
				ptr->val++;
			}
			curpos = rempos;
		}
		for(auto &i : dap) printf("%lld ", i - 1);
		cout << endl;
	}
}
