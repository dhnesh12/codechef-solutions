#include<bits/stdc++.h>
using namespace std;
vector<long long> adj[11];
long long ss[16], mm[16], mns[16], auxm[16], sss[16];

int main(){//can also add before :(
    adj[0] = {0, 8};
    adj[1] = {0, 1, 3, 4, 7, 8, 9};
    adj[2] = {2, 8};
    adj[3] = {3, 8, 9};
    adj[4] = {4, 8, 9};
    adj[5] = {5, 6, 8, 9};
    adj[6] = {6, 8};
    adj[7] = {0, 3, 7, 8, 9};
    adj[8] = {8};
    adj[9] = {8, 9};
    adj[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int tc; scanf("%d", &tc);
    while(tc--){
        long long s,m; scanf("%lld %lld", &s, &m);
        if(m==0){cout<<"0"<<endl; continue;}
        
        for(long long i=0; i<15; i++){
            ss[i]=0; mm[i]=0; sss[i]=0;
            auxm[i] = 0; mns[i] = 0;
        }
        long long js=0, cs=s;
        while(cs > 0){
            sss[js] = cs%10LL; cs = cs/10LL; js++;
        }
        if(s==0)js++;
        
        long long jm = 0, cm=m, ptm=1;
        while(cm > 0){
            ptm = ptm*10;
            auxm[jm] = m%ptm;
            mm[jm] = cm%10LL; cm = cm/10LL; jm++;
        }
        for(int yy=jm; yy<15; yy++)auxm[yy] = auxm[jm-1];

        long long ans = 0;

        for(int beg=0; beg+js-1<15; beg++){//where s begins

            for(int yy=0; yy<beg; yy++)ss[yy]=10;//so we can add digits before
            for(int yy=beg; yy<=beg+js-1; yy++)ss[yy] = sss[yy - beg];
            for(int yy=beg+js; yy<15; yy++)ss[yy] = 10;//and after

            long long pt1=1, fmm=0;
            for(long long i=0; i<15; i++){
               mns[i] = adj[ss[i]][0];//smallest possible outcome
               fmm += pt1*mns[i]; pt1 = pt1*10;
            }
            if(fmm > m)continue;
            
            //cout<<endl;
            bool already_smaller = false, ok=true, allz=true;
            for(long long i = 14; i>=0; i--){
                long long cur = ss[i];
                long long j = adj[cur].size() - 1;
                if(already_smaller){ss[i] = adj[cur][j];continue;}
                bool flag = true;
                while(flag){
                    long long cand = adj[cur][j];//can i use cand?
                    long long aux = 0, pt=1;
                    for(long long jj=0; jj<i; jj++){
                        aux += pt*mns[jj]; pt = pt*10;
                    }
                    aux += pt*cand;
                    if(aux <= auxm[i])flag = false;
                    else j--;
                }
                //cout<<"POSITION "<<i<<" gets "<<adj[cur][j]<<endl;
                if(i>=beg && i<=beg+js-1 && adj[cur][j]==0 && allz){ok=false;break;}
                ss[i] = adj[cur][j];
                if(ss[i]!=0)allz=false;
                if(ss[i] < mm[i])already_smaller = true;
            }
            long long pt2=1, fm=0;
            for(long long i=0; i<15; i++){
               fm += pt2*ss[i]; pt2 = pt2*10;
            }
            if(fm <= m && ok)ans = max(ans, fm);
        }
        printf("%lld\n", ans);
    }
}