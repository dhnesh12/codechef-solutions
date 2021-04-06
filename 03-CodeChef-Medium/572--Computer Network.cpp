#include<bits/stdc++.h>
using namespace std;
int main(){
    int tc; scanf("%d", &tc);
    while(tc--){
        int n,m; scanf("%d %d", &n, &m);
        if(n<=2){//special case
            printf("-1 -1\n");
        }else{
            if(m < n || (n!=3 && m > 2*n - 4)){
                printf("-1 -1\n");
            }else{
                int i = 2*n - m - 1;//special internal nodes are 1 and i
                for(int j=1; j<i; j++)printf("%d %d\n", j, j+1);
                for(int j=i+1; j<=n; j++){
                    printf("1 %d\n", j);
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
}