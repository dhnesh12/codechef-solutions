    #include <stdio.h>
    #include <string.h>
    #define siz 160
    #define _T for(i=0; i<N; i++)

    int N, L, K, a[4*siz][siz], b[siz][siz], c[4*siz][siz];
    char d[siz][4*siz];

    void A(int k, int n)
    {
    if(k==1)
    	{
    	printf("%s",d[n]);
    	return;
    	}
    A(k-1,a[k][n]);
    printf("%s",d[n]+L-b[a[k][n]][n]);
    }

    int B(int k, int n)
    {
    int l;
    if(k==1)
    	{
    	printf("%d %d\n",n,0);
    	return 0;
    	}
    l=B(k-1,a[k][n]);
    printf("%d %d\n",n,l+b[a[k][n]][n]);
    return l+b[a[k][n]][n];
    }

    main()
    {
    int fall, i, j, k, p;
    for(scanf("%d",&fall); fall--; printf("%d\n",c[K][p]),A(K,p),puts(""),B(K,p),puts(""))
    	{
    	for(memset(b,i=p=!scanf("%d %d %d",&N,&L,&K),sizeof(b)); i<N; scanf("%s",d[i]),c[1][i++]=L);
    	_T for(j=-1; ++j<N; b[i][j]=L-b[i][j])
    		for(k=0; ++k<L; b[i][j]=(d[i][k]!=d[j][b[i][j]])?0:b[i][j],b[i][j]+=(d[i][k]==d[j][b[i][j]]));
    	for(k=2; k<=K; k++)_T
    		{
    		c[k][i]=c[k-1][0]+b[0][i];
    		a[k][i]=0;
    		for(j=1; j<N; j++)
    			if(c[k][i]>c[k-1][j]+b[j][i])
    				{
    				c[k][i]=c[k-1][j]+b[j][i];
    				a[k][i]=j;
    				}
    		}
    	for(i=-!(p=0); ++i<N; p=(c[K][i]<c[K][p])?i:p);
}
return 0;
}