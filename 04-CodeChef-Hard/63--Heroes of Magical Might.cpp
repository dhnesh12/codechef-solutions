#include<vector>
#include<cstring>
#include<cstdio>
#include<queue>
#define F first
#define S second
#define M 20
#define INF 1e5
#define DELTA 1e-6
using namespace std;
inline void I(int &a)
{
    register int c;
    a=0;
    do c=getchar_unlocked(); while(c<'0');
    do
    {
        a=(a<<1)+(a<<3)+c-'0';
        c=getchar_unlocked();
    }while(c >= '0');
}
int main(){
    int T;
    int d[4][2] = {0,1, 0,-1, 1,0, -1,0};
    I(T);
    int m, n, i, j, k, sx, sy;
    double p;
    char map[M+2][M+2];
    vector<pair<int,int> > gate;
    int gsize;
    double step[M+2][M+2];
    pair<int,int> now;
    bool inque[M+2][M+2], self;
    vector<pair<int,int> > work;
    int wsize;
    double check, exp, stay;
    bool change;
    while(T--){
        work.clear();
        gate.clear();
        queue<pair<int,int> > list;
        memset(inque, 0, sizeof(inque));
        pair<int,int> loc;
        I(m); I(n);scanf("\n");
        for(i=0; i<=n+1; i++)
            map[0][i] = map[m+1][i] = '#';
        for(i=0; i<=m+1; i++)
            map[i][0] = map[i][n+1] = '#';
        for(i=1; i<=m; i++){
            for(j=1; j<=n; j++){
                scanf("%c", &map[i][j]);
                step[i][j] = INF;
                if(map[i][j] == 'S'){
                    sx = i;
                    sy = j;
                }
                else if(map[i][j] == '@')
                    gate.push_back (make_pair(i,j));
                else if(map[i][j] == '*'){
                    step[i][j] = 0.0;
                    list.push (make_pair(i,j));
                    inque[i][j] = 1;
                }
            }
            scanf("\n");
        }
        scanf("%lf", &p);
        gsize = gate.size();
        while(!list.empty()){
            loc = list.front();
            list.pop();
            for(i=0; i<4; i++){
                if(inque[loc.F+d[i][0]][loc.S+d[i][1]] || map[loc.F+d[i][0]][loc.S+d[i][1]] == '#')continue;
                list.push ( make_pair (loc.F+d[i][0], loc.S+d[i][1]) );
                work.push_back ( make_pair (loc.F+d[i][0], loc.S+d[i][1]) );
                inque[loc.F+d[i][0]][loc.S+d[i][1]] = 1;
            }
            if(map[loc.F][loc.S] == '@'){
                for(i=0; i<gsize; i++){
                    if(inque[gate[i].F][gate[i].S])
                        continue;
                    list.push ( make_pair(gate[i].F,gate[i].S) );
                    work.push_back ( make_pair(gate[i].F,gate[i].S) );
                    inque[gate[i].F][gate[i].S] = 1;
                }
            }
        }
        wsize = work.size();
        do{
            change = 0;
            for(k=0; k<wsize; k++){
                now = work[k];
                    check = INF;
                    for(i=0; i<4; i++){
                        exp = stay = 0.0;
                        for(j=0; j<4; j++){
                            if(j == i){
                                if(map[now.F+d[j][0]][now.S+d[j][1]] == '#')
                                    stay += p;
                                else
                                    exp += step[now.F+d[j][0]][now.S+d[j][1]] * p;
                            }
                            else{
                                if(map[now.F+d[j][0]][now.S+d[j][1]] == '#')
                                    stay += (1-p)/3;
                                else
                                    exp += step[now.F+d[j][0]][now.S+d[j][1]] * (1-p)/3;
                            }
                        }
                        exp += 1.0;
                        if(stay < 1.0 - DELTA)
                            exp /= (1-stay);
                        else
                            exp = INF;
                        if(check > exp + DELTA)
                            check = exp;
                    }
                if(map[now.F][now.S] == '@'){
                    exp = 0.0;
                    for(i=0; i<gsize; i++){
                        if(gate[i].F==now.F && gate[i].S==now.S)
                            continue;
                        exp += step[gate[i].F][gate[i].S];
                    }
                    exp /= (gsize-1);
                    exp += 1.0;
                    if(check > exp + DELTA)
                        check = exp;
                }
                if(check < step[now.F][now.S] - DELTA){
                    step[now.F][now.S] = check;
                    change = 1;
                }
            }
        }while(change);   
        printf("%.2lf\n", step[sx][sy]);
    }
}  