#include "bits/stdc++.h"
using namespace std;

class DSU{
public:
    vector<int> parent,xorr;
    DSU(int n){
        parent.resize(n,-1);
        xorr.resize(n,0);
    }
    int find(int n){
        if(parent[n]<0)
            return n;
        int tmp=find(parent[n]);
        xorr[n]^=xorr[parent[n]];
        parent[n]=tmp;
        return tmp;
    }
    int join(int a, int b, int w){
        int ap=find(a);
        int bp=find(b);
        if(ap==bp)
            return xorr[a]^xorr[b]^w;
        if(parent[ap]<parent[bp]){
            parent[ap]+=parent[bp];
            parent[bp]=ap;
            xorr[bp]=xorr[a]^xorr[b]^w;
        }else{
            parent[bp]+=parent[ap];
            parent[ap]=bp;
            xorr[ap]=xorr[a]^xorr[b]^w;
        }
        return 0;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t,n,q,t1,t2,w;
    cin>>t;
    bool ans;
    while(t--){
        cin>>n>>q;
        ans=true;
        DSU ds(n);
        for(int i=0;i<q;i++){
            cin>>t1>>t2>>w;
            t1--;
            t2--;
            if(ds.join(t1,t2,w))
                ans=false;
        }
        if(ans)
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }
}