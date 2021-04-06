#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
int main(){int T; cin >> T;
    while (T--) {long long N, X; cin >> N >> X; vector<long long> a(N);
        for (int i = 0; i < N; i++){cin >> a[i];} vector<long long> sum(N+1, 0);
        for (int i = N-1; ~i; i--){sum[i] = sum[i+1]+a[i];}vector<long long> f(N), g(N); g[0] = X;
        for (int i = 1; i < N; i++){g[0] += i*a[i];}
        for (int i = 1; i < N; i++){g[i]=g[i-1]-sum[i]+sum[0]-sum[i];} long long ans = X*N;
        for (int i = 0; i < N; i++){f[i] = g[i]; long long delta = sum[i];
            for (int j = i-1; ~j; j--){f[i] = min(f[i],f[j]-delta+X);delta += sum[(i+j+1)/2];}
            ans=min(ans,f[i]);}cout<<(sum[0] == 0?0:ans)<<endl;}}