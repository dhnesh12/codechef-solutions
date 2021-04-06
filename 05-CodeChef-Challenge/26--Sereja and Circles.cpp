#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 400;
 
const int DX[] = {-1, 1, 0, 0, -1, 1, -1, 1};
const int DY[] = {0, 0, -1, 1, -1, 1, 1, -1};
 
bool R = 1;
 
inline int sqr(int x) { return x*x; }
 
int n, s, skip, placed, u, d, moves;
int r[N], x[N], y[N], radius[N], eat[N];
bool p[N];


const double X = 1e9;
const int MAX_S = 5000;

int mx_;
double _sqrt[2*MAX_S*MAX_S+1];

void init(int s) {
    s = min(s, MAX_S);
    mx_ = 2*s*s;
    for (int dx = 1, dx2 = 1; dx <= s; dx2 += dx++<<1|1)
        for (int dy = dx, sqr = 2*dx2; dy <= s; sqr += dy++<<1|1)
            _sqrt[sqr] = sqrt(sqr);
}

double get(int dx, int dy) {
    int sqr = dx*dx+dy*dy;
    if (sqr > mx_)
        return X;
    if (_sqrt[sqr] < 1)
        _sqrt[sqr] = sqrt(sqr);
    return _sqrt[sqr];
}

void place(int turn, int thisRadius)
{
    int minDelta = INT_MAX; 
    int bestIndex = -1;
 
    for (int i = placed; i < moves; ++i)
    {
        int delta = abs(thisRadius - radius[i]);
        if (delta < minDelta)
            minDelta = delta, bestIndex = i;
    }
 
    swap(radius[bestIndex], radius[placed]);
    radius[placed] = thisRadius;
    swap(x[bestIndex], x[placed]);
    swap(y[bestIndex], y[placed]);
 
    x[placed] = min(s-thisRadius, max(thisRadius, x[placed]));
    y[placed] = min(s-thisRadius, max(thisRadius, y[placed]));
 
    /*
    int i = placed;
    int ri = radius[i];
 
    double man = 1e9;
 
    for (int j = 0; j < moves; ++j)
        if (i != j)
            man = min(man, hypot(x[i] - x[j], y[i] - y[j]) - radius[j] - ri);
 
    bool go = true;
    for (int it = 0; it < 23 && go; ++it)
    {
        go = false;
        for (int st = 1<<2; st; st >>= 1)
            for (int d = 0; d < 4; ++d)
            {
                int cx = x[i]+st*DX[d];
                int cy = y[i]+st*DY[d];
 
                if (cx < ri || cy < ri || cx > s-ri || cy > s-ri)
                    continue;
 
                double ma = 1e9;
 
                for (int j = 0; j < n-skip; ++j)
                    if (j != i)
                        ma = min(ma, hypot(cx - x[j], cy - y[j]) - radius[j] - ri);
 
                if (man < ma)
                    go = true, man = ma, x[i] = cx, y[i] = cy;
            }
    }
    */
 
    if (rand()%107 == 0)
    for (int it = 0; it < 3; ++it)
    {
        for (int i = placed; i < moves; ++i)
        {
            int ri = radius[i];
            int w = s - 2*ri;
 
            double man = 1e9;
 
            for (int j = 0; j < moves; ++j)
                if (i != j)
                    man = min(man, get(x[i] - x[j], y[i] - y[j]) - radius[j] - ri);
 
            for (int t = 0; t < 7; ++t)
            {
                int cx = ri + rand()%w;
                int cy = ri + rand()%w;
 
                double ma = 1e9;
 
                for (int j = 0; j < moves; ++j)
                    if (j != i)
                        ma = min(ma, get(cx - x[j], cy - y[j]) - radius[j] - ri);
 
                if (man < ma)
                    man = ma, x[i] = cx, y[i] = cy;
            }
 
            bool go = true;
            for (int it = 0; it < 4 && go; ++it)
            {
                go = false;
                for (int st = 1<<3; st; st >>= 1)
                    for (int d = 0; d < 4; ++d)
                    {
                        int cx = x[i]+st*DX[d];
                        int cy = y[i]+st*DY[d];
 
                        if (cx < ri || cy < ri || cx > s-ri || cy > s-ri)
                            continue;
 
                        double ma = 1e9;
 
                        for (int j = 0; j < moves; ++j)
                            if (j != i)
                                ma = min(ma, get(cx - x[j], cy - y[j]) - radius[j] - ri);
 
                        if (man < ma)
                            go = true, man = ma, x[i] = cx, y[i] = cy;
                    }
            }
        }
    }
}
 
void show(int x, int y)
{
    if (R)
        printf("%d %d\n", x, y);
}
 
void play()
{
    placed = 0;
    memset(p, 0, sizeof p);
    
    for (int turn = 0; turn < n; ++turn)
    {
        int ri = eat[turn];
        if (R)
            scanf("%d", &ri);
 
        if (turn+skip == n)
        {
            --skip;
            show(-1, -1);
        }
        else 
        {
            bool skipped = false;
            if (skip > 0)
                for (int j = u; j < n<<1; ++j)
                    if (!p[j] && r[j] == ri)
                    {
                        show(-1, -1);
                        p[j] = true;
                        skipped = true;
                        --skip;
                        break;
                    }
            if (!skipped)
            {
                place(turn, ri);
                show(x[placed], y[placed]);
                ++placed;
            }
        }
 
        fflush(stdout);
    }   
}
 
int main()
{
//    freopen("input.txt", "r", stdin);
    
    n = 200;
    s = 50000;
    skip = 50;
    if (R)
        scanf("%d %d %d", &n, &s, &skip);
    memset(_sqrt, 0, sizeof _sqrt);
    //init(s);
    for (int i = 0; i < n<<1; ++i)
    {
        r[i] = rand()%100+1;
        if (R)
            scanf("%d", r+i);
    }
 
    moves = n-skip;
    for (int i = 0; i < n; ++i)
        eat[i] = r[i];
 
    int maxR = 1;
    for (int i = 0; i < n<<1; ++i)
        maxR = max(maxR, r[i]);
 
    int n0 = 1, n1;
    do
    {
        n1 = (n0-1)/sqrt(3);
        if (2*n0*n1 - n0 - n1 + 1 >= n-skip)
            break;
        ++n0;
    }
    while (true);
 
    int d = (s-2*maxR)/(n0-1);
    int hd = 0.5*(s-2*maxR)/(n0-1);
    int h = sqrt(3)*(s-2*maxR)/(n0-1);
    int d2 = 0.5*sqrt(3)*(s-2*maxR)/(n0-1);
 
    int k = 2*n0*n1 - n0 - n1 + 1;
 
    vector<int> x0, y0;
 
    int cx = maxR;
    for (int i = 0; i < n1; ++i)
    {
        int cy = maxR;
        for (int j = 0; j < n0; ++j)
        {
            x0.push_back(cx);
            y0.push_back(cy);
            cy += d;
        }
        cx += h;
    }
 
    cx = maxR+d2;
    for (int i = 0; i < n1-1; ++i)
    {
        cx += h;
        int cy = maxR+hd;
        for (int j = 0; j < n0-1; ++j)
        {
            x0.push_back(cx);
            y0.push_back(cy);
            cy += d;
        }
    }
 
    d = n;
    u = (n<<1)-skip;
 
    sort(r, r+(n<<1));
 
    for (int i = d; i < u; ++i)
        radius[i-d] = r[i];
 
    random_shuffle(radius, radius+n-skip);
 
    for (int i = 0; i < n-skip; ++i)
        x[i] = x0[i], y[i] = y0[i];
 
    for (int i = 0; i < n-skip; ++i)
    {
        int ri = radius[i];
        int w = s - 2*ri;
 
        int maxDist = INT_MIN, bx, by;
        
        for (int t = 0; t < 111; ++t)
        {
            int cx = ri + rand()%w;
            int cy = ri + rand()%w;
 
            double ma = 1e9;
            for (int j = 0; j < i; ++j)
                ma = min(ma, get(cx - x[j], cy - y[j]) - radius[j] - ri);
 
            if (maxDist < ma)
                maxDist = ma, bx = cx, by = cy;
        }
        x[i] = bx;
        y[i] = by;
    }
 
    for (int it = 0; it < 400; ++it)
    {        
        for (int i = 0; i < n-skip; ++i)
        {
            int ri = radius[i];
            int w = s - 2*ri;
 
            double man = 1e9;
 
            for (int j = 0; j < n-skip; ++j)
                if (i != j)
                    man = min(man, get(x[i] - x[j], y[i] - y[j]) - radius[j] - ri);
 
            for (int t = 0; t < 1; ++t)
            {
                int cx = ri + rand()%w;
                int cy = ri + rand()%w;
 
                double ma = 1e9;
 
                for (int j = 0; j < n-skip; ++j)
                    if (j != i)
                        ma = min(ma, get(cx - x[j], cy - y[j]) - radius[j] - ri);
 
                if (man < ma)
                    man = ma, x[i] = cx, y[i] = cy;
            }
 
            bool go = true;
            for (int it = 0; it < 10 && go; ++it)
            {
                go = false;
                for (int st = 1<<2; st; st >>= 1)
                    for (int d = 0; d < 4; ++d)
                    {
                        int cx = x[i] + st*DX[d];
                        int cy = y[i] + st*DY[d];
 
                        if (cx < ri || cy < ri || cx > s-ri || cy > s-ri)
                            continue;
 
                        double ma = 1e9;
 
                        for (int j = 0; j < n-skip; ++j)
                            if (j != i)
                                ma = min(ma, get(cx - x[j], cy - y[j]) - radius[j] - ri);
 
                        if (man < ma)
                            go = true, man = ma, x[i] = cx, y[i] = cy;
                    }
            }
        }
    }
 
    double minD = INT_MAX;
 
    for (int i = 0; i < n-skip; ++i)
        for (int j = i+1; j < n-skip; ++j)
            minD = min(minD, get(x[i]-x[j], y[i]-y[j])-r[i]-r[j]);
 
    for (int it = 0; it < 100; ++it)
    {
        int i = rand()%(n-skip), j = rand()%(n-skip);
        if (i == j) 
            continue;
        swap(radius[i], radius[j]);
 
        double md = INT_MAX;
        for (int i = 0; i < n-skip; ++i)
            for (int j = i+1; j < n-skip; ++j)
                md = min(md, get(x[i]-x[j], y[i]-y[j])-radius[i]-radius[j]);
 
        if (md > minD)
            minD = md;
        else
            swap(radius[i], radius[j]);
    }
 
    play();
 
    if (!R)
    {
        double minD = INT_MAX;
 
        for (int i = 0; i < placed; ++i)
            for (int j = i+1; j < placed; ++j)
                minD = min(minD, get(x[i]-x[j], y[i]-y[j])-r[i]-r[j]);
 
        cout << minD << endl;
    }
 
    return 0;
}
