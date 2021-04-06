#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int get_weight(int color) {
    cout << 1 << endl;
    cout << 1 << " " << color << endl;
    cout << 0 << endl; 
    int result;
    cin >> result;
    return result;
}

void answer(int color) {
    cout << 2 << endl;
    cout << color << endl;
    exit(EXIT_SUCCESS);
}

int main() {
    for (int color = 1; color <= 5; color++) {
        if (get_weight(color) == 2) {
            answer(color);
        }
    }
}
