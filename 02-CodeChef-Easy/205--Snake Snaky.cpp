#include <stdio.h>
    #include <string.h>
    #define siz 1010
     
    main()
    {
    int fall, M, N, y, i, tx, ty, L, x, m, hy, hx;
    char w, B[siz][siz], z[siz*siz+siz];
     
    for(scanf("%d",&fall); fall--; printf(" %d\n",m))
    	{
    	scanf("%d %d %d %d %d %s",&N,&M,&tx,&ty,&L,z);
    	for(y=0; y<M; memset(B[y++],'.',(N)*sizeof(char)));
    	for(B[hy=--ty][hx=--tx]='#'+(i=0); i<L-1; ++i)
    		{
    		hy+=(z[i]=='U')-(z[i]=='D');
    		hx+=(z[i]=='R')-(z[i]=='L');
    		B[hy][hx]='#';
    		}
    	for(w=z[L-2*!(m=0)]; m<1001; B[hy][hx]='#',m++)
    		{
    		B[ty][tx]=' ';
    		ty+=(z[m]=='U')-(z[m]=='D');
    		tx+=(z[m]=='R')-(z[m]=='L');
    		z[L+m]=w;
    		hy+=(w=='U')-(w=='D');
    		hx+=(w=='R')-(w=='L');
    		if(hy<0||hy>=M||hx<0||hx>=N)
    			{
    			printf("WALL");
    			break;
    			}
    		if(B[hy][hx]=='#')
    			{
    			printf("BODY");
    			break;
    			}
    		}
    	}
     
    return 0;
    }   
