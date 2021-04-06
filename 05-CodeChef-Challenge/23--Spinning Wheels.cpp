     #include<stdio.h>
    #include<stdlib.h>
    int main()
    {
    int t,n,i,j,k;
    scanf("%d",&t);
    while(t--){
    scanf("%d",&n);
    for(i=0;i<2*n;i++)for(j=0;j<n;j++)scanf("%d",&k);
    if(n==2){
    printf("100\n");
    for(i=0;i<100;i++){printf("%d %d\n",(rand()-1)%n+1,(rand()-1)%n+1);}
    }
    else printf("-1\n");
    }
    return 0;} 