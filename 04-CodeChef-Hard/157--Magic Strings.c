#include <stdio.h>
#include <string.h>
 
char ch;
#define MAXN 2005
char a[MAXN], s[MAXN];
char half[MAXN], mhalf[MAXN], shalf[MAXN];
int todel[MAXN][MAXN][2];
int len[MAXN][MAXN][2];
int sick[MAXN][MAXN][2];
int n;
 
int main(void){
    int i, j, k, q, t, tm;
    scanf("%d", &t);
    while(t--){
		scanf("%s", &a[0]);
        n = strlen(a);
        for(i = 0; i <= n; i++)    todel[i][i][0] = 0, todel[i][i][1] = 0, len[i][i][0] = 1, len[i][i][1] = 1;
        for(i = 0; i < n; i++)    todel[i + 1][i][0] = 0, todel[i + 1][i][1] = 0;
        for(i = n - 1; i >= 0; i--)    for(j = i + 1; j < n; j++)    for(k = 0; k <= 1; k++){
            todel[i][j][k] = 1000000000;
            if(k & 1){
                if(a[i] > a[j])    todel[i][j][k] = todel[i + 1][j - 1][1 - k];
                tm = todel[i + 1][j][k];
				if(todel[i][j - 1][k] < tm)    tm = todel[i][j - 1][k];
				tm++;
				if(todel[i][j][k] < tm)    tm = todel[i][j][k];
                todel[i][j][k] = tm;
                len[i][j][k] = j - i + 1 - todel[i][j][k];
            }
            else{
                if(a[i] < a[j])    todel[i][j][k] = todel[i + 1][j - 1][1 - k];
                tm = todel[i + 1][j][k];
				if(todel[i][j - 1][k] < tm)    tm = todel[i][j - 1][k];
				tm++;
				if(todel[i][j][k] < tm)    tm = todel[i][j][k];
                todel[i][j][k] = tm;
                len[i][j][k] = j - i + 1 - todel[i][j][k];
            }
        }
        if(len[0][n - 1][0] == 1){
            char cur = '{';
            for(i = 0; i < n; i++)    if(a[i] < cur)    cur = a[i];
            printf("%c\n", cur);
        }
        else{
            int hcnt = 0;
            int ans = len[0][n - 1][0], m = 0, lo = 0, hi = n - 1 , rem = ans, x, y;
            char isok = 'a';
            while(lo <= hi){
                if(len[lo][hi][m] <= 1)    break;
                x = -1;
                for(k = lo; k <= hi; k++){
                    if(a[k] == isok){
                        x = k;
                        break;
                    }
                }
                if(x == -1){
                    isok++;
                    continue;
                }
                y = -1;
                if(m & 1){
                    for(k = hi; k > x; k--){
                        if(a[k] < isok){
                            y = k;
                            break;
                        }
                    }
                }
                else{
                    for(k = hi; k > x; k--){
                        if(a[k] > isok){
                            y = k;
                            break;        
                        }       
                    }     
                }
                if(y == -1){
                    isok++;
                    continue;
                }
                if(len[x + 1][y - 1][1 - m] + 2 == rem){
                    rem -= 2;            
                    half[hcnt++] = isok;
                    isok = 'a';
                    lo = x + 1, hi = y - 1;
                    m = 1 - m;
                }
                else{
                    isok++;
                    continue;
                }
            }
            half[hcnt] = '\0';
            for(i = 0; i <= hcnt; i++)    s[i] = half[i];
            int N = strlen(s);
            for(i = lo; i <= n; i++)    sick[0][i][0] = 0, sick[0][i][1] = 0;
            for(j = 0; j <= N; j++)    sick[j][n][0] = 0, sick[j][n][1] = 0;
            for(i = 1; i <= N; i++)    for(j = n - 1; j >= lo; j--)    for(k = 0; k <= 1; k++){
                if(k & 1){
                    if(s[i - 1] > a[j])    sick[i][j][k] = 1 + sick[i - 1][j + 1][1 - k];
                    else sick[i][j][k] = sick[i][j + 1][k];     
                }          
                else{
                    if(s[i - 1] < a[j])    sick[i][j][k] = 1 + sick[i - 1][j + 1][1 - k];
                    else sick[i][j][k] = sick[i][j + 1][k];     
                } 
            }
            int scnt = 0;
            int i = strlen(s) - 1, j = lo, em = 1 - m, togo = ans - i - 1;
            int how = 0, fpos = lo, apos = lo;
            if(ans % 2)    togo--, j++, fpos++; 
            while(i >= 0 && j < n){
                if(sick[i + 1][j][em] == togo){
                    char cur = '{';
                    int pos = 0;
                    while(sick[i + 1][j][em] == togo && j < n){
                        if(em == 0){
                            if(s[i] < a[j]){
                                if(a[j] < cur){
                                    cur = a[j];
                                    pos = j;        
                                }        
                            }
                        }     
                        else{
                            if(s[i] > a[j]){
                                if(a[j] < cur){
                                    cur = a[j];
                                    pos = j;        
                                }        
                            }
                        }     
                        j++;
                    }
                    shalf[scnt++] = cur;
                    j = pos + 1;
                    how++;
                    if(how == 1)    fpos = j - 1;
                    togo--;          
                    em = 1 - em;
                    i--;
                }         
                else j++; 
            }
            shalf[scnt] = '\0';
            int mcnt = 0;
            if(ans % 2){
                char cur = '{';
                for(q = apos; q < fpos; q++){
                    if(a[q] < cur)    cur = a[q];
                }
                mhalf[mcnt++] = cur;
            }
            mhalf[mcnt] = '\0';
            printf("%s%s%s\n", half, mhalf, shalf);
        }
    }
    return 0;
}
 