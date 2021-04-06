#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

struct Node {
	Node* left = nullptr;
	Node* right = nullptr;
	int key, prior, size, value;
	// x -- key, y -- prior
	Node(int key, int prior, int value) : key(key), prior(prior),
		value(value), left(nullptr), right(nullptr), size(1) {}
};

int node_size(Node* n) {
	if (n == nullptr)
		return 0;
	else
		return n->size;
}

void upd_size(Node* n) {
	if (n != nullptr) {
		n->size = 1 + node_size(n->left) + node_size(n->right);
	}
}

Node* merge(Node* a, Node* b) {
	upd_size(a);
	upd_size(b);
	if (!a)
		return b;
	if (!b)
		return a;
	if (a->prior > b->prior) {
		a->right = merge(a->right, b);
		upd_size(a);
		return a;
	}
	else {
		b->left = merge(a, b->left);
		upd_size(b);
		return b;
	}
}

pair<Node*, Node*> split(Node* a, int key) {
	if (!a) {
		return { 0, 0 };
	}
	upd_size(a);
	if (a->key < key) {
		auto res = split(a->right, key);
		auto l = res.first;
		auto r = res.second;
		upd_size(l);
		upd_size(r);
		a->right = l;
		upd_size(a);
		return { a, r };
	}
	else {
		auto res = split(a->left, key);
		auto l = res.first;
		auto r = res.second;
		upd_size(l);
		upd_size(r);
		a->left = r;
		upd_size(a);
		return { l, a };
	}
}

int find_node(Node* n, int pos) {
	upd_size(n);
	if (node_size(n->left) + 1 == pos)
		return n->value;
	if (node_size(n->left) >= pos)
		return find_node(n->left, pos);
	else
		return find_node(n->right, pos - node_size(n->left) - 1);
}

Node* insert(Node* a, Node* b) {
	if (b == nullptr)
		return a;
	auto res = split(a, b->key);
	auto l = res.first, r = res.second;
	upd_size(l);
	upd_size(r);
	a = merge(merge(l, b), r);
	upd_size(a);
	return a;
}

Node* add_tree(Node* a, Node* b) {
	if (b == nullptr)
		return a;
	//cout << node_size(b)<< ' ' << b->left << '\n';
	auto l = b->left, r = b->right;
	a = insert(a, new Node(b->key, b->prior, b->value));
	//cout << node_size(b) << ' ' << b->left << '\n';
	//cout << node_size(a) << '\n';
	if (l != nullptr)
		a = add_tree(a, l);
	if (r != nullptr)
		a = add_tree(a, r);
	upd_size(a);
	return a;
}

Node* unite(Node* a, Node* b) {
	upd_size(a);
	upd_size(b);
	//cout << node_size(a) << ' ' << node_size(b) << '\n';
	if (node_size(b) > node_size(a))
		swap(a, b);
	//cout << node_size(a) << ' ' << node_size(b) << '\n';
	a = add_tree(a, b);
	return a;
}

int main() {
	srand(time(NULL));
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<Node*> arr(n);
	for (int i = 0; i < n; ++i)
		arr[i] = new Node(i + 1, rand(), i + 1);
	for (int i = 0; i < q; ++i) {
		string query;
		int a, b;
		cin >> query >> a >> b;
		--a;
		--b;
		if (query == "UNION") {
			arr.push_back(unite(arr[a], arr[b]));
		}
		else {
			cout << find_node(arr[a], b + 1) << '\n';
		}
	}
	return 0;
}