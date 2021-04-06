#include<iostream>
#include<vector>
#include<map>
using namespace std;

vector<vector<long long>> da_ta;
vector<vector<pair<long long,long long>>> printthis;
void abbi(vector<long long> arr);
void print(vector<pair<long long,long long>> arr);
void ddgty(vector<vector<pair<long long,long long>>> arr);
void printda_ta();
void vbg77(long long i,long long j);
void bnh7(long long i,long long j,vector<long long> dl);
void nhm89(long long i,long long j);
bool mjk90(int i,int j);

int main()
{
    int n,m,a,r;
    cin>>n>>m>>a>>r;
    da_ta.resize(n+1);
    int am=m;while(am--){
        int x,y;scanf("%d %d",&x,&y);
        da_ta[x].push_back(y);da_ta[y].push_back(x);
    }
    for(int i=1;i<=n-1;i++){
        for(int j=i+1;j<=n;j++){
            if(mjk90(i,j)){
                nhm89(i,j);}}
    }
    int b=909598,c;
    while(b){
        b--;
    }
   
    for(int i=1;i<=n-1;i++){
        for(int j=i+1;j<=n;j++){
            if(mjk90(i,j)){
                vbg77(i,j);
                
                vector<pair<long long,long long>> a;
                a.push_back(pair<long long,long long>(i,j));
                printthis.push_back(a);
            }
        }
    }
    ddgty(printthis);
    return 0;
}
void abbi(vector<long long> arr){for(auto i:arr){printf("%lld ",i);}cout<<endl;}
void vbg77(long long i,long long j){
    for(auto it=da_ta[i].begin();it!=da_ta[i].end();it++){
        if(*it==j){
            da_ta[i].erase(it);
            break;
        }
    }
    for(auto it=da_ta[j].begin();it!=da_ta[j].end();it++){
        if(*it==i){
            da_ta[j].erase(it);
            break;
        }
    }
}
void print(vector<pair<long long,long long>> arr){for(auto i:arr){printf("%lld %lld ",i.first,i.second);}cout<<endl;}
void printda_ta(){
    for(auto i:da_ta){
        abbi(i);
    }
}
bool mjk90(int i,int j){
    for(auto a:da_ta[i]){
        if(a==j){return true;}
    }
    return false;
}
void nhm89(long long i,long long j){
    map<long long,long long> mp;
    vector<long long> dl;
    for(auto a:da_ta[i]){mp[a]++;}
    for(auto a:da_ta[j]){
        mp[a]++;
        if(mp[a]>1){
            dl.push_back(a);
        }
    }
    bnh7(i,j,dl);
}
void bnh7(long long i,long long j,vector<long long> dl){
    long long sz=dl.size();
    if(!sz)return;
    vector<pair<long long,long long>> q;
    while(sz>1){
        int x=dl[0],y=dl[1];
        dl.erase(dl.begin());
        dl.erase(dl.begin());
        q.push_back(pair<long long,long long>(i,j));
        q.push_back(pair<long long,long long>(i,y));
        vbg77(i,y);
        vbg77(j,y);
        q.push_back(pair<long long,long long>(j,x));
        vbg77(j,x);
        vbg77(i,x);
        printthis.push_back(q);
        q.clear();
        sz=dl.size();
    }
    if(sz==1){
        q.push_back(pair<long long,long long>(i,j));
        q.push_back(pair<long long,long long>(i,dl[0]));
        vbg77(i,dl[0]);
        vbg77(j,dl[0]);
        printthis.push_back(q);
    }
    vbg77(i,j);
}
void ddgty(vector<vector<pair<long long,long long>>> arr){
    
    cout<<arr.size()<<endl;
    for(auto i:arr){
        
        cout<<"1 "<<i.size()<<" ";
        print(i);
    }
}
