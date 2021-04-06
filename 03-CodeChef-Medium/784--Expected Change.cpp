//#include <atcoder/maxflow.hpp>
#include <memory>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <functional>
#include <queue>
#include <deque>
#include <stack>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <fstream>
#include <iterator>
#include <random>
#include <chrono>
#include <complex>
#include <thread>
#include <bitset>

#define forr(i,start,count) for (int i = (start); i < (start)+(count); ++i)
#define set_map_includes(set, elt) (set.find((elt)) != set.end())
#define readint(i) int i; cin >> i
#define readll(i) ll i; cin >> i
#define readdouble(i) double i; cin >> i
#define readstring(s) string s; cin >> s

typedef long long ll;

using namespace std;
//using namespace atcoder;

ll modd = (1000LL * 1000LL * 1000LL + 7LL);
//ll modd = 998244353;

template<class T>
T fastpower(T x, ll pw, T id = 1) {
    T w = x, res = id;
    while (pw>0) {
        if (pw&1) {
            res = (res * w) % modd;
        }
        pw >>= 1;
        w = (w * w) % modd;
    }
    return res;
}

ll wrong(string s) {
        ll tot = 0, tot_changes = 0;
        forr(i,0,s.size()) {
            for(int j = i; j < s.size(); ++j) {
                ++tot;
                int minn = 0, curr = 0;
                for(int k = i; k <= j; ++k) {
                    if (s[k]=='(') { ++curr;  } 
                    if (s[k]==')') { --curr;  }
                    minn = min(minn, curr);
                }
                tot_changes += (-minn+1)/2;
            }
        }
        return (tot_changes * fastpower(tot, modd-2)) % modd;
}

int main(int argc, char *argv[])   {

    ios_base::sync_with_stdio(false);

    cout.precision(17);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rand_gen(0, modd);   // rand_gen(rng) gets the rand no

//    auto start = chrono::steady_clock::now();

    readint(test_cases);
//    int test_cases = 1;
    forr(t, 1, test_cases) {
        readint(n);
        readstring(s);

//        cout << wrong(s) << endl;

        ll tot = 0, tot_changes = 0;
        forr(i,0,s.size()) {
            int minn = 0, curr = 0;
            for(int j = i; j < s.size(); ++j) {
                ++tot;
                if (s[j]=='(') { ++curr;  } 
                if (s[j]==')') { --curr;  }
                minn = min(minn, curr);
                tot_changes += (-minn+1)/2;
            }
        }
        cout << (tot_changes * fastpower(tot, modd-2)) % modd << endl;
   }

//        auto stop = chrono::steady_clock::now(); 
//        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
//        cout << "Duration: " << duration.count() << endl;
    return 0;
}