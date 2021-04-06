#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair

typedef struct dtype {
    vector< pair<int,int> > y;
    vector< pair<int,int> > n;
} dta;
int bd;

int power2(int k){
    int a=1;
    while(k--)a*=2;
    return a;
}

int bit_total(int k){
    int s=1,p=0;int as=0;
    while(p<= 1+bd){
        
        if((s&k) > 0){as++;}
        s*=2;
        p++;
    }
    return as;
}

vector< pair<int,int> > makeSum(vector< pair<int,int> > xy,vector< pair<int,int> > xn){
    vector< pair<int,int> > zz;
    pair<int,int> p;int mm=-1;
    set< pair<int,int> > st;set< pair<int,int> >::iterator it;
    int i=0,j=0;
    map<int,bool> tg;
    while(i<xy.size()){
        j=0;
        while(j<xn.size()){
            p.first = xy[i].first+xn[j].first;
            p.second = (xy[i].second|xn[j].second);
            if(mm==-1)mm = p.first;
            if(p.first >= mm+bd)break;
            st.insert(p);
            j++;
        }
        i++;
    }
    it=st.begin();
    while(it!=st.end()){
        zz.push_back((*it));it++;
    }
    st.clear();
    return zz;
}

vector< pair<int,int> > makeOne(vector< pair<int,int> > xy,vector< pair<int,int> > xn){
    vector< pair<int,int> > zz;
    pair<int,int> p;int mm=-1;
    int s=0,i=0,j=0;
        //map<int,bool> tg;
        while(1){
            if(j==xn.size())break;
            if(i==xy.size())break;
            if(xy[i].first <= xn[j].first){
                p=xy[i];i++;
            }
            else{
                p=xn[j];j++;
            }
            if(mm == -1)mm = p.first;
            if(p.first >= mm+bd){break;}
            zz.push_back(p);
            // if(!tg[p.first]){
            //     s++;tg[p.first]=true;
            // }
        }
        while(1){
            if(i<xy.size())p=xy[i],i++;
            else if(j<xn.size())p=xn[j],j++;
            else{break;}
            if(mm == -1)mm = p.first;
            if(p.first >= mm+bd)break;
            zz.push_back(p);
            // if(!tg[p.first]){
            //     s++;tg[p.first]=true;
            // }
        }
        //tg.clear();
    return zz;
}

dta cnt(int k,vector<int> tree[],int kc[]){
    int l = tree[k].size();dta xx,yy,zz;
    int f=power2(kc[k]);
    zz.n.clear();zz.y.clear();
    pair<int,int> p;
    if(l==0){
        p.first =1;p.second = f;
        zz.y.push_back(p);zz.n.push_back(mp(0,0));
    }
    else if(l==1){
        xx = cnt(tree[k][0],tree,kc);
        zz.n = xx.y;
        zz.y = makeOne(xx.y,xx.n);
        int s=0;
        while(s<zz.y.size()){
            zz.y[s].first++;zz.y[s].second = (zz.y[s].second|f);s++;
        }
    }
    else if(l==2){
        xx = cnt(tree[k][0],tree,kc);
        yy = cnt(tree[k][1],tree,kc);
        //
        zz.n = makeSum(xx.y,yy.y);
        //
        dta cv;
        cv.y = makeOne(yy.y,yy.n);
        cv.n = makeOne(xx.y,xx.n);
        //
        zz.y = makeSum(cv.y,cv.n);
        //
        int s=0;
        while(s<zz.y.size()){
            zz.y[s].first++;zz.y[s].second = (zz.y[s].second|f);s++;
        }
    }
    else {}
    xx.n.clear();xx.y.clear();yy.n.clear();yy.y.clear();
    return zz;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,k;cin>>n>>m>>k;bd=k;
        int kc[n+1],tt[k+1];int i=0;
        while(i<=k)tt[i]=0,i++;
        i=1;
        while(i<=n)cin>>kc[i],tt[kc[i]]++,i++;
        int u,v;
        i=0;vector<int> tree[n+1];
        while(i<m){
            cin>>u>>v;tree[u].push_back(v);i++;
        }
        i=1;bool exist = true;
        while(i<=k){
            if(tt[i]==0){exist=false;break;}i++;
        }
        if(!exist){cout<<-1<<endl;continue;}
        //
        //
        dta xx = cnt(1,tree,kc);
        //
        //
        xx.y = makeOne(xx.y,xx.n);
        int s=0;
        int ans=-1;
        //cout<<bd<<endl;
        while(s<xx.y.size()){
            //cout<<xx.y[s].first<<":"<<xx.y[s].second<<endl;
            //cout<<bit_total(xx.y[s].second)<<endl;
            int ab = xx.y[s].first+bd-bit_total(xx.y[s].second);
            if(ans==-1)ans=ab;
            ans=min(ab,ans);s++;
        }
        cout<<ans<<endl;
    }
    return 0;
}