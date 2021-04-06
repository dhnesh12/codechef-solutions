#include "bits/stdc++.h"
#define ll long long
using namespace std;

double apms=0;

bool comp(vector<int>& a, vector<int>& b){
    return a[2]<b[2];
}

class DSU{
public:
    vector<int> parent;
    DSU(int n){
        parent.resize(n,-1);
    }
    int find(int n){
        if(parent[n]<0)
            return n;
        parent[n]=find(parent[n]);
        return parent[n];
    }
    void join(int a, int b, int w){
        a=find(a);
        b=find(b);
        double t1,t2,t3;
        t1=parent[a];
        t2=parent[b];
        t3=w;
        apms+=(t1*t2*t3);
        if(a==b)return;
        if(parent[a]<parent[b]){
            parent[a]+=parent[b];
            parent[b]=a;
        }else{
            parent[b]+=parent[a];
            parent[a]=b;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<vector<int>> a;
    for(int i=0;i<n-1;i++){
        vector<int>temp(3);
        cin>>temp[0]>>temp[1]>>temp[2];
        temp[0]--;
        temp[1]--;
        a.push_back(temp);
    }
    sort(a.begin(),a.end(),comp);
    DSU ds(n);
    double totalweight=0;
    for(int i=0;i<n-1;i++){
        ds.join(a[i][0],a[i][1],a[i][2]);
        totalweight+=a[i][2];
    }
    double div=n;
    div*=(n-1);
    div/=2.0;
    cout<<fixed<<setprecision(6)<<totalweight-(apms/div)<<endl;
}