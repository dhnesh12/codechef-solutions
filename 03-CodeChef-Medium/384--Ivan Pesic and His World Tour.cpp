
#include<iostream>
#include<cstdio>
#include<cstring>
#include <climits>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define ll long long
#define LL long long
#define LD long double
#define DB double
#define pii pair<int,int>
#define mp make_pair
#define test_n LL N; cin>>N; while(N--)
#define fi first
#define se second
int read(){
    char ch=getchar();int x=0,fl=1;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')fl=-1;
    for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch-'0');
    return x*fl;
}
const int NN=250000+17;
 
int n,q;

vector<int> adj[NN];

int XOR_pre[NN];

//segmeent tree--------------------//
int t[4*NN];
int HHH[NN];
//HLD initials
vector<int> parent, depth, heavy, head, pos,rev;
/*
heavy->to store next heavy node of the same chain if any
head-> for all nodes store head to the chain to which node belongs
pos-> position of the node in the segment tree according to chaining-timing-dfs traversal during HLD
rev-> store original node number according to the index/or position in segment tree
end_ch-> store the ending node(farthest node in the chain w.r.t to  considered root of tree) of the chain to which particular node belongs
parent and depth are usual things
*/

/* 
//=========CARERFUL, don't use if not required, it takes too much memory, consider using only in certain tasks like updating subtree queries after HLD==============//

it's not quite efficient
but it helps greatly in performing the subtree query on the already decomposed tree into chains by considering(storing)
 all the node numbers which are head of the chains in the subtree of considered node

for all nodes , it stores this in the form of vectors<int>
we can also store it in the form of sets but it incurs additional costs of log(n) for insertion and finding and O(n) in merging( but it can be helpful in certain queries)
*/
int cur_pos; //for assigning positions of nodes in the segment tree


/*below is the definition and functions of usual segment tree with lazy updates currently performing max query over range but can be easily modified to make perfoorm any associative function like (min,max,sum,product,xor,and,or) etc*/

void mx_build( int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = HHH[rev[tl]]; 
    } else {
        int tm = (tl + tr) / 2;
        mx_build( v*2, tl, tm);
        mx_build( v*2+1, tm+1, tr);
        t[v] = (t[v*2]^t[v*2+1]); 
    }
}


//------------------------------query function f sum-----------------------------------------//
int maax(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0; //change this also accordingly like 0 for sum and 1 for product
    if (l == tl && r == tr) {
        return t[v];
    }
   
    int tm = (tl + tr) / 2;
    return (maax(v*2, tl, tm, l, min(r, tm))
            ^maax(v*2+1, tm+1, tr, max(l, tm+1), r));
}

//--------------------------update fun of sum-------------------------------//
void update(int v, int tl, int tr, int l, int r, int add) {
    if (l > r)
        return ;
    if (l == tl && r == tr) {
        t[v] = add;
        
    } else {
        
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), add);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        t[v]= (t[v*2]^t[2*v+1]);
    }
}



//============================//

//--------------------------------------//

//HLD_construction---------//


/* below dfs funtion for assigning heavy nodes and deapth for all the nodes according to subtree size and ties broken arbitrarily*/
int dfs(int v) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }

    return size;
}

/*/==below recursive decompose function for decomposing tree into chains 
cosiderig--
if a node has heavy edge the include it in th current chain of which particular node is already a part. 
else start a new chain from that node considring that node as the head of new chian
assigning head
and end_ch using something like backtracking.
also calculating sbtree[] foe each node in this function
*/

void decompose(int v, int h) {
    head[v] = h;  rev[cur_pos]=v; pos[v] = cur_pos++; 
   
   //cout<<" v "<<head[v]<<" cup "<<cur_pos<<" \n";
    if (heavy[v] != -1)
        {decompose(heavy[v], h);

    }
        
    
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
           { decompose(c, c ); 
       
           }
    }
   
}
/* assigning root and initialising vector sizes and cur_pos as 0*/

void init(int root) {
    
    parent = vector<int>(NN);
    depth = vector<int>(NN);
    heavy = vector<int>(NN, -1);
    head = vector<int>(NN);
    pos = vector<int>(NN);
    rev = vector<int>(NN);
    cur_pos = 0;

    dfs(root);

    decompose(root, root);

    mx_build(1,0,n-1);
}

/*query
in this function we accoding to depth of heads of chain of respective two nodes, swaps or calculates the query incorporating the finding of LCA of a and b
*/
pair<int,int> query(int a, int b) {
    int res = 0; //change this also accordingly like 0 for sum and 1 for product
    int t_l=0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = maax(1,0,n-1,pos[head[b]], pos[b]);
        t_l+=(pos[b]-pos[head[b]]+1 );
        res = (res^ cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = maax(1,0,n-1,pos[a], pos[b]);
    t_l+=(pos[b]-pos[a]+1);
    res = (res ^ last_heavy_path_max);
    return {res,t_l};
}

/*below is quite important function for updating the subtree of a node using the decomposed HLD chains
uses sbtree_head we calculated earlier
heads of chains of all nodes that lie in the subtree of node
and updating all chains one by one using segmentTree with lazy_propagation 
*/


//----------------------------------------------//

 
int main(){    
ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

test_n{

FOR(i,0,NN){ adj[i].clear();}

int xo=1;


    cin>>n; cin>>q;
 XOR_pre[1]=1;   
FOR(i,2,n+1)
{ xo^=i;
XOR_pre[i]=xo;
}

FOR(i,0,n){cin>>HHH[i];}

    for(int i=1;i<=n-1;i++){
        int x,y; cin>>x>>y; x--; y--;              
        adj[x].push_back(y);
        adj[y].push_back(x);
        
    }

        init(0);
    
        int a,b,c;
    for(int i=1;i<=q;i++){
         cin>>a;
	if(a==2){
	cin>>b>>c; b--;
	update(1,0,n-1,pos[b],pos[b],c);
	        }
            else{
          cin>>b>>c; b--; c--; int L;
          pair<int,int> xori=query(b,c);
          L=XOR_pre[xori.second];
          if(L==xori.first){cout<<"Yes\n";}else{cout<<"No\n"; }
             }
        }

 
}   
    return 0;
}
