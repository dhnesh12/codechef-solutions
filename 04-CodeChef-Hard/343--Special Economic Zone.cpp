#include <iostream>
#include <list>
#include <queue>

#define maxN 10000
#define maxM 100000

#define mp make_pair
#define fi first
#define se second

using namespace std;

int n,m;
list<int> h[2][maxN];

int p[2][maxN];
int anc[maxN];
bool b[maxN];

queue< pair<int,int> > sor;
int num;

void process0() {
    while((!sor.empty()) && (sor.front().se == 0)) {
        int q = sor.front().fi;
        sor.pop();

        for(int i:h[0][q]) {
            if(anc[i] >= 0) continue;
            anc[i] = q;
            sor.push(mp(i,1));
        }
    }
}

bool process1() {
    bool ret = 0;
    while((!sor.empty()) && (sor.front().se == 1)) {
        int q = sor.front().fi;
        sor.pop();

        if(p[1][q] < 0) {
            ret = 1;
            continue;
        }

        sor.push(mp(p[1][q],0));
    }

    return ret;
}

bool add(bool t, int k) {

    if(t) {
        if(add(0,anc[k])) {
            p[1][k] = anc[k];
            p[0][anc[k]] = k;
            return 1;
        } else return 0;
    } else {
        if(b[k]) return 0;
        b[k] = 1;
        if(p[0][k] < 0) return 1;
        return add(1,p[0][k]);
    }
}

int main()
{
    ios::sync_with_stdio(0);

    cin >> n >> m;
    for(int i=0; i<m; i++) {
        int x,y;
        cin >> x >> y;
        x--; y--;
        h[0][x].push_back(y);
        h[1][y].push_back(x);
        h[1][x].push_back(y);
        h[0][y].push_back(x);
    }

    for(int i=0; i<n; i++) {
        p[0][i] = p[1][i] = -1;
    }

    int sol = 0;
    do {
        for(int i=0; i<n; i++) {
            anc[i] = -1;
            b[i] = 0;
            if(p[0][i] < 0) sor.push(mp(i,0));
        }

        while(!sor.empty()) {
            process0();
            if(process1()) break;
        }
        while(!sor.empty()) sor.pop();

        num = 0;
        for(int i=0; i<n; i++) {
            if((anc[i] >= 0) && (p[1][i] < 0)) {
                num += add(1,i);
            }
        }
        sol += num;
    } while(num);

    cout << n-sol << endl;
}
