#include <bits/stdc++.h>

constexpr int N = 10;

std::vector<std::vector<int>> partitions[N + 1];
std::vector<double> anss[N + 1];

std::vector<double> gauss(std::vector<std::vector<double>> a, std::vector<double> b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        double x = a[i][i];
        for (int j = i; j < n; ++j) a[i][j] /= x;
        b[i] /= x;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            x = a[j][i];
            for (int k = i; k < n; ++k) a[j][k] -= a[i][k] * x;
            b[j] -= b[i] * x;
        }
    }
    return b;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed << std::setprecision(7);
    
    for (int n = 1; n <= N; ++n) {
        std::vector<int> partition;
        std::function<void(int, int)> dfs = [&](int rest, int last) {
            if (rest == 0) {
                partitions[n].push_back(partition);
                return;
            }
            for (int i = 1; i <= last && i <= rest; ++i) {
                partition.push_back(i);
                dfs(rest - i, i);
                partition.pop_back();
            }
        };
        dfs(n, n);
        
        int cnt = partitions[n].size();
        std::vector<std::vector<double>> a(cnt, std::vector<double>(cnt));
        std::vector<double> b(cnt);
        a[0][0] = 1;
        for (int x = 1; x < cnt; ++x) {
            partition = partitions[n][x];
            a[x][x] += 1;
            b[x] += 1;
            int total = n * (n - 1) / 2;
            for (int i = 0; i < int(partition.size()); ++i) {
                for (int j = 1; j < partition[i]; ++j) {
                    double prob = partition[i] * 0.5 / total;
                    auto newPartition(partition);
                    newPartition.erase(newPartition.begin() + i);
                    newPartition.push_back(j);
                    newPartition.push_back(partition[i] - j);
                    std::sort(newPartition.begin(), newPartition.end(), std::greater<>());
                    a[x][std::lower_bound(partitions[n].begin(), partitions[n].end(), newPartition) - partitions[n].begin()] -= prob;
                }
            }
            for (int i = 0; i < int(partition.size()); ++i) {
                for (int j = 0; j < i; ++j) {
                    double prob = partition[i] * partition[j] * 1.0 / total;
                    auto newPartition(partition);
                    newPartition.erase(newPartition.begin() + i);
                    newPartition.erase(newPartition.begin() + j);
                    newPartition.push_back(partition[i] + partition[j]);
                    std::sort(newPartition.begin(), newPartition.end(), std::greater<>());
                    a[x][std::lower_bound(partitions[n].begin(), partitions[n].end(), newPartition) - partitions[n].begin()] -= prob;
                }
            }
        }
        anss[n] = gauss(a, b);
    }
    
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            --a[i];
        }
        std::vector<bool> vis(n);
        std::vector<int> partition;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            int len = 0;
            for (int j = i; !vis[j]; j = a[j], ++len) vis[j] = true;
            partition.push_back(len);
        }
        std::sort(partition.begin(), partition.end(), std::greater<>());
        std::cout << (double)anss[n][std::lower_bound(partitions[n].begin(), partitions[n].end(), partition) - partitions[n].begin()] << "\n";
    }
    
    return 0;
}