     #include<stdio.h>
    int main(){
    int n,m,k,i,j,l,p,q;
    int a[101][101],b[100][3];
    scanf("%d%d%d",&n,&m,&k);
    for(i=0;i<n;i++){
    for(j=0;j<m;j++){
    a[i][j]=0;
    }
    }
    for(i=0;i<k;i++){
    scanf("%d%d",&q,&l);
    q=q-1;
    l=l-1;
    a[q][l]=-1;
    }
    p=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++){
            if(a[i][j]==0){
                b[p][0]=i+1;
                b[p][1]=j+1;
                b[p][2]=1;
                p++;
                for(l=i;l<n;l++){
                    if(a[l][j]==-1){
                        break;
                    }
                    a[l][j]=1;
                }
            }
        }
    }
    printf("%d\n",p);
    for(i=0;i<p;i++){
    printf("%d %d %d\n",b[i][0],b[i][1],b[i][2]);
    }
    }


