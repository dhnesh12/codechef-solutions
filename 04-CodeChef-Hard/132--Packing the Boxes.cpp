#include <vector>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <sstream>
using namespace std;
#define GI ({int t; scanf("%d", &t); t;})
#define LET(x,a) __typeof(a) x(a)
#define FOR(i,a,b) for(LET(i,a);i!=(b);++i)
#define EACH(it,v) FOR(it, v.begin(), v.end())
#define REP(i,n) FOR(i,0,n)
#define pb push_back
#define mkp make_pair
#define INF (int)1e8
#define MAX 2002
#define sz size()
typedef long long LL;
typedef double D;
typedef vector<int> VI;
#define  dbg(a) ({cout<<#a<<" -> "<< a <<" ";;})
#define  dbge(a) ({cout<<#a<<" -> "<< a <<"\n";;})
#define DEBUG 0

const int mlen=20000;
char buf[mlen],*pp;
int parse,sgn,aaa;
#define nextInt() ({	\
	sgn=0;\
	while ( *pp && *pp <= ' ') ++pp;	\
	if ( !*pp ) fread(buf, 1, mlen , stdin),pp=buf;	\
	parse = 0;	\
	while (*pp > ' ') {	\
		if (*pp == '-' ) sgn=1,pp++;\
		else parse = parse*10+(*(pp++)&15);	\
		if ( !*pp ) fread(buf, 1, mlen , stdin), pp=buf;	\
	}	\
	parse*=(sgn?-1:1);	\
})

#define HEAPMAX 1000000
LL heap[HEAPMAX], copy_heap[HEAPMAX];
int heap_size;
inline void insert(LL val) {
   heap[heap_size++] = val;
   // Bubble up
   LL tmp;
   int child=heap_size-1, par = (child-1)/2;
   int left = 2*par, right = 2*par+1;
   while(par >= 0 && heap[child] < heap[par]) {
      tmp = heap[child], heap[child] = heap[par], heap[par] = tmp;
      child = par, par = (child-1)/2;
   }
}
inline LL extract_min() {
   if(heap_size == 0) return -1;
   else if(heap_size == 1) {      
      return heap[--heap_size];
   }
   LL root = heap[0], tmp;
   heap[0] = heap[--heap_size];
   // Bubble down
   int par = 0, child;
   int left = 2*par+1, right = 2*par+2;
   while(par < heap_size && (left < heap_size && heap[left] < heap[par] || right < heap_size && heap[right] < heap[par])) {
      if(left >= heap_size) child = right; 
      else if(right >= heap_size) child = left;
      else if(heap[left] < heap[right]) child = left;
      else child = right;      
      tmp = heap[child], heap[child] = heap[par], heap[par] = tmp;
      par = child;
      left = 2*par+1, right = 2*par+2;
   }
   return root;
}

int n, a[MAX], K;
LL nCr[MAX][MAX], fun[2*MAX], MOD = 1000000000LL, best[MAX][MAX], sum;
int subsum[MAX], left_sum[MAX], seen[MAX][MAX], mem[MAX][MAX];
int enter[MAX][MAX];
int go(int index, int pairs) {
   if(index >= 0 && pairs >= 0)
    enter[index][pairs] = 1;
    if(index >= 0 && sum == subsum[index] && 2*pairs >= index+1) return fun[2*pairs];
    else if(index < 0 || 2*pairs >= index+1 || pairs <= 0 || pairs <= n && sum != best[index][pairs]) return 0;
    if(seen[index][pairs]) return mem[index][pairs];
    seen[index][pairs] = 1;
    sum -= subsum[index];
    
    int &res = mem[index][pairs] = go(index, 2*pairs);

    int used=1, beg=index;
    for(int i = 1, j = index; i <= 2*pairs && j >= 0; i++,j--) {  
        if(j<index && a[j] == a[j+1]) used++;
        else used=1, beg=j;   
        int cand = (nCr[left_sum[beg]][used] * go(j-1, 2*pairs - i)) % MOD;
        res = (cand + res) % MOD;
    }
    res = (fun[2*pairs] * res) % MOD;
/*   
    if(!res) {
      dbg(index); dbg(pairs); dbg(sum+subsum[index]); dbge(best[index][pairs]);
    }
*/
    sum += subsum[index];
    return res;
}
LL calc_fun(int n) {
    if(fun[n] != -1) return fun[n];
    if(n == 2) return fun[n] = 1LL;
    else if(n < 2) return fun[n] = 0LL;    
    return fun[n] = (calc_fun(n-2) * (n-1)) % MOD;
} 
void init() {
    FOR(i,1,MAX) nCr[i][0] = nCr[i][i] = 1LL;
    FOR(i,2,MAX) FOR(j,1,i) nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % MOD;
    REP(i,MAX) REP(j,MAX) if(!nCr[i][j]) nCr[i][j] = 1LL;
    memset(fun,-1,sizeof(fun));
    REP(i,2*MAX) fun[i] = calc_fun(i);
}
int main() {
    init();
	 fread(buf, 1, mlen, stdin);	
	 pp=buf;    
    n = nextInt();
    REP(i,n) a[i] = nextInt();
    sort(a,a+n);
    REP(i,n) {
        left_sum[i] = 1, subsum[i] = a[i];
        if(i && a[i-1] == a[i]) left_sum[i] += left_sum[i-1];
        if(i) subsum[i] += subsum[i-1];
    }
    int copied=0, copy_heap_size;
    LL copy_tmp, tmp, copy_f;
    FOR(cnt,1,n+1) { 
       tmp = 0LL;
       heap_size = 0;
       if(copied) {
          heap_size = copy_heap_size;
          REP(i, heap_size) heap[i] = copy_heap[i];
          insert(a[cnt-1]);
          if(copy_f) insert(copy_f);
          tmp += copy_tmp;
       }
       else {
          REP(i,cnt) insert(a[i]);
       }
       copied=copy_f=0;
       
       while(heap_size) {
           best[cnt-1][heap_size] = tmp;
           if(!copied && cnt < n && heap[0] >= a[cnt]) {            
               copied = 1;
               REP(j,heap_size) copy_heap[j] = heap[j];
               copy_heap_size = heap_size;
               copy_tmp = tmp;
           }                          
           LL f = extract_min(), g;
           if(heap_size) {
              if(!copied && cnt < n && heap[0] >= a[cnt]) {
                  copied = 1;
                  REP(j,heap_size) copy_heap[j] = heap[j];
                  copy_heap_size = heap_size;
                  copy_tmp = tmp;
                  copy_f = f;
              } 
               g = extract_min();
               tmp += f+g;
               insert(f+g);
           }
       }
    }
    /*
REP(i,n) {
   REP(j,i+1) { cout << best[i][j] <<"  "; }
   cout << endl;   
}
*/

    sum = best[n-1][1];
    printf("%Ld %d\n", sum, go(n-1, 1));
 
}