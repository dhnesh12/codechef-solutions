#include <stdio.h> 
#include <stdlib.h> 

#define ullint unsigned long long
#define uint unsigned int 

#define MOD 4294967143ULL
#define MODINV 1789569643ULL

typedef struct {
    ullint a;
    ullint b;
} surd;

inline ullint modprod(ullint a, ullint b) {
    return (a*b) % MOD;
}

inline ullint modminus(ullint a, ullint b) {
    a = a % MOD;
    b = b % MOD;
    if (a >= b)
        return a - b;
    else
        return (MOD - b) + a;
}

inline surd mult(surd s1, surd s2) {
    surd res;
    res.a = (modprod(s1.a,s2.a) + modprod(modprod(s1.b,s2.b),3)) % MOD;
    res.b = (modprod(s1.a,s2.b) + modprod(s1.b,s2.a)) % MOD;
    return res;
}


ullint p3array[65];
ullint p2array[65];
surd surdarray[65];

void init() {
    p2array[1] = 2;
    p3array[1] = 3;
    surdarray[1].a = 2;
    surdarray[1].b = 1;
    for(int i = 2; i < 65; i++) {
        p2array[i] = modprod( p2array[i-1] , p2array[i-1] );
        p3array[i] = modprod( p3array[i-1] , p3array[i-1] );
        surdarray[i] = mult(surdarray[i-1],surdarray[i-1]);
    }
}

void solve(ullint a) {

    if (a == 0 || a % 2 == 1) {
        printf("0\n");
        return;
    }

    a = a >> 1;

    ullint p2 = 1;
    ullint p3 = 1;
    surd ps;
    ps.a = 1;
    ps.b = 0;

    int i = 1;
    while(a > 0) {
        if ( (a & 1) == 1) {
            p2 = modprod(p2, p2array[i]);
            p3 = modprod(p3, p3array[i]);
            ps = mult(ps,surdarray[i]);
        }
        i++;
        a = a >> 1;
    }

    surd psminus;
    psminus.a = modminus(2*ps.a, 3*ps.b);
    psminus.b = modminus(2*ps.b, 3*ps.a);

    ullint res1 = modprod(MODINV, (2*psminus.a + p3 + 2*p2 + 3) % MOD );
    ullint res2 = 2*(2*ps.a + p3 + p2 + 1);
    
    ullint res = modminus(res2, res1);
    printf("%llu\n", res);
}

main() {

    int T;
    scanf("%d", &T);

    int i;
    init();
    for(i = 0; i < T; i++) {

        ullint a;
        scanf("%llu", &a);

        solve(a);
    }
}

