#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<bitset>
const int INF=0x3f3f3f3f;
using namespace std;
#define N 100005
int arr[N<<2];
long long int tree1[N<<2];
long long int minn[N<<2];
void readin(int n){
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
}
void update(int node){
    tree1[node]=tree1[node<<1]|tree1[(node<<1)+1];//返回可改变的二进制位数上有1的数
    minn[node]=min(minn[node<<1],minn[(node<<1)+1]);
    return;
}
void build_tree(int node,int sta,int end){
    if(sta==end){
        tree1[node]=arr[sta];
        minn[node]=arr[sta];
        return;
    }
    int mid=(sta+end)>>1;
    build_tree(node<<1,sta,mid);
    build_tree((node<<1)+1,mid+1,end);
    update(node);
}
void add(int node,int sta,int end,int l,int r,int x){
    int mid=(sta+end)>>1;
    if(l<=sta&&r>=end){
        if(tree1[node]==(tree1[node]&x)){//如果没变化
            return;
        }
        if(sta==end){
            minn[node]&=x;
            tree1[node]&=x;
            return;
        }
        add(node<<1,sta,mid,l,r,x);
        add((node<<1)+1,mid+1,end,l,r,x);
        update(node);
        return;
    }
    if(l<=mid){
        add(node<<1,sta,mid,l,r,x);
    }
    if(r>mid){
        add((node<<1)+1,mid+1,end,l,r,x);
    }
    update(node);
    return;
}
long long int querry(int node,int sta,int end,int l,int r){
    int mid=(sta+end)>>1;
    long long int minnn=INF;
    if(l<=sta&&r>=end){
        return minn[node];
    }
    if(l<=mid){
        minnn=min(minnn,querry(node<<1,sta,mid,l,r));
    }
    if(r>mid){
        minnn=min(minnn,querry((node<<1)+1,mid+1,end,l,r));
    }
    return minnn;
}
int main(){
    int n,q;scanf("%d %d",&n,&q);
    readin(n);
    for(int i=1;i<=(N<<2)-2;i++){
        minn[i]=INF;
    }
    build_tree(1,1,n);
    while(q--){
        int c;scanf("%d",&c);
        if(c){
            int l,r,x;scanf("%d %d %d",&l,&r,&x);
            add(1,1,n,l,r,x);
        }
        else{
            int l,r;scanf("%d %d",&l,&r);
            printf("%lld\n",querry(1,1,n,l,r));
        }
    }
    return 0;
}