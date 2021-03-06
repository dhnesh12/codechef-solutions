#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <assert.h>
 
using namespace std;
 
#define eps 1e-10
#define SZ(X)   (int)(X).size()
#define FOR(i, n)   for(int (i) = 0; (i) < (n); (i)++)
#define inf (1LL<<30)
#define PI acos(-1.0)
#define SQR(v)  (1LL*(v)*(v))
#define MP(x, y)  make_pair((x), (y))
#define maxn 50+5
#define int64 long long
 
char sa[200+5], sb[2000000+5], sc[200+5], s[1000+5], c[1000+5];
int na, nb, nc;
 
#define maxnode 2000000+5
const int MOD = 1000000007;
 
struct TNode
{
    struct TNode *child[2], *sufnode;
    int weight;
};
 
struct TNode *THead, heap[maxnode], *q[maxnode];
int heapsize;
 
void init()
{
    heapsize = 0;
    THead = &heap[heapsize++];
    THead->child[0] = THead->child[1] = NULL;
    THead->weight = 0;
    THead->sufnode = THead;
}
void AddWord(const string &s)
{
    struct TNode *now = THead, *Temp;
    for(unsigned i = 0; i < s.size(); i++) {
        Temp = now->child[s[i]-'0'];
        if(Temp == NULL)  {
            Temp = &heap[heapsize++];
            Temp->child[0] = Temp->child[1] = NULL;
            Temp->weight = (i+1)*(i+1);
            now->child[s[i]-'0'] = Temp;
        }
        now = now->child[s[i]-'0'];
    }
}
 
 
void buildGraph() {
    int inc = 0, sf = 0;
    q[sf++] = THead;
    struct TNode *now;
    while(inc < sf) {
        now = q[inc];
        now->weight = now->weight + now->sufnode->weight;
        if(now->weight >= MOD)   now->weight -= MOD;
        for(int k = 0; k < 2; k++) {
            if(now->child[k] != NULL) {
                q[sf++] = now->child[k];
            }
            if(now == THead) {
                if(now->child[k] == NULL)   now->child[k] = THead;
                else       now->child[k]->sufnode = THead;
                continue;
            }
            if(now->child[k] == NULL)   now->child[k] = now->sufnode->child[k];
            else   {
                now->child[k]->sufnode = now->sufnode->child[k];
            }
        }
        inc++;
    }
}
 
struct TNode* findChild(struct TNode *now, int k) {
    now = now->child[k];
    return ( now == NULL ?  THead : now );
}
string str(char ch) {
    int x = 0;
    if(ch >= 'a'&&ch <= 'z')   x = ch - 'a';
    else     x = ch - 'A' + 26;
    string s = "";
    for(int i = 4; i >= 0; i--)  {
        if(x&(1<<i))    s += "1";
        else    s += "0";
    }
    return s;
}
 
int main() {
    //freopen("A.txt", "r", stdin);
    string s1 = "", s2 = "";
    scanf("%s", sa);
    long long xx = clock();
    na = strlen(sa);
    for(int i = 0; i < na; i++)   s1 += str(sa[i]);
    scanf("%s", sb);
    nb = strlen(sb);
    scanf("%s", sc);
    nc = strlen(sc);
    for(int i = 0; i < nc; i++)  s2 += str(sc[i]);
    init();
  //  cout << sa << " " << sc << endl;
    AddWord(s1);
    for(unsigned i = 0; i < s2.size(); i++)  {
        if(s2[i] == '1') {
            s1[i] = '1' - s1[i] + '0';
            AddWord(s1);
            for(unsigned j = i+1; j < s2.size(); j++) {
                if(s2[j] == '1')  {
                    s1[j] = '1' - s1[j] + '0';
                    AddWord(s1);
                    s1[j] = '1' - s1[j] + '0';
                }
            }
            s1[i] = '1' - s1[i] + '0';
        }
    }
   // cout << heapsize << endl;
    buildGraph();
    int ans = 0;
    struct TNode *now = THead;
    string s = "";
    long long tt = clock();
    //cout << (tt - xx)/CLOCKS_PER_SEC << endl;
    for(int i = 0; i < nb; i++) {
        int tt = 0;
        if(sb[i] >= 'a'&&sb[i] <= 'z')  tt = sb[i] - 'a';
        else   tt = sb[i] - 'A' + 26;
        for(int j = 4; j >= 0; j--) {
            if((tt&(1<<j)))
                now = findChild(now, 1);
            else
                now = findChild(now, 0);
            ans = ans + now->weight;
            if(ans >= MOD)  ans -= MOD;
        }
    }
     //   cout << (clock()-tt)/CLOCKS_PER_SEC << endl;
    printf("%d\n", ans);
    return 0;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 