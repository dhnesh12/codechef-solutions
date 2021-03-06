
#include <stdio.h> // printf, scanf
int b[500][500], n;
 
bool safe(int x, int y) {
    int i = x, j = y;
    while(--i >= 0)
        if(b[y][i] == -1) break;
        else if(b[y][i] == 1) return false;
    while(--j >= 0)
        if(b[j][x] == -1) break;
        else if(b[j][x] == 1) return false;
    i = x, j = y;
    while(--i >= 0 && --j >= 0)
        if(b[j][i] == -1) break;
        else if(b[j][i] == 1) return false;
    i = x, j = y;
    while(++j < n && --i >= 0)
        if(b[j][i] == -1) break;
        else if(b[j][i] == 1) return false;
 
    return true;
}
 
bool solution(int x) {
    for(int y = 0; y < n; ++y) {
        if(safe(x,y) && b[y][x] != -1) {
            b[y][x] = 1;
            if(x == n-1) return true;
            if(solution(x + 1)) return true;
            b[y][x] = 0;
        }
    }
    return false;
}
 
int main() {
    int t,k,i,j;
 
    scanf("%d", &t);
    while(--t >= 0) {
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                b[j][i] = 0;
 
        scanf("%d%d\n", &n, &k);
        while(--k >= 0) {
            scanf("%d%d", &j, &i);
            b[--j][--i] = -1;
        }
 
        solution(0);
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                if(b[j][i] == 1) printf((i<n-1)?"%d ":"%d", j + 1);
        printf("\n");
    }
    return 0;
}