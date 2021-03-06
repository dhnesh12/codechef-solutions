#ifndef PROGRAMMING_CONTESTS_H
#define PROGRAMMING_CONTESTS_H
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <typeinfo>
#include <utility>
#include <vector>
#ifdef LOCAL
static FILE* _freopen = freopen("input.txt", "r", stdin);
#else
#define NDEBUG
#endif
using namespace std;
using namespace std::tr1;
 
 
 
 
 
 
 
typedef long long LL;
 
#define RI(x) {int _res=scanf("%i ", &(x)); assert(_res);}
#define RLL(x) {int _res=scanf("%lli ", &(x)); assert(_res);}
#define RS(x) {char _buf[2000]; int _res=scanf("%s ", _buf); assert(_res); x = string(_buf);}
#define RL(x) getline(cin, x); assert(cin.good()); //Expects and discards line break at end of line.
#define FIN(path) freopen(path, "r", stdin)
#define FOUT(path) freopen(path, "w", stdout)
 
#define FOR(i, a, b) for(int i=(a), _b=(b); i<_b; ++i)
#define FORR(i, a, b) for(int i=(b-1), _a=(a); i>=_a; --i)
#define IT(c) typeof(c.begin())
#define FORE(it, c) for(IT(c) it=c.begin(); it!=c.end(); ++it)
#define ALL(x) x.begin(), x.end()
 
#define PB push_back
#define MP make_pair
#define SZ(c) ((int)c.size())
#define LEN(a) (sizeof(a)/sizeof(a[0]))
#define END(a) (a+LEN(a))
 
#define TWO(e) (1<<e)
#define TWOL(e) (1LL<<e)
 
 
static const double PI = acos(-1.0);
static const double GOLD = (1+sqrt(5.0))/2;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
template<typename T> inline T sqr(const T& x){return x*x;}
template<typename T> inline double eucDist(const T& x0, const T& y0, const T& x1, const T& y1){return sqrt(sqr(x0-x1)+sqr(y0-y1));}
template<typename T> inline T manDist(const T& x0, const T& y0, const T& x1, const T& y1){return abs(x0-x1)+abs(y0-y1);}
 
 
// Requires that type of v is the type that a contains.
template <typename A, typename V>
static void fillArray(A &a, const V &v) {
  fill_n((V*)a, sizeof(a)/sizeof(V), v);
}
 
// Returns true iff a is less than b according to a pairwise element comparison.
template<typename T, size_t N>
static bool aLT(T (&a)[N], T (&b)[N]) {
  for(int i=0;i<N;++i) {
    if(a[i]<b[i]) return true;
    if(a[i]>b[i]) return false;
  }
  return false;
}
 
// Pieces which are the empty string are dropped.
static void split(const string &s, vector<string> &pieces, const string &delim = " ") {
  unsigned int nextI = 0;
    for(unsigned int cutAt = s.find(delim,nextI); cutAt != s.npos; cutAt = s.find(delim,nextI)) {
         if(cutAt > nextI) pieces.push_back(s.substr(nextI,cutAt-nextI));
         nextI = cutAt+delim.length();
    }
    if(nextI < s.length()) {
         pieces.push_back(s.substr(nextI));
  }
}
 
static void toLower(string& s) {
  transform(s.begin(), s.end(), s.begin(), (int (*)(int))tolower);
}
static void toUpper(string& s) {
  transform(s.begin(), s.end(), s.begin(), (int (*)(int))toupper);  
}
 
static bool isLetter(const char& c) {
  char d = tolower(c);
  return d >= 'a' && d <= 'z';
}
static bool isVowel(const char& c) {
  char d = tolower(c);
  return d=='a'||d=='e'||d=='i'||d=='o'||d=='u'||d=='y';
}
static bool isConsonant(const char& c) {
  return isLetter(c) && !isVowel(c);
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
// Stuff for debugging.
 
static void sleep(const int ms) {
    clock_t goal = ms + clock();
    while (goal > clock());
}
 
template<typename T>
static void print(T x) {
  cerr << x << endl;
}
 
template<typename T>
static void print(T first, const T &last) {
  while(first != last) cerr << *(first++) << " ";
  cerr << endl;
}
 
template<typename T, size_t LENGTH>
static void print(const T (&a)[LENGTH]) {
  print(a,a+LENGTH);
}
 
template<typename T, size_t LENGTH0, size_t LENGTH1>
static void print(const T (&a)[LENGTH0][LENGTH1]) {
  for(int i = 0; i < LENGTH0; ++i) {
    print(a[i]);
  }
}
 
static double timer() {
  return 1.0*clock()/CLOCKS_PER_SEC;
}
 
#endif // PROGRAMMING_CONTESTS_H
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
template<typename T>
static inline bool is1(const T& x, const int& i) {
  assert(i >= 0); assert(i < 8*sizeof(T));
  return (x & (1 << i)) != 0;
}
 
template<typename T>
static inline void set1(T& x, const int& i) {
  assert(i >= 0); assert(i < 8*sizeof(T));
  x |= (1 << i);
}
 
 
 
 
const int maxT = 100000;
 
int T,M,N,C,K;
int mapp[32];
int tr,tc;
int chef[maxT][32];
int ghosts[maxT][32];
 
int gr[32];
int gc[32];
int way[32]; //index of next waypoint for ghosts
int L[33];
int wayr[33][12];
int wayc[33][12];
 
 
 
int main() {
  RI(T);
  FOR(test,0,T) {    
 
    memset(chef,0,sizeof(chef));
    memset(ghosts,0,sizeof(ghosts));
    memset(mapp,0,sizeof(mapp));
    
    scanf("%i %i %i %i ",&M,&N,&C,&K);
    FOR(i,0,C) {
      RI(L[i]);
      FOR(j,0,L[i]) {
        scanf("%i %i ", &wayc[i][j], &wayr[i][j]);
      }
      gr[i] = wayr[i][0];
      gc[i] = wayc[i][0];
      set1(ghosts[0][gr[i]],gc[i]);
      way[i] = 1;
    }
    FOR(i,0,M) {
      string line; RS(line);
      FOR(j,0,N) {
        if(line[j]=='@') set1(chef[0][i],j);
        if(line[j]=='#') set1(mapp[i],j);
        if(line[j]=='$') {
          tr=i;tc=j;
        }
      }
    }
  
  
    bool done = false;
    FOR(t,1,min(maxT,K+1)) {
      if(done) break;
            
      //compute ghosts loc at time t
      FOR(i,0,C) {
        //reached waypoint
        if(gr[i]==wayr[i][way[i]]&&gc[i]==wayc[i][way[i]]) {
          if(way[i]==L[i]-1)way[i]=0;
          else ++way[i];
        }
        
        //move        
        if(gr[i]<wayr[i][way[i]])++gr[i];
        else if(gr[i]>wayr[i][way[i]])--gr[i];
        else if(gc[i]<wayc[i][way[i]])++gc[i];
        else if(gc[i]>wayc[i][way[i]])--gc[i];
        
        set1(ghosts[t][gr[i]],gc[i]);
      }
      
      
      
      FOR(r,0,M) {
        chef[t][r] |= chef[t-1][r];
        if(r+1<M) chef[t][r] |= chef[t-1][r+1];
        if(r-1>=0) chef[t][r] |= chef[t-1][r-1];
        chef[t][r] |= (chef[t-1][r] >> 1);
        chef[t][r] |= (chef[t-1][r] << 1)&((1<<N)-1);
        chef[t][r] &= ~mapp[r];
        chef[t][r] &= ~ghosts[t][r];
        chef[t][r] &= ~ghosts[t-1][r];               
      }
      
      if(is1(chef[t][tr],tc)) {
        done = true;
        printf("%i\n",t);
      }
      
    }
    if(!done) printf("%i\n",-1);    
  }
    
  return 0;
}
 
