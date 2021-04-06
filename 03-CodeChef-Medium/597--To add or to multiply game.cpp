#include <bits/stdc++.h>
using namespace std;
char s[1000];
int a[100005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        scanf("%d%s", &n, s);
        for(int i=1;i<=n;i++){
            scanf("%d", &a[i]);
            a[i] %= 2;
        }
        if(n == 1){
            if(a[1] == 0) printf("Chef\n");
            else printf("Chefu\n");
            continue;
        }

        if(strlen(s) == 4){
            if(n%2 == 0){
                printf("Chef\n");
            }
            else{
                int x = 0;
                for(int i=1;i<=n;i++){
                    if(a[i] == 1) 
					x++, i++;
                }
                for(int i=n;i>=2;i-=2){
                    if(x > 0) x--;
                }
                
                if(x > 0) printf("Chefu\n");
                else printf("Chef\n");
            }
        }
        else{
            if(n%2 == 1){
                printf("Chef\n");
            }
            else{
                int x = 0;
                for(int i=1;i<=n;i++){
                    if(a[i] == 1) x++, i++;
                }
                for(int i=n-1;i>=2;i-=2){
                    if(x > 0) x--;
                }
                
                if(x > 0) printf("Chefu\n");
                else printf("Chef\n");
            }
        }
    }
}   