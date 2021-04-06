#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#include <cstring>
 
using namespace std;
const int N=51200;
 
typedef struct{
    int id, index;
    int x1, y1, x2, y2;
}rect;
 
class coord{
public:
    int y, index, top;
    bool operator <(const coord&c) const{return y<c.y;}
	
};
 
int n;
int parent[N];
vector<rect> input;
set<coord> bst;
 
bool cmp(rect r1, rect r2){
    int i, j;
    if(r1.id == 0)
        i = r1.x1;
    else
        i = r1.x2;
    if(r2.id == 0)
        j = r2.x1;
    else
        j = r2.x2;
    return (i<j);
}
 
vector<int> g[N], base;
 
void buildGraph()
{
	base.clear();
	for(int i = 0; i < n; i++) g[i].clear();
	for(int i = 0; i < n; i++) {
		if(parent[i] == -1) base.push_back(i);
		else g[parent[i]].push_back(i);
	}
}
 
int sg[N];
 
int getSG(int v)
{
	if(sg[v] != -1) return sg[v];
	if(g[v].size() == 0) return sg[v] = 1;
	sg[v] = 0;
	for(int i = 0; i < g[v].size(); i++) sg[v] ^= getSG(g[v][i]);
	return sg[v] = sg[v]+1;
}
 
int getSGSum()
{
	memset(sg, -1, sizeof(sg));
	int sum = 0;
	for(int i = 0; i < base.size(); i++) sum ^= getSG(base[i]);
	return sum;
}
 
bool canMove[N];
 
void markIt(int v, int needXor)
{
	if(needXor == 0) { canMove[v] = true; return; }
	if(g[v].size() == 0) return;
	// children Xor
	int chXor = 0;
	for(int i = 0; i < g[v].size(); i++) chXor ^= sg[g[v][i]];
	for(int i = 0; i < g[v].size(); i++) markIt(g[v][i], (needXor-1) ^ chXor ^ sg[g[v][i]]);
}
 
void getMarks()
{
	memset(canMove, false, sizeof(canMove));
	int xorSum = 0;
	for(int i = 0; i < base.size(); i++) xorSum ^= sg[base[i]];
	for(int i = 0; i < base.size(); i++) markIt(base[i], xorSum ^ sg[base[i]]);
}
 
int main(){
    int t;
    cin>>t;
    int c1;
    for(int run=0; run<t; run++){
        cin>>n;
 
        rect r;
	input.clear();
        for(int i=0; i<n; i++){
            cin>>r.x1>>r.y1>>c1;
            r.x2 = c1+r.x1;
            r.y2 = c1+r.y1;
            r.index = i;
            r.id = 0;
            //rectangle.push_back(r);
            input.push_back(r);
            r.id = 1;
            input.push_back(r);
        }
        sort(input.begin(),input.end(),cmp);
        
        coord c;
	bst.clear();
        vector<rect>::iterator it;
        set<coord>:: iterator st;
        memset(parent, -1, sizeof(parent));
        for(it=input.begin(); it!=input.end(); ++it){
            //cout<<it->x1<<" "<<it->y1<<" "<<it->id<<"sort\n";
            c.index = it->index;
            if(it->id == 0){
                c.y = it->y2; c.top = 1;
                bst.insert(c);
                c.y = it->y1; c.top = 0;
                bst.insert(c);
		st = bst.lower_bound(c);
		
		
                if(st != bst.begin()){
                    
                    --st;
                    if(st->top == 0){
                        parent[c.index] = st->index;
                    }
                    else{
                        parent[c.index] = parent[st->index];
                    }
                }
            }
            else{
                c.y = it->y2; c.top = 1;
                bst.erase(c);
                c.y = it->y1; c.top = 0;
                bst.erase(c);
            }
        }
	
	
        buildGraph();
        int xorSum = getSGSum();
        printf("%s", xorSum == 0 ? "Fit" : "Fat");
        if(xorSum == 0) { printf("\n"); continue; }
        getMarks();
        int lo = -1;
        for(int i = 0; i < n; i++) if(canMove[i]) { lo = i; break; }
        printf(" %d\n", lo+1);
    }
    return 0;
} 