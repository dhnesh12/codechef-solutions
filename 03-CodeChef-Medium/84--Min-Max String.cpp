#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define loop(i,a,b) for (int i=a; i<b; ++i)
 
typedef struct TrieNode {
    int index;
    TrieNode * parent;
    int depth;
    vector < TrieNode *> children;
    TrieNode()
    {
        depth=0;
        index=-1;
        parent=NULL;
        children.assign(26, NULL);
    }
} TrieNode;
 
string  getString(TrieNode * node)
{
    TrieNode * parentnode=node->parent;
    string ans="";
    while (parentnode!=NULL)
    {
        for (int i=0;i<26; ++i)
        {
            if (parentnode->children[i]==node) 
            {
                ans+=((char)('a'+i));
                break;
            }
        }
        node=parentnode;
        parentnode=parentnode->parent;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
 
void build_jump_pointers(TrieNode * node, unordered_map <TrieNode *, vector <TrieNode *> > &jump_pointers)
{
    int pow2=1, size=1;
    for (int i=1; i<=21; ++i)
    {
        pow2*=2;
        if (node->depth < pow2)
        {
            break;
        }
        else size=i+1;
    }
    jump_pointers[node].resize(size);
    jump_pointers[node][0]=node->parent;
    for (int i=1; i<size; ++i)
    {
        jump_pointers[node][i] = jump_pointers[jump_pointers[node][i-1]][i-1];
    }
}
 
TrieNode * addstring(TrieNode * root, const string &s, int index, unordered_map < TrieNode *, vector <TrieNode *> > &jump_pointers)
{
    TrieNode * node=root;
    for (auto c: s)
    {
        if (node->children[c-'a']==NULL) {
            node->children[c-'a']=new TrieNode;
            node->children[c-'a']->parent=node;
            node->children[c-'a']->depth=node->depth+1;
            build_jump_pointers(node->children[c-'a'], jump_pointers);
        }
        node=node->children[c-'a'];
    }
    assert(node->index==-1);
    node->index=index;
    return node;
}
 
int minString(TrieNode * root)
{
    TrieNode * node=root;
    while (1)
    {
        bool leaf=true;
        for (int i=0; i<26; ++i)
        {
            if (node->children[i]!=NULL)
            {
                leaf=false;
                node=node->children[i];
                break;
            }
        }
        if (leaf) break;
    }
    return node->index;
}
 
int maxString(TrieNode * root)
{
    TrieNode * node=root;
    while (1)
    {
        bool leaf=true;
        for (int i=25; i>=0; --i)
        {
            if (node->children[i]!=NULL)
            {
                leaf=false;
                node=node->children[i];
                break;
            }
        }
        if (leaf) break;
    }
    return node->index;
}
 
bool isAncestor(TrieNode * u, TrieNode *v, unordered_map <TrieNode *, vector <TrieNode *> > &jump_pointers)
{
    if (v->depth < u->depth) return false;
    if (v->depth == u->depth) {
        if (v==u) return true;
        return false;
    }
    int diff = v->depth - u->depth;
    TrieNode * node = v;
    for (int i=0; i<=20; ++i)
    {
        if (diff & (1<<i)) {
            node=jump_pointers[node][i];
        }
    }
    if (node==u) return true;
    return false;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    while (T--)
    {
        TrieNode * root = new TrieNode;
        ll N;
        cin >> N;
        vector < TrieNode *> leaves(3e5, NULL);
        unordered_map < TrieNode *, vector <TrieNode *> > jump_pointers;
        int nextindex=1;
        loop(i,0,N)
        {
            string s;
            cin >> s;
            leaves[nextindex]=addstring(root,s, nextindex, jump_pointers);
            ++nextindex;
        }
        //loop(i,0,N) cout << getString(leaves[i+1]) << endl;
        int minindex=minString(root);
        int maxindex=maxString(root);
        ll Q;
        cin >> Q;
        for (int z=1; z<=Q; ++z)
        {
            int type; cin >> type;
            if (type==1) {
                int index; char c;
                cin >> index >> c;
                assert(leaves[index]->index!=-1);
                assert(leaves[index]->children[c-'a']==NULL || leaves[index]->children[c-'a']->index==-1);           
                if (leaves[index]->children[c-'a']==NULL) 
                {
                    if (isAncestor(leaves[index], leaves[minindex], jump_pointers))
                    {
                        if (index==minindex) {
                            minindex=nextindex;
                        }
                        else {
                            int smallest=-1;
                            for (int i=0; i<26; ++i) {
                                if (leaves[index]->children[i]!=NULL)
                                {
                                    smallest=i;
                                    break;
                                }
                            }
                            assert(smallest!=-1);
                            if ((c-'a') < smallest) {
                                minindex=nextindex;
                            }
                        }
                    }
                    if (isAncestor(leaves[index], leaves[maxindex], jump_pointers))
                    {
                        if (index==maxindex) {
                            maxindex=nextindex;
                        }
                        else {
                            int largest=-1;
                            for (int i=25; i>=0; --i) {
                                if (leaves[index]->children[i]!=NULL)
                                {
                                    largest=i;
                                    break;
                                }
                            }
                            assert(largest!=-1);
                            if ((c-'a') > largest) {
                                maxindex=nextindex;
                            }
                        }
                    }
                    leaves[index]->children[c-'a']=new TrieNode;
                    leaves[index]->children[c-'a']->depth = leaves[index]->depth+1;
                    leaves[index]->children[c-'a']->parent=leaves[index];
                }
                leaves[index]->children[c-'a']->index=nextindex;
                leaves[nextindex]=leaves[index]->children[c-'a'];
                build_jump_pointers(leaves[nextindex], jump_pointers);
                //cout << getString(leaves[nextindex]) << endl;
                ++nextindex;
            }
            else if (type==2) cout << minindex << "\n";
            else if (type==3) cout << maxindex << "\n"; 
        }
    }
    return 0;
} 