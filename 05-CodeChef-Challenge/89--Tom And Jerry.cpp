#include <cstring>
#include <cassert>
 
#include <iostream>
#include <queue>
#include <utility>
 
using namespace std;
 
#define FOR(i,a,n) for(int i=(a);i<(n);i++)
 
int M, N;
char B[64][64];
 
typedef pair<int, int> ip;
int dist[64][64];
int steps, min_dist;
 
int g[4] = {-1, 0, 0, 1},
    h[4] = {0, 1, -1, 0};
 
void build_dist() {
    memset(dist, -1, sizeof(int)*64*64);
    queue<ip> Q;
    FOR(i,0,M) FOR(j,0,N) if(B[i][j] == '0') {
        dist[i][j] = 0;
        Q.push(ip(i,j));
    }
    while(Q.size()) {
        ip T = Q.front();
        Q.pop();
        int i = T.first, j = T.second;
        FOR(k,0,4) {
            int ii = i+g[k], jj = j+h[k];
            if(ii < 0 || ii >= M || jj < 0 || jj >= N || dist[ii][jj] != -1) continue;
            if(B[ii][jj] == '#') continue;
            dist[ii][jj] = dist[i][j] + 1;
            Q.push(ip(ii,jj));
        }
    }
    FOR(i,0,M) FOR(j,0,N) if(B[i][j] == '*') min_dist = dist[i][j];
}
 
int ret[256][2];
 
void do_case() {
    steps = 0;
    do {
        min_dist = -1;
        build_dist();
        if(min_dist == 1) {
            break;
        }
        if(min_dist == -1) {
            break;
        }
        
        int placed = 0;
        FOR(i,0,M) FOR(j,0,N) if(!placed && B[i][j] == '*') {
            FOR(k,0,4) {
                int ii = i+g[k], jj = j+h[k];
                if(ii >= 0 && ii < M && jj >= 0 && jj < N && dist[ii][jj] == min_dist-1) {
                    assert(B[ii][jj] == '.');
                    B[ii][jj] = '#';
                    ret[steps][0] = ii;
                    ret[steps][1] = jj;
                    placed = 1;
                    break;
                }
            }
        }
        
        assert(placed);
        
        min_dist = -1;
        build_dist();
        if(min_dist == -1) continue;
        
        int moved = 0;
        FOR(i,0,M) FOR(j,0,N) if(!moved && B[i][j] == '*') {
            FOR(k,0,4) {
                int ii = i+g[k], jj = j+h[k];
                if(ii >= 0 && ii < M && jj >= 0 && jj < N && dist[ii][jj] == min_dist-1) {
                    assert(B[ii][jj] == '.');
                    B[ii][jj] = '*';
                    B[i][j] = '.';
                    moved = 1;
                    break;
                }
            }
        }
        
        assert(moved);
        
        steps++;
    } while(steps <= 200);
    if(min_dist != -1) {
        cout << 0 << endl;
    } else {
        cout << steps << endl;
        FOR(i,0,steps) cout << ret[i][0]+1 << " " << ret[i][1]+1 << endl;
    }
}
 
int main() {
    cin >> M >> N;
    FOR(i,0,M) cin >> B[i];
    do_case();
    return 0;
}
