#include<iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for (int xi=0; xi<t; xi++) {
        int n,v;
        cin >> n >> v;
        int curr_max_i = -1;
        int curr_max = 0;
        int prev = 0;
        int curr = 0;
        int arr_val;
        for (int i=0; i<n; i++) {
            cin >> arr_val;
            if (arr_val > v) {
                if (curr_max_i > -1 && curr_max == arr_val) {
                    curr++;
                    curr_max_i = i;
                } else {
                    prev = max(prev, curr);
                    curr = i - curr_max_i;
                    curr_max_i = i;
                    curr_max = arr_val;
                }
            } else {
                curr++;
            }
        }
        cout << (prev ? max(prev, curr) : 0) << "\n";
    }
    return 0;
}