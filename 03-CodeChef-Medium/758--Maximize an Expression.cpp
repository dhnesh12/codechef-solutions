#include <bits/stdc++.h>
using namespace std;

double k[1000001];
double c[1000001];
double x[1000001];

int main(){

    int t;
    scanf("%d", &t);

    while(t--){

        int n;
        scanf("%d", &n);

        for(int i=0;i<n;i++){
            scanf("%lf", &k[i]);
        }

        
        for(int i=0;i<n;i++){
            scanf("%lf", &c[i]);
        }

        double A = (double)0.0;
        for(int i=0;i<n;i++){
            
            A += k[i]*c[i];
        }

        double B = 0;
        for(int i=0;i<n;i++){
            
            B += (double)(1.0)/k[i];
        }

        if(A*B < (double)0.0){
            
            printf("-1\n");
            
        }else{

            for(int i=0;i<n;i++){

                x[i] = A/B;
                x[i] /= (k[i]*k[i]);
                x[i] -= c[i];
            }
        

            double ans = (double)0.0;

            for(int i=0;i<n;i++){

                ans += sqrt(x[i]+c[i]);
            }

            printf("%lf ", ans);

            for(int i=0;i<n;i++){

                printf("%lf ", x[i]);
            }

            printf("\n");
        }
    }

    return 0;
}