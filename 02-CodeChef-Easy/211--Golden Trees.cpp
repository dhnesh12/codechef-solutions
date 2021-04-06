// By Riiven

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define scanInt(i) scanf("%d",&i)
#define scanStr(i) scanf("%s",&i)
#define scanLong(i) scanf("%lld",&i)
#define printInt(i) printf("%d\n",i)
#define printLong(i) printf("%lld\n",i)
#define printStr(i) printf("%s\n",i)
#define vci vector<int>
#define vcll vector<long long>
#define pb push_back
#define MOD 100000007

int initTax,slot1,slot2,k;
ll n;
int txt[101];

ll mat[101][101],temp[101][101];

ll gcd(ll a,ll b)
{
    if(a==0)
    return b;

    return gcd(b%a,a);

}

void init(){
    memset(txt,0,sizeof(txt));
    int i = 1;
    txt[i] = initTax;
    i++;
    while(i<=slot1+1){
        txt[i] = txt[i-1]+1;
        i++;
    }
    while(i<=slot2+slot1+1){
        txt[i] = (2 * txt[i-1]) % MOD;
        i++;
    }
}

void mat_mul(ll temp1[101][101]){

    ll temp2[101][101];
    memset(temp2,0,sizeof(temp2));
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            for(int l=0;l<k;l++)
                temp2[i][j] += mat[i][l]*temp1[l][j];
                
            if(temp2[i][j]>=MOD-1)
                temp2[i][j] = temp2[i][j] % (MOD-1);
        }
    }

    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            mat[i][j] = temp2[i][j];
}

void create_mat(ll n){
    if( n == 0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<k;i++)
            mat[i][i] = 1;
        memset(temp,0,sizeof(temp));
        for(int j=0;j<k;j++)
            temp[0][j] = 1;

        for(int j=1;j<k;j++)
            temp[j][j-1] = 1;
        return;
    }
    create_mat(n/2);
    mat_mul(mat);
    if(n % 2 != 0)
        mat_mul(temp);
}

ll expoItr(ll base,ll power){
    if(power == 0)
        return 1;

    ll t = 1;
    while(power > 0){
        if( power % 2 != 0)
            t = (t*base) % MOD;
        base = (base * base) % MOD;
        power = power / 2;
    }
    return t;
}

int main() {


    int t;
    scanInt(t);

    while(t--){
        scanInt(initTax);
        scanInt(slot1);
        scanInt(slot2);
        scanInt(k);
        scanLong(n);
        init();
        if(n <= slot1 + slot2 + 1)
            cout<<txt[n]<<endl;
        else{
            create_mat(n-slot1-slot2-1);

            ll result = 1;
            for(int i = slot1+slot2+1,j=0;i>slot1+slot2+1-k;i--,++j)
                result = (result * expoItr(txt[i],mat[0][j])) % MOD;

            cout<<result<<endl;
        }
    }
    return 0;
}





