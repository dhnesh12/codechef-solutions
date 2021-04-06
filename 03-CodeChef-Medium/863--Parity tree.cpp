#include<bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent,xorr;
    long long pow;
    DSU(int n){
        parent.resize(n,-1);
        xorr.resize(n,0);
        pow=n-1;
    }

    int find(int n){
        if(parent[n]<0)
            return n;
        int pno=find(parent[n]);
        xorr[n]^=xorr[parent[n]];
        parent[n]=pno;
        return pno;
    }

    int join(int a, int b, int w){
        int ap=find(a);
        int bp=find(b);
        int tmp=xorr[a]^xorr[b]^w;
        if(ap==bp)
            return tmp;
        this->pow--;
        if(parent[ap]<parent[bp]){
            parent[ap]+=parent[bp];
            parent[bp]=ap;
            xorr[bp]=tmp;
        }else{
            parent[bp]+=parent[ap];
            parent[ap]=bp;
            xorr[ap]=tmp;
        }
        return 0;
    }

};

int fastexpo(long long a,long long pow){
    long long ans=1, mod=1000000007;
    while(pow>0){
        if(pow&1)
            ans=(ans*a)%mod;
        pow=pow>>1;
        a=(a*a)%mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t,n,q,t1,t2,w;
    cin >> t;
    bool found;
    while (t--) {
        found=true;
        cin>>n>>q;
        DSU ds(n);
        for(int i=0;i<n-1;i++)
            cin>>t1>>t2;
        for(int i=0;i<q;i++){
            cin>>t1>>t2>>w;
            if(ds.join(t1-1,t2-1,w))
                found=false;
        }
        if(found)
            cout<<fastexpo(2,ds.pow)<<endl;
        else
            cout<<0<<endl;
    }
}