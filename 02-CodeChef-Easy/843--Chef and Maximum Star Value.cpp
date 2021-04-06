#include<iostream>
using namespace std;


int main(){
    cin.sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n ;
        cin >> n;
        bool hsh[1000001] = {0};
        int cnt[1000001] = {0};
        int A[n];

        for(int i = 0; i < n; i++){
            cin >> A[i];
            cnt[A[i]]++;
            hsh[A[i]] = 1;
        }

        int ans = 0;
        for(int i = n - 1; i > 0; i--){
            cnt[A[i]]--;

            int count = 0;
            if(!hsh[A[i]])
                continue;
            
            for(int j = A[i]; j < 1000001; j += A[i]){
                count += cnt[j];
            }
            ans = max(ans, count);
            hsh[A[i]] = 0;
        }
        cout << ans << '\n';
    }
    return 0;
}