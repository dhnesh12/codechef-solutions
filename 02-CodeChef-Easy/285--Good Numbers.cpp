#include <iostream>
#include <map>
using namespace std;
const int SIZE = 100001, PRIMESIZE = 304129;
int main() 
{
    int T;
    cin >> T;
    int minprime[PRIMESIZE] = {};
    for(int i = 2; i < PRIMESIZE; i++) {
        if(minprime[i] == 0) {
            for(int j = i; j < PRIMESIZE; j += i) {
                minprime[j] = i;
            }
        }
    }
    long long prefix[SIZE];
    prefix[1] = 0;
    for(int i = 2; i < SIZE; i++) {
        map<int, int> count;
        for(int j = i; j > 1; j /= minprime[j]) {
            count[minprime[j]]++;
        }
        bool squarefree = true, good = false;
        int current = 1;
        for(auto& j : count) {
            if(j.second > 1) {
                squarefree = false;
                break;
            }
            current *= j.first + 1;
        }
        if(squarefree) {
            count.clear();
            for(int j = current; j > 1; j /= minprime[j]) {
                count[minprime[j]]++;
            }
            if(minprime[count.size()] == count.size()) {
                good = true;
            }
        }
        prefix[i] = prefix[i - 1] + current * good;
    }
    for(int L, R; cin >> L >> R; ) {
        cout << prefix[R] - prefix[L - 1] << endl;
    }
    return 0;
}