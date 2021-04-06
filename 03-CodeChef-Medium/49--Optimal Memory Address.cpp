#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
int dist_sum;

struct trie{
    struct node{
        int isSpecial;
        int subtree_size;
        map<int,pair<int,node*> > ch;
        node(){isSpecial = 0;}
        node* add(int p, int q){
            auto nx = ch.find(p);
            if (nx == ch.end()){
                node* nn = new node();
                ch[p] = make_pair(q,nn);
                return nn;
            }
            else{
                int edg_len = nx->second.first;
                node* nxt = nx->second.second;
                if (edg_len == q) return nxt;
                else if (q > edg_len){
                    return nxt->add(p,q-edg_len);
                }
                else{
                    node* nn = new node();
                    ch[p] = make_pair(q,nn);
                    nn->ch[p] = make_pair(edg_len-q,nxt);
                    return nn;
                }
            }
        }
    };
    node* root;
    trie(){root = new node();}
    void add (vector<pair<int,int> > nv){
        node* cn = root;
        for (auto v : nv){
            cn = cn->add(v.first,-v.second);
        }
        cn->isSpecial++;
    }
    
    int dfs(node* crr){
        int sm = 0;
        for (auto vv : crr->ch){
            sm += dfs(vv.second.second);
        }
        sm+=crr->isSpecial;
        crr->subtree_size = sm;
        return sm;
    }
    
    void dfs_util(){
        dfs(root);
    }
    
    int solve(){
        node* cn = root;
        int ans = dist_sum;
        while (true){
            if (cn->ch.empty()) return ans;
            bool is_better=0;
            for (auto vv : cn->ch){
                node* look = vv.second.second;
                int len = vv.second.first;
                if (look->subtree_size > (n/2)){
                    ans -= (look->subtree_size*len);
                    int ky = n-(look->subtree_size);
                    ans += (ky*len);
                    cn = look; is_better = 1; break;
                }
            }
            if (!is_better) return ans;
        }
    }
};

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    dist_sum = 0;
    cin >> n;
    trie T;
    vector<pair<int,int> > stu[n];
    for (int i=0; i<n; i++){
        int k; cin >> k; vector<pair<int,int> > cr;
        int p,q;
        for (int j=0; j<k; j++){
            cin >> p >> q;
            stu[i].emplace_back(p,-q);
            //assert(q==1);
            dist_sum += q;
        }
    }
    sort(stu,stu+n);
    for (int i=0; i<n; i++) T.add(stu[i]);
    T.dfs_util();
    cout << T.solve();
}