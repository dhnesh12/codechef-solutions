#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1000000000;
const int MAXN = 100000;
const int MAXLL = 7;
const int MAXLA = 100;

int dp[MAXLL + 5][MAXN + 5], par[MAXLL + 5][MAXN + 5], minGet[MAXN + 5], split;
vector<int> optSeq[MAXN + 5];

void add (vector<int>& where, int what, int howMany) {
    for(int i = 0; i < howMany; i++)
        where.push_back(what);
}

void outputPattern (vector<int> pattern) {
    for(int i = 0; i < pattern.size(); i++) {
        pattern[i] = pattern[i] * 100000 - i;
    }
    vector<int> sorted(pattern);
    sort(sorted.begin(), sorted.end());
    cout << pattern.size() << endl;
    for(int i = 0; i < pattern.size(); i++) {
        cout << (int)(lower_bound(sorted.begin(), sorted.end(), pattern[i]) - sorted.begin()) + 1;
        if (i != pattern.size() - 1)
            cout << " " ;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    int lisLength = 5;
    for(int len = 0; len <= lisLength; len++)
        for(int prod = 1; prod <= MAXN; prod++)
            dp[len][prod] = INF;
    
    dp[0][1] = 0;
    for(int i = 0; i <= lisLength; i++) for(int j = 1; j <= MAXN; j++) {
        for(int k = 1; k * j <= MAXN; k++)
            if (dp[i + 1][j * k] > dp[i][j] + k) {
                dp[i + 1][j * k] = dp[i][j] + k;
                par[i + 1][j * k] = k;
            }
    }
    for(int i = 1; i <= MAXN; i++) {
        minGet[i] = dp[lisLength][i];
        if (minGet[i] <= 100) {
            int cnt = 0;
            int pi = i, pj = lisLength;
            while (pj > 0) {
                add(optSeq[i], ++cnt, par[pj][pi]);
                pi /= par[pj][pi];
                --pj;
            }
        }
    }
    int tn;
    cin >> tn;
    while (tn--) {
        int n;
        cin >> n;
        if (minGet[n] <= 100) {
            outputPattern(optSeq[n]);
        } else {
            int split = -1;
            for(int i = 1; i < n; i++) if (minGet[i] + minGet[n - i] <= 100) {
                split = i;
                break;
            }
            assert(split != -1);
            vector<int> pat;
            pat.clear();
            for(int i : optSeq[split])
                pat.push_back(i + 5);
            for(int i : optSeq[n - split])
                pat.push_back(i);
            
            outputPattern(pat);
        }
    }
    return 0;
}