#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll inf = 1ll * 1000000000 * 1000000000;
struct LINE{
    ll m , c;
    int index;
    LINE(ll mm , ll cc , int ii):m(mm),c(cc),index(ii){}
    ll eval(ll x){
        return x * m + c;
    }
};
bool operator < (const LINE &A , const LINE &B){
    if(A.m != B.m) return A.m < B.m;
    else return A.c < B.c;
}
ll intersection(LINE A , LINE B){
    if(A.m == B.m && A.c < B.c) return inf + 1;
    if(A.c >= B.c) return 0;
    ll a = B.c - A.c , b = A.m - B.m;
    return (a + b - 1)/b;
}
struct BLOCK{

    vector < LINE > lines , CH;
    vector < ll > intersections;
    int queries_cnt , our_guy;
    ll allCoefAdd , allSlopeAdd , allSlopeEffect;

    BLOCK(){
        lines.clear(); intersections.clear(); CH.clear();
        queries_cnt = our_guy = allCoefAdd = 0;
        allSlopeAdd = allSlopeEffect = 0;
    }
    void increment(){
        ++queries_cnt;
        allSlopeEffect += allSlopeAdd;
    }
    void relax(){
        for(auto &L : lines){
            L.c += 1ll * L.m * queries_cnt + allCoefAdd + allSlopeEffect;
            L.m += allSlopeAdd;
        }
        queries_cnt = allCoefAdd = 0;
        allSlopeAdd = allSlopeEffect = 0;
    }
    void convex_hull(){
        intersections.clear();
        CH.clear();
        for(auto &L : lines){
            while(CH.size() >= 2){
                if(intersection(L , CH.back()) <= intersections.back()){
                    intersections.pop_back();
                    CH.pop_back();
                }
                else break;
            }
            bool ok = 1;
            if(!CH.empty())
                if(intersection(L , CH.back()) > inf)
                    ok = 0;
            if(ok){
                if(CH.size() > 0)
                    intersections.push_back(intersection(L , CH.back()));
                CH.push_back(L);

            }
        }
        if(CH.size() < 2) assert(intersections.size() == 0);
        else assert(intersections.size() + 1 == CH.size());
    }

    void init(){
        sort(lines.begin() , lines.end());
        convex_hull();
    }

    void rearrange(int st , int en){
        vector < LINE > v1 , v2;
        for(auto &L : lines){
            if(L.index >= st && L.index <= en) v1.push_back(L);
            else v2.push_back(L);
        }
        lines.clear();
        int it1 = 0 , it2 = 0;
        while(it1 < v1.size() && it2 < v2.size()){
            if(v1[it1] < v2[it2]) lines.push_back(v1[it1++]);
            else lines.push_back(v2[it2++]);
        }
        while(it1 < v1.size()) lines.push_back(v1[it1++]);
        while(it2 < v2.size()) lines.push_back(v2[it2++]);
    }
    void fix(int st , int en , bool re = false){
        our_guy = 0;
        if(re)
            rearrange(st , en);
        convex_hull();
    }
    ll get_max(){
        if(intersections.empty())
            return CH[0].eval(queries_cnt) + allCoefAdd + allSlopeEffect;
        while(our_guy < intersections.size() && queries_cnt >= intersections[our_guy])
            ++our_guy;
        return CH[our_guy].eval(queries_cnt) + allCoefAdd + allSlopeEffect;
    }

    ll get_specified_max(int st , int en){
        ll ret = -inf;
        for(auto &L : lines){
            if(L.index >= st && L.index <= en){
                ret = max(ret , L.eval(queries_cnt) + allCoefAdd + allSlopeEffect);
            }
        }
        return ret;
    }
    void specified_increment(int st , int en){
        relax();
        for(auto &L : lines)
            if(L.index >= st && L.index <= en)
                L.c += L.m;
        fix(st , en);

    }
    void increment_coef(ll V){
        allCoefAdd += V;
    }
    void increment_slope(ll V){
        allSlopeAdd += V;
    }
    void specified_increment_slope(int st , int en , ll V){
        relax();
        for(auto &L : lines)
            if(L.index >= st && L.index <= en)
                L.m += V;
        fix(st , en , 1);
    }
    void specified_increment_coef(int st , int en , ll V){
        relax();
        for(auto &L : lines)
            if(L.index >= st && L.index <= en)
                L.c += V;
        fix(st , en);
    }

}bucket[3000];
const int MX = (1<<19);
int SQ , n , QN , bucket_cnt;
int A[MX] , B[MX];
int main(){
    #ifdef YALALOV
    freopen("in.in","r",stdin);
    #endif // YALALOV
    scanf("%d %d",&n,&QN);
    SQ = 1;
    while(SQ * SQ < n) ++SQ;
    SQ = 164;
    for(int j = 1 ; j <= n ; j++) scanf("%d",&A[j]);
    for(int j = 1 ; j <= n ; j++) scanf("%d",&B[j]);

    for(int a = 1 ; ; a+=SQ){
        ++bucket_cnt;
        int b = min(n , a + SQ - 1);
        bucket[bucket_cnt] = BLOCK();
        for(int j = a ; j <= b ; j++)
            bucket[bucket_cnt].lines.push_back(LINE(B[j] , A[j] , j));
        bucket[bucket_cnt].init();
        if(b == n) break;
    }
    while(QN--){
        int cmd , st , en;
        scanf("%d %d %d",&cmd,&st,&en);
        long long ans = -inf;
        int V;
        if(cmd > 2) scanf("%d",&V);
        for(int a = 1 , idx = 1 ; a <= n ; ++idx ,  a+=SQ){
            int b = min(n , a + SQ - 1);
            if(st > b || en < a) continue;
            if(a >= st && b <= en){
                //cout<<qw<<' '<<idx<<endl;
                if(cmd == 1) ans = max(ans , bucket[idx].get_max());
                if(cmd == 2) bucket[idx].increment();
                if(cmd == 3) bucket[idx].increment_slope(V);
                if(cmd == 4) bucket[idx].increment_coef(V);
            }
            else{
                if(cmd == 1) ans = max(ans , bucket[idx].get_specified_max(st , en));
                if(cmd == 2) bucket[idx].specified_increment(st , en);
                if(cmd == 3) bucket[idx].specified_increment_slope(st , en , V);
                if(cmd == 4) bucket[idx].specified_increment_coef(st , en , V);
            }

        }

        if(cmd == 1) printf("%lld\n",ans);
    }
}