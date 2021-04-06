#include <stdio.h>
#include <vector>
#include <map>
using namespace std;
#define MOD 1000000009
#define mod 1000000007
#define BASE 110
#define N 111111
#define ll long long
char mapper[10] = {11, 24, 56, 69, 8, 48, 50, 30, 21, 4};
ll P[N];
ll p[N];
ll nP[N];
ll np[N];

void init() {

    P[0] = p[0] = 1;
    nP[0] = MOD - 1;
    np[0] = mod - 1;
    for (int i = 1; i < N; i++) {
        P[i] = P[i-1] * BASE % MOD;
        p[i] = p[i-1] * BASE % mod;
        nP[i] = MOD - P[i];
        np[i] = mod - p[i];
    }
}

ll ucombine(ll u, ll v) {
    
    ll U = u >> 32;
       u = u & ((1LL<<32)-1);
    ll R = (U * BASE + v) % MOD;
    ll r = (u * BASE + v) % mod;
    return (R << 32) | r;
}

ll dcombine(ll d, ll v, int x) {
    
    ll D = d >> 32;
       d = d & ((1LL<<32)-1);
    ll R = (D + v * P[x]) % MOD;
    ll r = (d + v * p[x]) % mod;
    return (R << 32) | r;
}

ll usub(ll u1, ll u2, int x) {
    
    ll U1 = u1 >> 32;
       u1 = u1 & ((1LL<<32)-1);
    ll U2 = u2 >> 32;
       u2 = u2 & ((1LL<<32)-1);
    ll R = (U1 + U2 * nP[x]) % MOD;
    ll r = (u1 + u2 * np[x]) % mod;
    return (R << 32) | r;
}


struct Tree {
    vector<Tree*> children;
    ll uhash;
    int size;
    int depth;
    char value;
    bool pal;

    Tree(char value): value(mapper[value]), uhash(0), size(1), depth(0), pal(false) {
        children.clear();
    }

    void add_child(Tree *tree) {
        size += tree->size;
        children.push_back(tree);
    }

    Tree *root_on_centroid() {
        Tree *tree = this;
        while (true) {
            bool good = true;
            for (int idx = 0; idx < tree->children.size(); idx++) {
                Tree *child = tree->children[idx];
                if (child->size > tree->size >> 1) 
                {
                    tree->value = child->value;
                    tree->size -= child->size;
                    Tree *last = tree->children.back();
                    tree->children.pop_back();
                    if (idx < tree->children.size()) {
                        tree->children[idx] = last;
                    }

                    child->add_child(tree);

                    tree = child;
                    good = false;
                    break;
                }
            }

            if (good) {
                return tree;
            }
        }
    }
};

vector<ll> stack;
map<ll,int> hset;
vector< pair<ll,char> > adj[N];

#define hclear() hset.clear()
#define hadd(h) (hset.find(h) == hset.end() ? hset[h] = 1 : hset[h]++)
#define hsub(h) (hset[h]--)
#define hhas(h) (hset.find(h) != hset.end() && hset[h] != 0)


Tree *make_tree(int i, int p = -1, int v = -1) {
    
    Tree *tree = new Tree(v);
    for (int nb = 0; nb < adj[i].size(); nb++) {
        int j = adj[i][nb].first;
        int k = adj[i][nb].second;
        if (p == j) continue;
        tree->add_child(make_tree(j, p = i, v = k));
    }
    return tree;
}

void compute_hashes(Tree *tree, int depth = 0, ll uhash = 0, ll dhash = 0) {
    
    tree->depth = depth;
    tree->uhash = uhash;
    tree->pal = uhash == dhash;
    hadd(uhash);
    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        ll nuhash = ucombine(uhash, child->value);
        ll ndhash = dcombine(dhash, child->value, depth);
        compute_hashes(child, depth+1, nuhash, ndhash);
    }
}

void hadd_all(Tree *tree) {
    
    hadd(tree->uhash);
    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        hadd_all(child);
    }
}

void hsub_all(Tree *tree) {
   
    hsub(tree->uhash);
    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        hsub_all(child);
    }
}

bool any_good(int l, Tree *tree) {
  
    int d = tree->depth;
    int x = l - d;

    stack.push_back(tree->pal ? tree->uhash : -1);

    if (x <= 0) {
       
        if (tree->pal) {
            return true;
        }
    } else {
  
        int y = d - x;
        if (y >= 0) {
            ll uhash = stack[y];
            if (uhash >= 0) {
                uhash = usub(tree->uhash, uhash, x);
                if (hhas(uhash)) {
                    return true;
                }
            }
        }
    }


    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        if (any_good(l, child)) {
            return true;
        }
    }

    stack.pop_back();
    
    return false;
}

int ans;
int r[2];
void compute_answer(Tree *tree) {
    tree = tree->root_on_centroid();
    hclear();
    compute_hashes(tree);
    

    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        hsub_all(child);
        

        #define binsearch(e) do {\
            int L = ans - ((ans & 1) != e);\
            int R = r[e];\
            while (R - L > 2) {\
                int M = (L + R >> 2 << 1) + e;\
                stack.clear();\
                stack.push_back(0);\
                if (any_good(M, child)) {\
                    L = M;\
                } else {\
                    R = M;\
                }\
            }\
            ans = max(ans, L);\
        } while (0)
        binsearch(0); 
        binsearch(1); 
        hadd_all(child);
    }


    for (int idx = 0; idx < tree->children.size(); idx++) {
        Tree *child = tree->children[idx];
        compute_answer(child);
    }
}

int main() {

    init();

    int z;
    scanf("%d", &z);
    while (z--) {
        int n;
        scanf("%d", &n);
        // input
        for (int i = 0; i < n; i++) adj[i].clear();
        for (int a = 1; a < n; a++) {
            int i, j, k;
            scanf("%d%d%d", &i, &j, &k);
            i--, j--;
            adj[i].push_back(make_pair(j, k));
            adj[j].push_back(make_pair(i, k));
        }


        Tree *tree = make_tree(0);
        if (n % 2 == 0) {
            r[0] = n;
            r[1] = n+1;
        } else {
            r[0] = n+1;
            r[1] = n;
        }

        ans = int(n > 1);
        compute_answer(tree);
        printf("%d\n", ans+1);
    }
}