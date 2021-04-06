#include <bits/stdc++.h>
#define sz(X) (int)((X).size())
#define entire(X) X.begin(),X.end()
using namespace std; typedef long long ll;
void OJize(){cin.tie(NULL);ios_base::sync_with_stdio(false);}
template <class T1, class T2>ostream&operator<<(ostream &os,pair<T1,T2>const&x){os<<'('<<x.first<<", "<<x.second<<')';return os;}
template <class Ch, class Tr, class Container>basic_ostream<Ch,Tr>&operator<<(basic_ostream<Ch,Tr>&os,Container const&x){for(auto&y:x)os<<y<<" ";return os;}

struct SuffixTree{
    string S;
    ll cnt = 0;
    int remmed_leaf = 0;

    struct Node{
        SuffixTree *context;
        int l, r, leaf_id = -1;
        Node *par, *suflink = NULL;
        map<char, Node*> nxt;
        Node(SuffixTree *ST, int L, int R, Node *P, bool LEAF):
            context(ST), l(L), r(R), par(P){
                if(LEAF) leaf_id = sz(context->leaves);
            }
        bool is_leaf(){return leaf_id != -1;}
        int size(){
            if(is_leaf()) return sz(context->S) - l;
            return par? r-l+1 : 0;
        }
    };
    struct State{
        Node *node; int pos;
        State(){}
        State(Node *N, int P = -666):
            node(N), pos(P){if(P == -666) pos = node->size()-1;}
        void go_back(){if(pos-- == 0) node = node->par, pos = node->size()-1;}
    } st;

    Node *root;
    vector<Node*> nodes, leaves;

    SuffixTree(string s = "", char termination = '\0'){
        root = new Node(this,-1,-1,NULL,false);
        nodes.push_back(root);
        for(char c: s) append(c);
        if(termination) append(termination);
    }

    Node *make_node(int L, int R, Node *P, bool LEAF){
        nodes.push_back(new Node(this,L,R,P,LEAF));
        return nodes.back();
    }

    // advance state st by character c
    // if new internal node is created, return it
    // otherwise, return NULL
    bool rule3;
    Node *walkdown(char c){
        Node *v = st.node;
        if(st.pos == v->size()-1){
            // [Rule 1] if leaf, append to v's label
            if(v->is_leaf()){v->r++, st.pos++; return NULL;}
            // [Rule 2/3] else, walk down
            if(!v->nxt[c]){
                v->nxt[c] = make_node(sz(S)-1, sz(S)-1, v, true); cnt++;
                leaves.push_back(v->nxt[c]);
            }
            else rule3 = true;
            st.node = v->nxt[c], st.pos = 0;
            return NULL;
        }
        Node *p = v->par;
        // we read st.pos characters in the edge p->v
        // [Rule 3] if match, advance
        if(S[v->l + st.pos + 1] == c){st.pos++; rule3 = true; return NULL;}
        // [Rule 2] else, split to [:st.pos+1] and [st.pos+1:]
        Node *mid = make_node(v->l, v->l + st.pos, p, false); // p <- mid
        p->nxt[S[v->l]] = mid; // p -> mid
        mid->nxt[S[v->l + st.pos + 1]] = v; // v <- mid
        v->par = mid; // v -> mid
        v->l+= st.pos + 1;
        mid->nxt[c] = make_node(sz(S)-1, sz(S)-1, mid, true); cnt++;
        st.node = mid->nxt[c], st.pos = 0;
        leaves.push_back(st.node);
        return mid;
    }

    void find_suflink_state(int l, bool is_addition = true){
        Node *v = st.node;
        if(st.pos == v->size()-1 && v->suflink){
            st = State(v->suflink); return;
        }
        Node *p = v->par;
        // we read st.pos characters on edge p->v
        assert(!p->par || p->suflink);
        if(p->suflink){
            l = sz(S) - st.pos - is_addition - 1;
            st = State(p->suflink);
        }
        else st = State(root, -1);
        while(l < sz(S) - is_addition){
            int l_rem = sz(S) - is_addition - l;
            int pos_rem = st.node->size()-1 - st.pos;
            if(l_rem <= pos_rem){st.pos+= l_rem; break;}
            l+= pos_rem+1;
            st.node = st.node->nxt[S[l-1]], st.pos = 0;
        }
    }

    void append(char c){
        S+= c;
        rule3 = false;
        if(sz(S) == 1){
            st = State(root, -1);
            walkdown(c); return;
        }
        // 1st extension
        cnt+= sz(leaves) - remmed_leaf;
        st = State(leaves.back());
        st.go_back();
        // 2nd+ extension
        Node *old_w = NULL;
        for(int l=sz(leaves); l<sz(S); l++){
            find_suflink_state(l);
            Node *w = walkdown(c); st.go_back();
            if(old_w) old_w->suflink = st.node;
            old_w = w;
            if(rule3){walkdown(c); return;}
        }
    }

    void delete_node(Node *n){
        if(!n->par) return;
        if(st.node == n){
            // n contracts and becomes a new leaf
            int old_pos = st.pos;
            find_suflink_state(sz(leaves)+1, false);
            int to_decrease = n->size() - old_pos - 1;
            cnt-= to_decrease;
            n->leaf_id = sz(leaves);
            n->suflink = NULL;
            leaves.push_back(n);
            n->l = sz(S) - old_pos - 1;
            //st.node = st.node->suflink;
            //st.pos = st.node->size() - 1 - to_decrease;
            //assert(st.pos>=0);
            return;
        }
        cnt-= n->size();
        Node *p = n->par;
        assert(p->nxt[S[n->l]] == n);
        p->nxt.erase(S[n->l]);
        if(p->nxt.empty()) delete_node(p);
    }
};

void print_state(SuffixTree &T){
    cout<<"State: ";
    if(!T.st.node->par) {cout<<endl; return;}
    vector<SuffixTree::Node*> nodes(1, T.st.node);
    vector<string> s(1, T.S.substr(T.st.node->l, T.st.pos+1));
    while(1){
        SuffixTree::Node *v = nodes.back();
        if(!v->par || !v->par->par) break;
        nodes.push_back(v->par);
        s.push_back(T.S.substr(v->par->l, v->par->size()));
    }
    reverse(s.begin(), s.end());
    for(string t: s) cout<<t<<' ';
    cout<<endl;
}

const int MOD = 1000000007;
int main(){OJize();
	int Q; cin>>Q;
    SuffixTree T;
    ll tot = 0;
    while(Q--){
        char q, c; cin>>q;
        if(q == '+') cin>>c, T.append(c);
        else T.delete_node(T.leaves[T.remmed_leaf++]);
        tot+= T.cnt, tot%= MOD;
    }
    cout<<tot;
}