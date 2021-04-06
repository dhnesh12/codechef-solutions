struct pre{
    int prev;
    int prevc;
};
struct rett
{
    float value;
    int min;
    int index;
};
typedef struct rett ret;
typedef struct pre pair;
int days,dishes,budgets;
int cost[51],value[51];
ret memo[22][101][51][3];
int mincost=0;
ret rec(int day,int budget,pair pre)
{
    if(day<=0)
    return (ret){0,0,0};
    else if(~(int)(memo[day][budget][pre.prev][pre.prevc].value)){
       // printf("day=%d,budget=%d,pre.prevc=%d,pre.pre=%d\n",day,budget,pre.prevc,pre.prev);
        return memo[day][budget][pre.prev][pre.prevc];
    }
    else{
        int i,index=-1,Min=10000;
        float max=-1.0,val=0.0;
        ret tem;
        pair temp;
        for(i=1;i<=dishes;i++){
            if(pre.prev==i){
                if(pre.prevc==0){
                val=value[i];
                temp.prevc=(pre.prevc+1);
                }
                else if(pre.prevc==1){
                val=((float)value[i])/2.0;
                temp.prevc=(pre.prevc+1);}
                else if(pre.prevc>1){
                val=0;temp.prevc=2;}
                temp.prev=i;
            }
            else{
                val=value[i];
                temp=(pair){i,1};
            }
            //printf("day=%d i=%d val=%f\n",day,i,val);
            if(budget-cost[i]<0) continue;
            else{
                tem=rec(day-1,budget-cost[i],temp);
                if(tem.value>=0){
                    if(max<(val+tem.value))
                    {
                        max=val+tem.value;
                        Min=cost[i]+tem.min;
                        index=i;
                    }
                   else if(max==(val+tem.value))
                    {
                        if(tem.min+cost[i]<Min){
                            Min=tem.min+cost[i];
                            index=i;
                        }
                    }
                }
            }
            //printf("day=%d i=%d max=%f tem=%f,%d,temp.prev=%d temp.prevc=%d\n",day,i,max,tem.value,Min,temp.prev,temp.prevc);
        }
        //printf("For day=%d index=%d max=%f budget=%d mincost=%d pre.prev=%d,pre.prevc=%d\n",day,index,max,budget,Min,pre.prev,pre.prevc);
        if(index==-1) max=-10;
        memo[day][budget][pre.prev][pre.prevc]=(ret){max,(Min==10000?-100:Min),index};
        //mincost=budget-cost[index];
        return (ret){max,(Min==10000?-100:Min),index};
    }
}
int main(){
    int i,j,k,pp,m,n;
    while(scanf("%d%d%d",&days,&dishes,&budgets),days){
        for(i=1;i<=dishes;i++){
            scanf("%d%d",&cost[i],&value[i]);
            //(cost[i])<<=1;
        }
        for(i=1;i<=days;i++) for(j=0;j<=budgets;j++) for(k=0;k<=dishes;k++){
        memo[i][j][k][0]=(ret){-1,0,0};
        memo[i][j][k][1]=(ret){-1,0,0};
        memo[i][j][k][2]=(ret){-1,0,0};
        }
        ret res=rec(days,budgets,(pair){0,0});
        if(res.value<0)
        printf("0.0\n");
        else{
            printf("%.1f\n",res.value);
            pp=days;
            while(pp>0){
                printf("%d ",res.index);
                if(pp==days){ m=res.index;n=1; }
                else{
                    if(res.index==m){ n++; if(n>2) n=2;}
                    else{ m=res.index;n=1; }
                }
                res=memo[pp-1][budgets-=cost[res.index]][m][n];
                pp--;
            }
            printf("\n");
        }
        //printf("%f %f %f\n",memo)
    }
    return 0;
}
 