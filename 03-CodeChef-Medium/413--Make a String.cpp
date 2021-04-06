#include<bits/stdc++.h>

using namespace std;

#define FOR(i,n)	for(int i=0;i<(int)n;i++)
#define FOB(i,n)	for(int i=n;i>=1;i--)
#define MP(x,y)	make_pair((x),(y))
#define ii pair<int, int>
#define lli long long int
#define ld long double
#define ulli unsigned long long int
#define lili pair<lli, lli>
#ifdef EBUG
#define DBG	if(1)
#else
#define DBG	if(0)
#endif
#define SIZE(x) int(x.size())
const int infinity = 2000000999 / 2;
const long long int inff = 4000000000000000999;

typedef complex<long double> point;

template<class T>
T get() {
    T a;
    cin >> a;
    return a;
}

template <class T, class U>
ostream& operator<<(ostream& out, const pair<T, U> &par) {
    out << "[" << par.first << ";" << par.second << "]";
    return out;
}

template <class T>
ostream& operator<<(ostream& out, const set<T> &cont) {
    out << "{";
    for (const auto &x:cont) out << x << ", ";
    out << "}";
    return out;
}

template <class T, class U>
ostream& operator<<(ostream& out, const map<T,U> &cont) {
    out << "{";
    for (const auto &x:cont) out << x << ", ";
    out << "}"; return out;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
  FOR(i, v.size()){
    if(i) out << " ";
    out << v[i];
  }
  out << endl;
  return out;
}

bool ccw(point p, point a, point b) {
  if((conj(a - p) * (b - p)).imag() <= 0) return false;
  else return true;
}

struct pismenkac {
    char pismenko;
    int ends;
    int starts;
    vector<pismenkac *> deti;
    pismenkac *aho;
    int len;
    
    pismenkac(char c, int l) {
        pismenko = c;
        ends = -1;
        starts = -1;
        aho = NULL;
        deti.resize(30);
        len = l;
    }
    
    void add_string(string s, int it, int start, int end) {
        if (s.size() == it) {
            ends = (ends == -1 ? end : min(ends, end));
            starts = (starts == -1 ? start : min(starts, start));
        }
        else {
            if (deti[s[it] - 'a'] == NULL) deti[s[it] - 'a'] = new pismenkac(s[it], it + 1);
            deti[s[it] - 'a'] -> add_string(s, it + 1, start, end);
        }
    }
    
    void debug_print(string k, string s) {
        cout << k << "In prefix |" << s << "| [st=" << starts << "; en=" << ends << "] we have: " << endl;
        FOR(i, 26) {
            if (deti[i] != NULL) {
                cout << k << " -["<< i << "]-> " << deti[i] -> pismenko << ":" << endl;
                string t = s;
                t.push_back(deti[i] -> pismenko);
                deti[i] -> debug_print(k + "  ", t);
            }
        }
    }
    
};

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    
    int n = get<int>();
    
    pismenkac *tria = new pismenkac('-', 0);
    
    vector<string> s;
    vector<lli> cl, cr, kl, kr;
    
    FOR(i, n) s.push_back(get<string>());
    FOR(i, 26) cl.push_back(get<int>());
    FOR(i, 26) cr.push_back(get<int>());
    FOR(i, n) kl.push_back(get<int>());
    FOR(i, n) kr.push_back(get<int>());
    
    FOR(i, n) {
        tria -> add_string(s[i], 0, kl[i], kr[i]);
    }
    
    DBG tria -> debug_print("", "");
    string t = get<string>();
    
    int m = t.size();
    
    queue<pismenkac *> Q;  
    tria -> aho = tria;
    
    FOR(i, 26) {
        if(tria -> deti[i] != NULL) {
            tria -> deti[i] -> aho = tria;
            Q.push(tria -> deti[i]);
        }
    }
    
    while (Q.size()) {
        auto tr = Q.front();
            Q.pop();
        
        for (auto child : tr -> deti) {
            if (child == NULL) continue;
            child -> aho = tr -> aho;
            while (child -> aho != tria && child -> aho -> deti[child -> pismenko - 'a'] == NULL) {
                child -> aho = child -> aho -> aho;
            }
            if (child -> aho -> deti[child -> pismenko - 'a'] != NULL) child -> aho = child -> aho -> deti[child -> pismenko - 'a'];
            Q.push(child);
        }
    }
    
    pismenkac *aho = tria;
    
    vector<vector<lli> > lmatches(m, vector<lli>(103, -1));
    vector<vector<lli> > rmatches(m, vector<lli>(103, -1));
    vector<vector<lli> > dp(m, vector<lli>(m + 1, inff));
    
    FOR(i, m) dp[i][i + 1] = 0;
    
    FOR(i, m) {
        while (aho != tria && aho -> deti[t[i] - 'a'] == NULL) {
            aho = aho -> aho;
        }
        
        if (aho -> deti[t[i] - 'a'] != NULL) {
            aho = aho -> deti[t[i] - 'a'];
            auto aho2 = aho;
                
            while (aho2 != tria) {
                if (aho2 -> ends != -1) {
                    lmatches[i][aho2 -> len] = aho2 -> starts;
                    rmatches[i - aho2 -> len + 1][aho2 -> len] = aho2 -> ends;
                    dp[i - aho2 -> len + 1][i + 1] = 0;
                }
                aho2 = aho2 -> aho;
            }
            
        }
    }
    
    FOR(l, m) {
        FOR(i, m - l) {
            int j = i + l + 1;
            if (i) {
                DBG cout << "Can do " << t[i - 1] << "+" << t.substr(i, l + 1) << " for " << l + 1 << " * " << cl[t[i - 1] - 'a'] << " + " << dp[i][j] << endl;
                dp[i - 1][j] = min(dp[i - 1][j], dp[i][j] + ((lli)l + 1) * cl[t[i - 1] - 'a']);
            }
            if (j < m) {
                DBG cout << "Can do " << t.substr(i, l + 1) << "+" << t[j] << " for " << dp[i][j] << " + " << l + 1 << " * " << cr[t[j] - 'a'] << endl;
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + ((lli)l + 1) * cr[t[j] - 'a']);
            }
            
            for (int y = 1; i - y >= 0 && y < 101; y ++) {
                if (lmatches[i - 1][y] != -1) {
                    DBG cout << "Left match at i= " << i << ": " << t.substr(i - y, y) << "+" << t.substr(i, l + 1) << " for " << l + 1 << " * " << lmatches[i - 1][y] << " + " << dp[i][j] << endl;
                    dp[i - y][j] = min(dp[i - y][j], dp[i][j] + ((lli)l + 1) * lmatches[i - 1][y]);
                }
            }
            
            for (int y = 1; y < 101 && y + j <= m; y ++) {
                if (rmatches[j][y] != -1) {
                    DBG cout << "Right match at j= " << j << ": " << t.substr(i, l + 1) << "+" << t.substr(j, y) << " for " << dp[i][j] << " + " << l + 1 << " * " << rmatches[j][y] << endl;
                    dp[i][j + y] = min(dp[i][j + y], dp[i][j] + ((lli)l + 1) * rmatches[j][y]);
                }
            }
        }
    }
    
    cout << dp[0][m] << endl;
    
    
    
    
}
