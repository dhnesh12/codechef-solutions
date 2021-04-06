/*
Saurabh Joshi
IIIT Jabalpur
*/
#include<bits/stdc++.h>
#define LL long long int
#define M 1000000007
#define endl "\n"
#define eps 0.00000001
LL pow(LL a,LL b,LL m){ a%=m;LL x=1,y=a;while(b > 0){if(b%2 == 1){x=(x*y);if(x>m) x%=m;}y = (y*y);if(y>m) y%=m;b /= 2;}return x%m;}
LL gcd(LL a,LL b){if(b==0) return a; else return gcd(b,a%b);}
LL gen(LL start,LL end){LL diff = end-start;LL temp = rand()%start;return temp+diff;}
using namespace std;
int a[17][17];
vector<long long> v;
vector<string> v_str1, v_str2, global;
string temp;
int counter = -1;
vector<long long> v1, v2;
int delta = 0;
vector<long long> bcost;
vector<long long> acost;
void generate_all(int pos,int &n, int m, long long cost = 0) {
    if(pos == m + 1) {
        v.push_back(cost);
        global.push_back(temp);
        return;
    }
    for(int i = 1; i <= n; i++) {
        temp.push_back((char)(96 + i));
        generate_all(pos + 1, n , m , cost + a[delta + pos][i]);
        temp.pop_back();
    }
}

inline long long check(long long cost) {
    long long total = 0;
    for(int i = 0; i < v1.size(); i++) {
        long long rem = cost - v1[i];
        int l = 0, r = v2.size() - 1;
        int ans = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(v2[mid] >= rem) {
                ans = max(ans , mid);
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        total += (ans + 1);
    }   
    return total;
}

inline bool cmp(const pair<long long,int > &a, const pair<long long, int > &b) {
    if(a.first > b.first)
        return 1;
    return 0;
}
    


int main()	{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    long long k;
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    if(m == 1) { // handle this separately
        vector<pair<int,int> > v;
        for(int i = 1; i <= n; i++) {
            v.push_back({-a[1][i] , i});
        }
        sort(v.begin() , v.end());
        cout << (char)(96 + v[k - 1].second);
        return 0;
    }
    generate_all(1, n, m >> 1);
    v1 = v;
    for(int i = 0; i < v1.size(); i++) {
        acost.push_back(v1[i]);
    }
    sort(v1.begin() , v1.end(), greater<long long>());
    v_str1 = global;
    v.clear();
    delta = (m >> 1);
    counter = -1;
    global.clear();
    generate_all(1 , n, m - (m >> 1));
    v_str2 = global;
    v2 = v;
    for(int i = 0; i < v2.size(); i++) {
        bcost.push_back(v2[i]);
    } 
    sort(v2.begin() , v2.end(), greater<int>());
    long long l_cost = 0, r_cost = 10000000000LL;
    long long req_cost = -1;
    while(l_cost <= r_cost) {
        LL mid = (l_cost + r_cost) >> 1;
        if(check(mid) >= k) {
            req_cost = max(req_cost , mid);
            l_cost = mid + 1;
        }
        else {
            r_cost = mid - 1;
        }
    }
    
    long long k_ = check(req_cost + 1);
    k = k - k_;
    //sort(v1.begin() , v1.end(), cmp_l);
    //sort(v2.begin() , v2.end(), cmp_r);
    unordered_map<long long,int> cnt;
    for(int i = 0; i < v2.size(); i++) {
        cnt[v2[i]]++;
    }
    //find the kth string with cost req_cost
    string ans1 , ans2;
    for(int i = 0; i < v1.size(); i++) {
        long long cur = acost[i];
        long long req = req_cost  - cur;
        ans1 = v_str1[i];
        if(cnt[req] < k) {
            k -= cnt[req];
        }
        else {
            for(int j = 0; j < v2.size(); j++) {
                if(bcost[j] == req) {
                    --k;
                    if(k == 0) {
                        ans2 = v_str2[j];
                        break;
                    }
                }
            }
        }
        if(k == 0)
            break;
    }
    cout << ans1 << ans2;
}