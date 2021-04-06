#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define LD long double

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)


const int N = 1010;

int inf = 1e9;
int mod = 1e9 + 7;

int mem[N][N];
int cntQ = 0;

int ask(int u, int v) {
    if(mem[u][v] != -1) {
        return mem[u][v];
    }
    if(u == v) {
        return mem[u][v] = u;
    }
    cntQ++;
    if(cntQ >= 25000) {
        assert(1 == 0);
    }
    cout << "? " << u << " " << v << "\n";
    cout.flush();
    int w;
    cin >> w;
    assert(w != -1);
    return mem[u][v] = mem[v][u] = w;
}

vector<vector<int>> chains[N];
int ans[N];

int getRoot(int n) {
    int x = rand() % n + 1;
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        int temp = ask(i, x);
        if(temp == i) {
            v.push_back(i);
        }
    }
    sort(v.begin(), v.end(), [&](int a, int b) {
        return ask(a, b) == b;
    });

    return v.back();
}

void solve(int root, int node) {
    if(chains[root].empty()) {
        vector<int> temp;
        temp.push_back(node);
        chains[root].push_back(temp);
        return;
    }

    int maxLenIdx = -1, sz = -1;
    for(int i = 0; i < (int)chains[root].size(); i++) {
        if((int)chains[root][i].size() > sz) {
            sz = (int)chains[root][i].size();
            maxLenIdx = i;
        }
    }

    int last = chains[root][maxLenIdx].back();
    int w = ask(last, node);

    if(w == root) {
        maxLenIdx = -1;
        for(int i = 0; i < (int)chains[root].size(); i++) {
            int x = ask(node, chains[root][i][0]);
            if(x != root) {
                maxLenIdx = i;
                break;
            }
        }
//        debug(root, node, maxLenIdx);
        if(maxLenIdx == -1) {
            vector<int> temp;
            temp.push_back(node);
            chains[root].push_back(temp);
            return;
        }
    }

    last = chains[root][maxLenIdx].back();
    w = ask(last, node);

    if(w == last) {
        chains[root][maxLenIdx].push_back(node);
        return;
    }

    for(int u : chains[root][maxLenIdx]) {
        if(u == w) {
            solve(u, node);
            return;
        }
    }

    int low = 0, high = (int)chains[root][maxLenIdx].size() - 1;
    int idx = -1;

    while(low <= high) {
        int mid = (low + high) / 2;
        int ww = ask(node, chains[root][maxLenIdx][mid]);
        if(ww == w) {
            idx = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    assert(idx != -1);

    vector<int> temp;
    for(int i = 0; i < idx; i++) {
        temp.push_back(chains[root][maxLenIdx][i]);
    }
    temp.push_back(w);
    for(int i = idx; i < (int)chains[root][maxLenIdx].size(); i++) {
        temp.push_back(chains[root][maxLenIdx][i]);
    }
    chains[root][maxLenIdx] = temp;

    if(w != node) {
        temp.clear();
        temp.push_back(node);
        chains[w].push_back(temp);
    }

    return;
}


signed main()
{
    //freopen("IN", "r", stdin);
    //freopen("OUT", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    srand(time(0));

    int _; cin >> _;
    while(_--) {
        int n, q;
        cin >> n >> q;

        memset(mem, -1, sizeof(mem));
        cntQ = 0;

        int root = getRoot(n);

//        debug(root);

        for(int i = 1; i <= n; i++) {
            chains[i].clear();
        }

        for(int i = 1; i <= n; i++) {
            if(i == root) {
                continue;
            }
            solve(root, i);
        }

        memset(ans, -1, sizeof(ans));

        for(int i = 1; i <= n; i++) {
            for(auto it : chains[i]) {
                int p = i;
                for(int j = 0; j < (int)it.size(); j++) {
                    ans[it[j]] = p;
                    p = it[j];
                }
            }
        }

        cout << "! ";
        for(int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        cout.flush();
        cin >> n;
        assert(n != -1);
    }
    return 0;
}