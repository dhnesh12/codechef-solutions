#include <iostream>
#define RULL register unsigned long long
using namespace std;
constexpr int mod = 1000000007;
inline void fastscan(int &number){register int c;number=0;c=getchar();
    for(;(c>47&&c<58);c=getchar()){number=number*10+c-48;}}
int main(){int T; fastscan(T); for (int i = 0; i < T; i++){int N; fastscan(N); bool pows[100003] = {};
        for (int i = 3; i < N + 3; i++){int in; fastscan(in); pows[i] = in == 2;}RULL sum = 0;
        RULL nm3 = 0; RULL nm2 = 0; RULL nm1 = 1; RULL even = 0; RULL odd = 0; unsigned long long *cur = &odd;
        for (unsigned n = 3; n < N + 3; n++){cur=n&1 ? &odd : &even; RULL dNum = nm1; bool pnm3 = pows[n-3];
            if (pows[n-2]){dNum += nm2; if(pnm3) dNum += nm3;}
            if (pows[n]) {if(pnm3) *cur += nm3; sum += 2 * dNum + *cur; 
                if (pows[n-1] && n != N + 2){sum += *cur;} else{*cur = 0;}}
            else{sum += dNum;*cur = 0;}
            if (n >= N + 1 && pows[n]){sum -= dNum;}
            dNum %= mod;sum %= mod;nm3 = nm2;nm2 = nm1;nm1 = dNum;}sum -= *cur;printf("%d\n", sum);}}