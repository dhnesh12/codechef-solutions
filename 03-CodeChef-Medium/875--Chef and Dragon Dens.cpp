#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define fin std::cin
#define fout std::cout

#define maxn 200005

// std::ifstream fin("input.txt");
// std::ofstream fout("output.txt");

int n, Q;
long long height[maxn];
long long beauty[maxn];

void readInput(){
    fin >> n >> Q;
    for(int i=1; i<=n; i++)
        fin >> height[i];
    for(int i=1; i<=n; i++)
        fin >> beauty[i];
    height[0] = height[n+1] = 1e10;
}

class SegmentTree{
    int size = 2*maxn;
    long long sum[8*maxn] = {};

    public:
        SegmentTree(){};

        void update(int pos, int val, int node=0, int left=0, int right=2*maxn){
            if(left > pos or right < pos) return;
            if(left == right){
                sum[node] = val;
                return;
            }
            int mid = (left + right) / 2;
            update(pos, val, 2*node+1, left, mid);
            update(pos, val, 2*node+2, mid+1, right);

            sum[node] = sum[2*node+1] + sum[2*node+2];
        }

        long long query(int l, int r, int node=0, int left=0, int right=2*maxn){
            if(left > r or right < l) return 0;
            if(l <= left and right <= r) return sum[node];

            int mid = (left + right) / 2;
            return query(l, r, 2*node+1, left, mid) + query(l, r, 2*node+2, mid+1, right);
        }
};

SegmentTree sumLeft;
std::vector <int> edgeLeft[maxn];
int nextLeft[maxn];
bool vLeft[maxn];
int inLeft[maxn], outLeft[maxn];
int timeLeft;

void dfsLeft(int node){
    inLeft[node] = timeLeft ++;
    vLeft[node] = true;
    for(int next: edgeLeft[node]){
        if(vLeft[next] == false)
            dfsLeft(next);
    }
    outLeft[node] = timeLeft ++;
}

void buildLeftTree(){
    std::stack <int> stack;
    stack.push(0);
    for(int i=1; i<=n; i++){
        while(height[stack.top()] <= height[i])
            stack.pop();

        edgeLeft[stack.top()].push_back(i);
        stack.push(i);
    }

    dfsLeft(0);
    for(int i=0; i<=n; i++){
        sumLeft.update(inLeft[i], beauty[i]);
        sumLeft.update(outLeft[i], -beauty[i]);
    }
}

SegmentTree sumRight;
std::vector <int> edgeRight[maxn];
int nextRight[maxn];
bool vRight[maxn];
int inRight[maxn], outRight[maxn];
int timeRight;

void dfsRight(int node){
    inRight[node] = timeRight ++;
    vRight[node] = true;
    for(int next: edgeRight[node]){
        if(vRight[next] == false)
            dfsRight(next);
    }
    outRight[node] = timeRight ++;
}

void buildRightTree(){
    std::stack <int> stack;
    stack.push(0);
    for(int i=n; i>=1; i--){
        while(height[stack.top()] <= height[i])
            stack.pop();

        edgeRight[stack.top()].push_back(i);
        stack.push(i);
    }

    dfsRight(0);
    for(int i=0; i<=n; i++){
        sumRight.update(inRight[i], beauty[i]);
        sumRight.update(outRight[i], -beauty[i]);
    }
}

void solveQueries(){
    int type, a, b;

    // for(int i=0; i<=n; i++)
    //     fout << inLeft[i] << ' ' << outLeft[i] << '\n';

    while(Q --){
        fin >> type >> a >> b;
        if(type == 1){
            sumLeft.update(inLeft[a], b);
            sumLeft.update(outLeft[a], -b);
            sumRight.update(inRight[a], b);
            sumRight.update(outRight[a], -b);
        }
        else{
            if(a < b){
                if(inLeft[a] <= inLeft[b] and outLeft[b] <= outLeft[a])
                    fout << sumLeft.query(inLeft[a], outLeft[b]-1) << '\n';
                else fout << "-1\n";
            }
            else{
                if(inRight[a] <= inRight[b] and outRight[b] <= outRight[a])
                    fout << sumRight.query(inRight[a], outRight[b]-1) << '\n';
                else fout << "-1\n";
            }
        }
    }

};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    readInput();
    buildLeftTree();
    buildRightTree();
    solveQueries();

    return 0;
}