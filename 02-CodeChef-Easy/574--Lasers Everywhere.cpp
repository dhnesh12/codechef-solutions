#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

#define fin std::cin
#define fout std::cout

#define maxn 100005

// std::ifstream fin("input.txt");
// std::ofstream fout("output.txt");
int N, Q;
int h[maxn];
std::pair <int, int> v[maxn];

struct Event{
    int t, pos, val;
};
std::vector <Event> ev;

bool sortEvents(Event a, Event b){
    return a.t < b.t;
}

int ans[maxn];
struct Query{
    int y, x1, x2, ind;
}query[maxn];

bool sortQueriesY(Query a, Query b){
    return a.y < b.y;
}

int bit[maxn];

void update(int pos, int val){
    for(; pos<N; pos+=pos&(-pos))
        bit[pos] += val;
}

int bitQuery(int pos){
    int ans = 0;
    for(; pos>0; pos-=pos&(-pos))
        ans += bit[pos];
    return ans;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    fin >> T;
    while(T --){
        fin >> N >> Q;
        for(int i=0; i<N; i++)
            fin >> h[i];
        for(int i=1; i<N; i++){
            if(h[i-1] < h[i])
                v[i] = {h[i-1], h[i]};
            else 
                v[i] = {h[i], h[i-1]};
        }
            

        ev.clear();
        for(int i=0; i<=N; i++)
            bit[i] = 0;
        for(int i=1; i<N; i++){
            ev.push_back({v[i].first, i, 1});
            ev.push_back({v[i].second+1, i, -1});
        }

        std::sort(ev.begin(), ev.end(), sortEvents);

        for(int i=0; i<Q; i++){
            fin >> query[i].x1 >> query[i].x2 >> query[i].y;
            query[i].ind = i;
        }
            
        std::sort(query, query+Q, sortQueriesY);

        int it=0;
        for(int i=0; i<Q; i++){
            for(; it<ev.size() and ev[it].t <= query[i].y; it++)
                update(ev[it].pos, ev[it].val);
            ans[query[i].ind] = bitQuery(query[i].x2-1) - bitQuery(query[i].x1-1);
        }

        for(int i=0; i<Q; i++)
            fout << ans[i] << '\n';
    }

    return 0;
}