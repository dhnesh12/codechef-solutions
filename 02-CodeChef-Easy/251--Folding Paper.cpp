#include<bits/stdc++.h>
using namespace std;

#define int           long long 
#define S             second
#define F             first
#define pb            push_back
#define ppb           pop_back()
#define ppb           pop_back()
#define B(c)          (c).begin()
#define E(c)          (c).end()
#define all(c)        (c).begin(),(c).end()
#define rall(c)       (c).rbegin(),(c).rend() 
#define lb            lower_bound
#define si(c)         (int)((c).size())
#define lcm(a,b)      (a * (b / __gcd(a,b)))  
#define inf           (int)(9e18)
#define err           cerr << "move" << '\n';
#define endl          '\n'
#define pow(x, n)     (int)(pow(x, n))
#define mp            make_pair

typedef vector<int>                           vi;
typedef pair<int,int>                         pii;
typedef vector<pii>                           vpi;
typedef vector<vector<int> >                  vvi;;
typedef priority_queue<pii, vector<pii>, greater<pii> > pq;

const int N = 1e3+10;

struct Point{
    int x, y;
};

bool cmpx(Point p1, Point p2){
    return p1.x < p2.x;
}

bool cmpy(Point p1, Point p2){
    return p1.y < p2.y;
}

class ClosetDis{
public:
    static Point Px[N], Py[N];
    static int n;
    void AddPoint(int x, int y){
        Px[n] = Py[n] = {x, y}, n++;
    }
    double Dis(Point p1, Point p2){
        return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)); 
    }
    double BruteForce(Point P[], int n){
        double dis = 2e18;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                dis = min(dis, Dis(P[i], P[j]));
            }
        }
        return dis;
    }
    double StripCloset(Point P[], int n, double d){
        double dis = d;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n && (P[j].y-P[i].y < dis); j++){
                if(Dis(P[i], P[j]) < dis){
                    dis = Dis(P[i], P[j]);
                }
            }
        }
        return dis;
    }
    double MinDis(Point Px[], Point Py[], int n){
        if(n <= 3)return BruteForce(Px, n);

        int mid = n/2, l = 0, r = 0;
        Point p = Px[mid];
        Point Pyl[mid+1], Pyr[n-mid-1];

        for(int i = 0; i < n; i++){
            if(Py[i].x <= p.x)Pyl[l++] = Py[i];
            else Pyr[r++] = Py[i]; 
        } 
        
        double dl = MinDis(Px, Pyl, mid+1);
        double dr = MinDis(Px+mid+1, Pyr, n-mid-1);

        double dis = min(dl, dr);

        Point strip[n];
        int j = 0;
        for(int i = 0; i < n; i++){
            if(abs(Py[i].x-p.x) < dis){
                strip[j++] = Py[i];
            }
        }
        return min(dis, StripCloset(strip, j, dis));
    }

    double Init(int n){
        sort(Px, Px+n, cmpx);
        sort(Py, Py+n, cmpy);

        return MinDis(Px, Py, n);
    }

};

int ClosetDis :: n;
Point ClosetDis :: Px[N], ClosetDis :: Py[N];

void solve(){
    ClosetDis :: n = 0;
    ClosetDis cd;
    int n, m, h, w;
    cin >> n >> m >> w >> h;
    string s;
    cin >> s;
    int l = 0, r = 0, u = 0, d = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == 'L')l++;
        else if(s[i] == 'R')r++;
        else if(s[i] == 'U')u++;
        else d++;
    }
    int x[m], y[m];
    for(int i = 0; i < m; i++){
        cin >> x[i] >> y[i];
        cd.AddPoint(x[i], y[i]);
    }
    double ans;
    ans = m != 1 ? cd.Init(m) : 2e18;
    
    for(int i = 0; i < m; i++){

        if(l+r > 1)ans = min(ans, (double)min(2*x[i], 2*(w-x[i])));
        else if(r > 0)ans = min(ans, (double)(2*(w-x[i])));
        else if(l > 0)ans = min(ans, (double)(2*x[i]));

        if(u+d > 1)ans = min(ans, (double)min(2*y[i], 2*(h-y[i])));
        else if(u > 0)ans = min(ans, (double)(2*(h-y[i])));
        else if(d > 0)ans = min(ans, (double)(2*y[i]));
    }
    //cout << ClosetDis :: << endl;
    cout << ans << endl;
}

signed main(){

    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);   

    int t = 1;
    clock_t start, end; 
    start = clock(); 

    cout << fixed << setprecision(15);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    cin >> t;

    while(t--){
        solve();
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    // cerr<<time_taken;
}