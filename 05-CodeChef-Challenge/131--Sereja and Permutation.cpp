#include <bits/stdc++.h>
#define err(args...) {}
#ifdef DEBUG
#include "_debug.cpp"
#endif
using namespace std;
using ll = long long;
using ld = long double;
template <typename T> using lim = numeric_limits<T>;
template <typename T> istream& operator>>(istream& is, vector<T>& a) { for(T& x : a) { is >> x; } return is; }
template <typename T, typename Can> T bsearch(T L, T R, Can&& can, bool left_feasible = true) {
    static_assert(is_convertible<decltype(can), function<bool(T)>>::value, "can must be bool(T)");
    T& feasible = left_feasible ? L : R;
    T& infeasible = left_feasible ? R : L;
    while(R - L > 1) {
        T M = L + (R - L) / 2;
        (can(M) ? feasible : infeasible) = M;
    }
    return feasible;
}
double get_score(int n, int k, int s, vector<int>& a, vector<int>& I) {
    vector<int> psum(n);
    for(int i = 0; i < n; i++) {
        psum[i] = (i ? psum[i - 1] : 0) + a[I[i]];
    }
    double ans = 0;
    for(int i = 0; i < k; i++) {
        ans += a[I[i]] > s ? s : s - (psum[bsearch(i, n, [&](int k) {
            return psum[k] - (i ? psum[i - 1] : 0) <= s;
        })] - (i ? psum[i - 1] : 0));
    }
    return ans / k;
}
default_random_engine generator;
uniform_real_distribution<double> re_distribution(0.0, 1.0);
vector<int> anneal(int n, int k, int s, vector<int>& a, vector<int>& I) {
    uniform_int_distribution<int> int_distribution(0, n - 1);
    double best_score = get_score(n, k, s, a, I);
    double temp = 10.0;
    for(int iter = 1; iter <= 1000; iter++) {
        int i = int_distribution(generator), j = int_distribution(generator);
        swap(I[i], I[j]);
        double curr_score = get_score(n, k, s, a, I);
        if(best_score > curr_score or re_distribution(generator) < exp((best_score-curr_score)/(40*temp))) {
            best_score = curr_score;
        } else {
            swap(I[i], I[j]);
        }
        temp -= 0.01;
    }
    return I;
}
vector<int> greedy1(int n, int k, int s, vector<int>& a) {
    vector<int> smaller, bigger;
    for(int i = 0; i < n; i++) {
        (a[i] <= s ? smaller : bigger).push_back(i);
    }
    sort(smaller.begin(), smaller.end(), [&](int i, int j) {
        return a[i] > a[j];
    });
    sort(bigger.begin(), bigger.end(), [&](int i, int j) {
        return a[i] < a[j];
    });
    vector<int> I(n);
    for(int i = 0; i < n; i++) {
        I[i] = (smaller.empty() or (i % 2 and not bigger.empty()) ? bigger : smaller).back();
        (smaller.empty() or (i % 2 and not bigger.empty()) ? bigger : smaller).pop_back();
    }
    return anneal(n, k, s, a, I);
}
vector<int> greedy2(int n, int k, int s, vector<int>& a) {
    vector<int> I(n);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) {
        return (a[i] <= s and a[j] > s) or (a[i] > a[j]);
    });
    return anneal(n, k, s, a, I);
}
vector<int> brute(int n, int k, int s, vector<int>& a) {
    vector<int> I(n);
    iota(I.begin(), I.end(), 0);
    vector<int> best_I;
    double best_score = lim<double>::max();
    do {
        double curr_score = get_score(n, k, s, a, I);
        if(best_score > curr_score) {
            best_score = curr_score;
            best_I = I;
        }
    } while(next_permutation(I.begin(), I.end()));
    return best_I;
}
void print(int n, const vector<int>& I) {
    for(int i = 0; i < n; i++) {
        if(i) cout << " ";
        cout << I[i] + 1;
    }
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, k, s;
        cin >> n >> k >> s;
        vector<int> a(n);
        cin >> a;
        if(n <= 9) {
            print(n, brute(n, k, s, a));
        } else {
            auto g1 = greedy1(n, k, s, a), g2 = greedy2(n, k, s, a);
            if(get_score(n, k, s, a, g1) < get_score(n, k, s, a, g2)) {
                print(n, g1);
            } else {
                print(n, g2);
            }
        }
    }
    return 0;
}