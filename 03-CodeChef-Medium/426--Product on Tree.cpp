#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5+100 , mxm = 500 ;
vector<pair<int,vector<int>>> tree[mxn] ;
vector<array<int,2>>pm;
vector<int> mask;
long long  ret = 0 ;
int m , sz ;
void add(map<vector<int>,long long>pv,map<vector<int>,long long>pu){
    ret += pv[mask];
    for(auto it : pv){
        if(sz==1){
            for(int r=mask[0]-it.first[0];r<=mask[0];r++) ret += pu[{r}]*it.second;
        } else if(sz==2){
            for(int r1=mask[0]-it.first[0];r1<=mask[0];r1++){
                for(int r2=mask[1]-it.first[1];r2<=mask[1];r2++){
                    ret += pu[{r1,r2}]*it.second;
                }
            }
        }else if(sz==3){
            for(int r1=mask[0]-it.first[0];r1<=mask[0];r1++){
                for(int r2=mask[1]-it.first[1];r2<=mask[1];r2++){
                    for(int r3=mask[2]-it.first[2];r3<=mask[2];r3++){
                        ret += pu[{r1,r2,r3}]*it.second;
                    }
                }
            }
        }else{
            for(int r1=mask[0]-it.first[0];r1<=mask[0];r1++){
                for(int r2=mask[1]-it.first[1];r2<=mask[1];r2++){
                    for(int r3=mask[2]-it.first[2];r3<=mask[2];r3++){
                        for(int r4=mask[3]-it.first[3];r4<=mask[3];r4++){
                            ret += pu[{r1,r2,r3,r4}] * it.second;
                        }
                    }
                }
            }
        }
    }
}
map<vector<int>,long long> dfs(int u,int p){
    map<vector<int>,long long> pu ;
    for(auto &it : tree[u]){
        int v = it.first ;
        vector<int> weight = it.second;
        if(v==p)continue;
        map<vector<int>,long long> pv = dfs(v,u) , temp ;
        temp[weight]=1;
        for(auto it2 : pv){
            vector<int> nv = vector<int>(sz,0);
            for(int j=0;j<sz;j++) nv[j] = min( mask[j] , it2.first[j] + weight[j]);
            temp[nv]+=it2.second;
        }
        add(temp,pu);
        for(auto it2 : temp) pu[it2.first] += it2.second;
    }
    return pu ;
}
int main(){
    int n,u,v,w;
    scanf("%d%d",&n,&m);
    assert(m<=mxm);
    v=m;
    for(int d=2;d<=m;d++){
        if(v%d)continue;
        pm.push_back({d,0});
        while (v%d==0)pm.back()[1]+=1,v/=d;
    }
    sz = pm.size();
    assert(sz<=4);
    mask = vector<int>(sz,0);
    for(int i=0;i<pm.size();i++) mask[i] = pm[i][1] ;

    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        vector<int> weight(sz,0);
        for(int j=0;j<sz;j++) while (w%pm[j][0]==0 && weight[j]<pm[j][1])weight[j]++,w/=pm[j][0];
        tree[u].emplace_back(v,weight);
        tree[v].emplace_back(u,weight);
    }
    if(m==1){
        printf("%lld\n",1LL*m*(m-1));
        return 0;
    }
    dfs(1,1);
    printf("%lld\n",ret);
    return 0;
}