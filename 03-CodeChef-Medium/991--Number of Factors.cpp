#include <bits/stdc++.h>
#define maxN 1000001

using namespace std;

typedef long long vlong;

int p[maxN];

void prime(int x){
    int sq = sqrt(x);
    while(x%2 == 0){
        p[2]++;
        x/=2;
    }
    for(int i=3; i<=sq; i+=2){
        while(x%i == 0){
            p[i]++;
            x/=i;
        }
    }
    if(x>1)
        p[x]++;
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        memset(p, 0, sizeof(p));

        int n, x;
        cin >> n;
        while(n--){
            cin >> x;
            prime(x);
        }

        vlong num=1;
        for(int i=2; i<=maxN; i++){
            if(p[i] != 0){
                num *= (p[i]+1);
            }
        }
        cout << num << "\n";
    }
}
