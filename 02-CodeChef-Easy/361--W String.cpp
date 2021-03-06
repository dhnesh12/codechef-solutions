#pragma comment(linker, "/STACK:16777216")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <memory.h>
#include <sstream>
#include <complex>

#define FOR(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)

using namespace std;

int cnt[12222][30];

int calc(int u, int v) {
    int res = 0;

    FOR (i, 0, 25)
        res = max(cnt[v][i]-cnt[u][i], res);

    if (res == 0) res = -1000000;

    return res;
}

int main() {
    int ntest;
    cin >> ntest;

    while (ntest--) {
        string s;
        cin >> s;
        int n = s.size();
        s = "#" + s;

        //calculating cnt[i][c] is the number of character ('a' + c) in the substring s[0..i]
        memset(cnt, 0, sizeof(cnt));

        FOR (i, 1, n) {
            FOR (j, 0, 25)
                cnt[i][j] = cnt[i - 1][j];

            if (s[i] != '#')
                    cnt[i][s[i] - 'a'] ++;
        }

        //pos store the positons of # characters
        vector <int> pos;
        FOR (i, 0, n)
            if (s[i] == '#') pos.push_back(i);

        int res = 0;
        int nPos = pos.size();

        //calc(u, v) return the number of characters with the highest frequency in the sub-string s[u...v] which has s[u] = s[v] = '#'
        //in the case the return value shoule be 0, it return -1000000 instead so that we don't have to handle the case where two #s are adjacent in the wstring
        FOR (i, 0, nPos - 3)
            res = max(res, calc(0, pos[i]) + calc(pos[i], pos[i + 1]) + calc(pos[i + 1], pos[i + 2]) + calc(pos[i + 2], n) + 3);

        cout << res << endl;
    }
    return 0;
}
