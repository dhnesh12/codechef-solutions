#include <bits/stdc++.h>
using namespace std;

#define FOR(i, x) for( int i = 1; i <=x; i++ )
#define REP(i, x) for( int i = 0; i < x; i++ )
#define FORALL(it, x) for( __typeof(x.begin()) it = x.begin(); it != x.end(); it++ )
#define PB push_back
#define LL long long

typedef vector<int> VI;
typedef vector<VI> VVI;

const int MAX_N = 101000;

VVI tree(MAX_N);

int num[MAX_N];

int deg_ref[MAX_N];
int deg_cur[MAX_N];

int level[MAX_N];

int anc[MAX_N][25];
int next_num[MAX_N];

int n, q;
int v;

void renew(){
    level[0] = -100;
    FOR(i, n){
        tree[i].clear();
        num[i] = -1;
        deg_cur[i] = 0;
        level[i] = 0;
        next_num[i] = 0;
        REP(j, 22) anc[i][j] = 0;
    }
}

void wczytaj(){
    REP(i, n-1){
        int a, b;
        cin >> a >> b;
        tree[a].PB(b);
        tree[b].PB(a);
    }
}

void ukorzen(int i){
    FORALL(it, tree[i])
        if( *it != anc[i][0] ){
            anc[*it][0] = i;
            FOR(j, 20) anc[*it][j] = anc[anc[*it][j-1]][j-1];
            if( num[i] == num[*it] ) next_num[*it] = next_num[i];
            else next_num[*it] = i;

            level[*it] = level[i]+1;

            ukorzen(*it);
        }
}

int LCA(int a, int b){
    int wsk = 20;
    if( level[a] > level[b] ) swap(a, b);
    while( level[b] > level[a] ){
        if( level[b] - (1<<wsk) >= level[a] ) b = anc[b][wsk];
        wsk--;
    }

    if( a == b ) return a;

    wsk = 20;
    while( wsk >= 0 ){
        if( anc[a][wsk] != anc[b][wsk] ){
            a = anc[a][wsk];
            b = anc[b][wsk];
        }
        wsk--;
    }
    return anc[a][0];
}

LL inwersje(int a, int b, int lca){
    LL lewa[25];
    LL prawa[25];

    REP(i, 24) lewa[i] = prawa[i] = 0;

    while( level[next_num[a]] >= level[lca] ){
    //cout << a << " " << b << " "<< lca << " " << num[a] << level[next_num[a]] - level[a] << endl;
        lewa[num[a]] = level[a] - level[next_num[a]];
        a = next_num[a];
    }
    lewa[num[a]] = level[a] - level[lca];
    lewa[num[lca]]++;

    while( level[next_num[b]] >= level[lca] ){
        prawa[num[b]] = level[b] - level[next_num[b]];
        b = next_num[b];
    }
    prawa[num[b]] = level[b] - level[lca];

    for( int i = 22; i; i-- ) lewa[i-1] += lewa[i];
    REP(i, 23) lewa[i] = lewa[i+1];

    LL inw = 0;
    for( int i = 22; i; i-- ){
        inw += lewa[i] * prawa[i];
        prawa[i] += prawa[i+1];
        lewa[i-1] += prawa[i];
    }

    return inw;
}

void process(){
    FOR(i, n) deg_cur[i] = deg_ref[i] = tree[i].size();

    int krok = 1;
    stack<int> do_brania;
    stack<int> nastepne;
    stack<int> popraw;

    FOR(i, n) if( tree[i].size() <= 1 ) do_brania.push(i);

    while( !do_brania.empty() ){
        while( !do_brania.empty() ){
            v = do_brania.top();
            do_brania.pop();
            num[v] = krok;
            FORALL(it, tree[v]) if( num[*it] == -1 )
                if( deg_ref[*it] <= 2 ) do_brania.push(*it);
                else{
                    deg_cur[*it]--;
                    popraw.push(*it);
                    if( deg_cur[*it] == 1 ) nastepne.push(*it);
                }
        }
        for( ; !popraw.empty(); popraw.pop() )
            deg_ref[popraw.top()] = deg_cur[popraw.top()];
        swap(do_brania, nastepne);
        krok++;
    }

    ukorzen(v);
}

void answer(){
    REP(i, q){
        int u, v;
        cin >> u >> v;
        //cout << LCA(u, v) << endl;
        cout << inwersje(u, v, LCA(u, v)) << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--){
        cin >> n >> q;
        renew();
        wczytaj();
        process();
        answer();
    }
    return 0;
}
