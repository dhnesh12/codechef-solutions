#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#define MAXN 100005
#define MAXM 200005
#define MAXQ 100005
using namespace std;
int n,m,q;
// Based on Algorithm https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/a%20fast%20algorithm%20for%20finding.pdf
vector<vector <int> > succ(MAXN), pred(MAXN);
vector<int> parent(MAXN),ancestor(MAXN);
vector<vector <int> > bucket(MAXN);
vector<int>semi(MAXN);
vector<int>vertex(MAXN);
vector<int>dom(MAXN);
vector<int>label(MAXN);
int p[MAXQ];

int c;

void read_input(){
    int i;
    scanf("%d %d %d",&n,&m,&q);
    for(i=1;i<=n;i++){
        parent[i] = 0;
        ancestor[i] = 0;
        semi[i] = 0;
        label[i] = 0;
        vertex[i] = 0;
        succ[i].clear();
        pred[i].clear();
        bucket[i].clear();
    }
    for(i=0;i<m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        succ[u].push_back(v);
        pred[v].push_back(u);
    }
    for(i=1;i<=n;i++){
        sort(succ[i].begin(),succ[i].end());
    }
    for(i=0;i<q;i++){
        scanf("%d",&p[i]);
    }
}

void dfs(int v){
    semi[v] = ++c;
    vertex[c] = label[v] = v;
    ancestor[v] = 0;
    for(vector<int>::iterator it=succ[v].begin();it!=succ[v].end();it++){
        int w = *it;
        if(!semi[w]){
            parent[w] = v;
            dfs(w);
        }
    }
}


void compress(int v){
    if(ancestor[ancestor[v]]){
        compress(ancestor[v]);
        if(semi[label[ancestor[v]]]<semi[label[v]]){
            label[v] = label[ancestor[v]];
        }
        ancestor[v] = ancestor[ancestor[v]];
    }
}

int eval(int v){
    if(!ancestor[v])return v;
    compress(v);
    return label[v];
}

void link(int v,int w){
    ancestor[w] = v;
}

void dominators(){
    int i,u,v,w;
    for(v=1;v<=n;v++){
        bucket[v].clear();
        semi[v] = 0;        
    }
    c = 0;
    dfs(1);
    assert(c==n);
    for(i=n;i>1;i--){
        w = vertex[i];
        for(vector<int>::iterator it=pred[w].begin();it!=pred[w].end();++it){
            v = *it;
            u = eval(v);
            if(semi[u]<semi[w])semi[w] = semi[u];
        }
        bucket[vertex[semi[w]]].push_back(w);
        link(parent[w],w);
    }
}

void query(){
    int i;
    for(i=0;i<q;i++){
        printf("%d ",(int)bucket[p[i]].size());
    }
    printf("\n");
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        read_input();
        dominators();
        query();
    }
    return 0;
}
