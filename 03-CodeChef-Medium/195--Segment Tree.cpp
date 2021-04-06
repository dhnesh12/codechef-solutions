#include <bits/stdc++.h>
using namespace std;

/*
Observe that if some node in the tree is tagged, all its
ancestors must be tagged, because to get to that node in the
traversal, we must have passed through all its parents.
So if some ancestor of some node is not tagged, we can mark the case as impossible.

Now, consider the minimum set of ranges for a node's two children.
	- Case 1: The rightmost range of the left child and the leftmost range of the right child touch each other.
		In this case, we can perform a single changeSegtree to modify them both.
		Care must be taken: for this to work, the union of these ranges must not be the node's entire range.
	- Case 2: Those two ranges do not touch.
		In this case, the subproblems for the two nodes can be treated separately.
	- Case 3: One of the subtrees is unmodified.
		Just change the other one.
	- Case 4: None of the subtrees are modified.
		Use a single change to tag the current node.
*/

struct SegtreeSimul {
	int al, ar;
	SegtreeSimul *left, *right;
	bool tagged;
	int rightS = -1, rightE = -1, leftS = -1, leftE = -1;
	SegtreeSimul(int i, int j, queue<bool> &symb) : al(i), ar(j), left(nullptr), 
		right(nullptr) {
		if (i == j) {
			tagged = symb.front(); symb.pop();
		} else {
			int k = (i + j) / 2;
			left = new SegtreeSimul(i, k, symb);
			tagged = symb.front(); symb.pop();
			right = new SegtreeSimul(k + 1, j, symb);
		}
		// dprintf("%d %d tag %c\n", al, ar, (tagged ? 'y' : 'n'));
	}
	~SegtreeSimul() {
		if (left != nullptr) {
			delete left;
			delete right;
		}
	}
	bool checkPossible() {
		if (al == ar) return true;
		else if (!tagged) {
			return (!left->tagged && !right->tagged && left->checkPossible() && right->checkPossible());
		} else {
			return (left->checkPossible() && right-> checkPossible());
		}
	}
	int minChanges() {
		// dprintf("%d %d ttag %c\n", al, ar, (tagged ? 'y' : 'n'));

		if (!tagged) {
			// dprintf("BASE %d %d\n", al, ar);
			return 0;
		} else if (al == ar || (!left->tagged && !right->tagged)) {
			// printf("base %d %d\n", al, ar);
			leftS = rightS = al;
			leftE = rightE = ar;
			return 1;
		} else if (!right->tagged) {
			int ans = left->minChanges();
			leftS = left->leftS, rightS = left->rightS;
			leftE = left->leftE, rightE = left->rightE;
			return ans;
		} else if (!left->tagged) {
			int ans = right->minChanges();
			leftS = right->leftS, rightS = right->rightS;
			leftE = right->leftE, rightE = right->rightE;
			return ans;
		} else {
			int leftAns = left->minChanges();
			int rightAns = right->minChanges();
			leftS = left->leftS, leftE = left->leftE;
			rightS = right->rightS, rightE = right->rightE;
			// printf("%d %d branch [%d, %d], [%d, %d]\n", al, ar, leftS, leftE, rightS, rightE);
				if (left->rightE + 1 == right->leftS && 
					!(left->rightS == al && right->leftE == ar)) {
				return leftAns + rightAns - 1;
			} else {
				return leftAns + rightAns;
			}
		}
	}
};

int segtreeSize(int n) {
	if (n == 1) return 1;
	else return 1 + segtreeSize(n/2) + segtreeSize(n - n/2);
}

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		int n; scanf("%d", &n);
		int m = segtreeSize(n);
		queue<bool> isTagged;
		for (int i = 0; i < m; ++i) {
			int ctag; scanf("%d", &ctag);
			isTagged.push(ctag == 1);
		}
		SegtreeSimul cfing(0, n-1, isTagged);
		if (cfing.checkPossible()) {
			printf("%d\n", cfing.minChanges());
		} else {
			printf("-1\n");
		}
	}
	return 0;
}