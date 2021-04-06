#include <bits/stdc++.h>
using namespace std;

long double dist(long long x1,long long y1,long long x2, long long y2){
    long double ans= sqrt(1ll*(x1-x2)*(x1-x2)+ 1ll*(y1-y2)*(y1-y2));
    return ans;
}

int main() {
    long long t,n,m,k,i,j,x,y;
    cin>>t;
    while (t--){
        cin>>x>>y;
        cin>>n>>m>>k;
        long long a[n],b[n],c[m],d[m],e[k],f[k];
        for (i=0;i<n;i++){
            cin>>a[i];
            cin>>b[i];
        }
        for (i=0;i<m;i++){
            cin>>c[i];
            cin>>d[i];
        }
        for (i=0;i<k;i++){
            cin>>e[i];
            cin>>f[i];
        }
        long double best[m],best1[n];
        
        for (i=0;i<m;i++){
            best[i]=1e18;
            for (j=0;j<k;j++){
                best[i]=min(best[i],dist(c[i],d[i],e[j],f[j]));
            }
        }
        
        for (i=0;i<n;i++){
            best1[i]=1e18;
            for (j=0;j<k;j++){
                best1[i]=min(best1[i],dist(a[i],b[i],e[j],f[j]));
            }
        }
        
        long double ans=1e18;
        for (i=0;i<n;i++){
            for (j=0;j<m;j++){
                ans=min(ans,dist(x,y,a[i],b[i])+dist(a[i],b[i],c[j],d[j])+best[j]);
                
            }
        }
        
        for (j=0;j<n;j++){
            for (i=0;i<m;i++){
                ans=min(ans,dist(x,y,c[i],d[i])+dist(a[j],b[j],c[i],d[i])+best1[j]);
            }
        }
        
        cout<<fixed<<setprecision(7)<<ans<<endl;
    }
	// your code goes here
	return 0;
}
