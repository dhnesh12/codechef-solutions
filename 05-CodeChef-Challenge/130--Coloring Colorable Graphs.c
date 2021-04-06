#include <stdio.h>
#include <string.h>

int main() {
	int t,n,m,i=0,j=0,z=0,p,set[501][501],rindx[500],rnds[500];
    scanf("%d",&t);
    while(t--) {
    	int p1,p2; scanf("%d%d",&n,&p);
        for(i=1;i<=n;++i) {
        	for(j=1;j<=n;set[i][j++]=0);
			rindx[i]=0,rnds[i]=0;
        } for(i=1;i<=p;++i) {
        	scanf("%d%d",&p1,&p2);
            set[p1][p2]=1,set[p2][p1]=1;
        } for(i=1;i<=n;++i) {
        	for(z=1;z<=n;rindx[z++]=0);
            for(z=1;z<=n;++z) {
            	if((rnds[z]!=0)&&(set[i][z]==1)) {
            		rindx[rnds[z]]++;
            	}
            } for(j=1;((j<=n)&&(j<=i));++j) {
            	if((set[i][j]==1)&&(rnds[i]==rnds[j])||(!rnds[i])) {
            		while(rindx[++rnds[i]]!=0);
            	} else if((!set[i][j])&&(!rnds[i]))rnds[i]=1;
            }
        } for(i=1;i<=n;printf("%d ",rnds[i++]));puts("");
    } return(0);
}


