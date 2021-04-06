
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long lint;

int main() {
  int ntest;
  scanf("%d", &ntest);
  for (int test = 0; test < ntest; ++test) {
    int n, max_time, start;
    scanf("%d %d %d", &n, &max_time, &start), --start;
    vector<int> positions(n);
    for (int i = 0; i < n; ++i)
      scanf("%d", &positions[i]);

    vector<vector<lint>> from_start(max_time + 1, vector<lint>(n, LLONG_MAX));
    from_start[0][start] = 0;
    for (int t = 0; t + 1 <= max_time; ++t)
      for (int i = 0; i < n; ++i)
        if (from_start[t][i] != LLONG_MAX)
          for (int j = 0; j < n; ++j) {
            lint cost = (lint)(positions[i] - positions[j]) *
                        (positions[i] - positions[j]);
            from_start[t + 1][j] = min(from_start[t + 1][j],
                                       from_start[t][i] + cost);
          }

    vector<vector<lint>> to_edge(max_time + 1, vector<lint>(n, LLONG_MAX));
    if (start > 0) {
      to_edge[0][0] = 0;
      for (int t = 0; t + 1 <= max_time; ++t)
        for (int i = 0; i < start; ++i)
          if (to_edge[t][i] != LLONG_MAX)
            for (int j = i; j < start; ++j) {
              lint cost = (lint)(positions[i] - positions[j]) *
                (positions[i] - positions[j]);
              to_edge[t + 1][j] = min(to_edge[t + 1][j],
                                      to_edge[t][i] + cost);
            }
    }
    if (start < n - 1) {
      to_edge[0][n - 1] = 0;
      for (int t = 0; t + 1 <= max_time; ++t)
        for (int i = n - 1; i > start; --i)
          if (to_edge[t][i] != LLONG_MAX)
            for (int j = i; j > start; --j) {
              lint cost = (lint)(positions[i] - positions[j]) *
                (positions[i] - positions[j]);
              to_edge[t + 1][j] = min(to_edge[t + 1][j],
                                      to_edge[t][i] + cost);
            }
    }
    lint result = LLONG_MAX;
    for (int to_cross = 0; to_cross < n; ++to_cross) {
      if (abs(start - to_cross) == n - 1) {
        result = min(result, from_start[max_time][to_cross]);
      } else {
        {
          int j = to_cross;
          for (int i = to_cross - 1; i >= 0; --i) {
            while (j + 1 < n &&
                   (positions[j + 1] - positions[to_cross]) <=
                       (positions[to_cross] - positions[i])) {
              ++j;
            }
            if ((i == 0 || i < start) && (j == n - 1 || j > start)) {
              for (int t = 0; t + 1 <= max_time; ++t) {
                lint res = from_start[t][to_cross];
                if (res == LLONG_MAX) continue;
                res += (lint)(positions[to_cross] - positions[i]) *
                  (positions[to_cross] - positions[i]);
                if (j > start) {
                  if (to_edge[max_time - t - 1][j] == LLONG_MAX) continue;
                  res += to_edge[max_time - t - 1][j];
                }
                if (i < start) {
                  if (to_edge[max_time - t - 1][i] == LLONG_MAX) continue;
                  res += to_edge[max_time - t - 1][i];
                }
                result = min(result, res);
              }
            }
          }
        }
        {
          int i = to_cross;
          for (int j = to_cross + 1; j < n; ++j) {
            while (i - 1 >= 0 &&
                   (positions[to_cross] - positions[i - 1]) <=
                       (positions[j] - positions[to_cross])) {
              --i;
            }
            if ((i == 0 || i < start) && (j == n - 1 || j > start)) {
              for (int t = 0; t + 1 <= max_time; ++t) {
                lint res = from_start[t][to_cross];
                if (res == LLONG_MAX) continue;
                res += (lint)(positions[j] - positions[to_cross]) *
                  (positions[j] - positions[to_cross]);
                if (j > start) {
                  if (to_edge[max_time - t - 1][j] == LLONG_MAX) continue;
                  res += to_edge[max_time - t - 1][j];
                }
                if (i < start) {
                  if (to_edge[max_time - t - 1][i] == LLONG_MAX) continue;
                  res += to_edge[max_time - t - 1][i];
                }
                result = min(result, res);
              }
            }
          }
        }
      }
    }
    printf("%lld\n", result);
  }
  return 0;
}
