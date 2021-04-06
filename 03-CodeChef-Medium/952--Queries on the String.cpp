#include<bits/stdc++.h>
using namespace std;
#define assn(n,a,b) assert(n<=b and n>=a)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sd(n) scanf("%d",&n)
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
#define MAXN 100000
#define MAXM 100000
struct segtree
{
    int left[3];
    int right[3];
    LL cnt;
    int total;
    segtree(){
        memset(left,0,sizeof(left));
        memset(right,0,sizeof(right));
        cnt=0;
    }
};
segtree tree[6*MAXN];
string arr;
segtree merge(segtree a, segtree b){
    segtree ret;
    ret.cnt=a.cnt+b.cnt;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if((i+j)%3==0)ret.cnt+=(LL)a.right[i]*(LL)b.left[j];
    for(int i=0; i<3; i++){
        ret.left[i]=a.left[i]+b.left[(6-a.total+i)%3];
        ret.right[i]=b.right[i]+a.right[(6-b.total+i)%3];
    }
    ret.total=(a.total+b.total)%3;
    return ret;
}
void assign(int node, int p){
    tree[node]=segtree();
    tree[node].left[p]=1;
    tree[node].right[p]=1;
    tree[node].total=p;
    if(p==0)tree[node].cnt=1;
}
void build_tree(int node, int a, int b)
{
    if(a > b) return;
    if(a == b){
        assign(node,(arr[a]-'0')%3);
        return;
    }
    build_tree(node*2, a, (a+b)/2);
    build_tree(node*2+1, 1+(a+b)/2, b);
    tree[node] = merge(tree[node*2],tree[node*2+1]);
}
segtree query_tree(int node, int a, int b, int i, int j){
    if(a > b || a > j || b < i){
        segtree ret;
        return ret;
    }
    if(a >= i && b <= j)
        return tree[node];
    segtree q1 = query_tree(node*2, a, (a+b)/2, i, j);
    segtree q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j);
    return merge(q1,q2);
}
void update_tree(int node, int a, int b, int i, int value){
    if(a > b || a > i || b < i)
        return;
    if(a == b){
        assign(node,value%3);
        return;
    }
    update_tree(node*2, a, (a+b)/2, i,  value);
    update_tree(1+node*2, 1+(a+b)/2, b, i, value);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
}
 
int main()
{
    int m,n;
    sd(n),sd(m);
    cin >> arr;
    assn(n,1,MAXN);
    assert(arr.length()==n);
    assn(m,1,MAXM);
    for(int i=0; i<n; i++)
        assn(arr[i],'0','9');
    build_tree(1,0,n-1);
    while(m--){
        int fl,l,r;
        sd(fl),sd(l),sd(r);
        if(fl==2)
            printf("%lld\n",query_tree(1,0,n-1,l-1,r-1).cnt);
        else update_tree(1,0,n-1,l-1,r);
    }
    return 0;
}
 