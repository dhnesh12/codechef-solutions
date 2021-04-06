#include <iostream>
using namespace std;

int C[100011];
int main() {
    int z;
    cin >> z;
    for (int cas = 1; cas <= z; cas++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> C[i];
        }
        bool found = false;
        for (int i = 2; i < n; i++) {
            if (C[i-2] == C[i-1] && C[i-1] == C[i]) {
                found = true;
                break;
            }
        }
        cout << (found ? "Yes" : "No") << endl;
    }
}