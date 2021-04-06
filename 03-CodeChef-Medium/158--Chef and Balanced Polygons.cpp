#include "bits/stdc++.h"
using namespace std;
struct point{
    long long x , y;
    int val;
    point(long long _x = 0 , long long _y = 0 , int _val = 0){
        x = _x;
        y = _y;
        val = _val;
    }
    point operator + (const point &other) const {
        return point(x + other.x , y + other.y , val);
    }
    point operator - (const point &other) const {
        return point(x - other.x , y - other.y , val);
    }
    point operator * (const long long k) const {
        return point(x * k , y * k , val);
    }
};
const int N = 55;
const int inf = 1e9 + 9;
int t;
int n , m;
point arr[N];
long long dp[N][N][N + N];
int sum[N][N][N];
point p2[N];
int val[N];
long long dot(point a , point b){
    return a.x * b.x + a.y * b.y;
}
long long cross(point a , point b){
    return a.x * b.y - a.y * b.x;
}
long long dist(point a , point b){
    return dot(a - b , a - b);
}
bool clockwise(point a , point b , point c){
    long long val = cross(b - a , c - a);
    return (val <= 0);
}
bool inside(point a , point b , point c , point d){
    return clockwise(a , b , d) && clockwise(b , c , d) && clockwise(c , a , d);
}
int solve(point a , point b , point c){
    int res = 0;
    for(int i = 1 ; i <= m ; ++i){
        if(inside(a , b , c , p2[i])){
            if(val[i]){
                ++res;
            }
            else{
                --res;
            }
        }
    }
    return res;
}
long long solve(int first , int cur , int dif){
    if(dp[first][cur][dif + m] != -1){
        return dp[first][cur][dif + m]; 
    }
    long long res = !dif;
    for(int pos = cur + 1 ; pos <= n ; ++pos){
        res += solve(first , pos , dif + sum[first][cur][pos] - sum[first][cur][first]);
    }
    return dp[first][cur][dif + m] = res;
}
int main(){
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &n , &m);
        for(int i = 1 ; i <= n ; ++i){
            scanf("%lld %lld" , &arr[n - i + 1].x , &arr[n - i + 1].y);
        }
        for(int i = 1 ; i <= m ; ++i){
            scanf("%lld %lld %d" , &p2[i].x , &p2[i].y , val + i);
        }
        for(int i = 1 ; i <= n ; ++i){
            for(int j = 1 ; j <= n ; ++j){
                for(int k = 0 ; k <= m + m ; ++k){
                    dp[i][j][k] = -1;
                }
            }
        }
        for(int i = 1 ; i <= n ; ++i){
            for(int j = i + 1 ; j <= n ; ++j){
                for(int k = j + 1 ; k <= n ; ++k){
                    sum[i][j][k] = solve(arr[i] , arr[j] , arr[k]);
                }
                sum[i][j][i] = solve(arr[i] , arr[j] , arr[i]);
            }
        }
        long long res = 0;
        for(int i = 1 ; i <= n ; ++i){
            for(int j = i + 1 ; j <= n ; ++j){
                res += solve(i , j , sum[i][j][i]) - (!sum[i][j][i]);
            }
        }
        printf("%lld\n" , res);
    }
}
