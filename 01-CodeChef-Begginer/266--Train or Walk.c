#include<stdio.h>
int mod(int x,int y){
    if(x>y)return x-y;
    else return y-x;
}

int main(){
    int t;
    scanf("%d",&t);
    int n,a,b,c,d,p,q,y;
    for(int i=0;i<t;i++){
        scanf("%d %d %d %d %d %d %d %d",&n,&a,&b,&c,&d,&p,&q,&y);
        int arr[n];
        for(int j=0;j<n;j++){
            scanf("%d",&arr[j]);
        }
        if(y<mod(arr[a-1],arr[c-1])*p){
            printf("%d\n",p*mod(arr[a-1],arr[b-1]));
            continue;
        }
        int t1=mod(arr[a-1],arr[b-1])*p;
        int t2=y+mod(arr[c-1],arr[d-1])*q+mod(arr[d-1],arr[b-1])*p;
        if(t1<t2)printf("%d\n",t1);
        else printf("%d\n",t2);
    }
    return 0;
}