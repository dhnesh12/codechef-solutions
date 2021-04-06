//Bismillahir rahmanir rahim
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define debug(x) cout << #x << ": " << x << "\n";
using namespace std;

const int maxn = 200000+5;
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int r[maxn],sa[maxn],rak[maxn],height[maxn],dp[maxn][22],jump[maxn],SIGMA = 0 ;

int cmp(int *r,int a,int b,int l){return r[a] == r[b] && r[a+l] == r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for( i=0;i<m;i++) wc[i]=0;
    for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
    for( i=1;i<m;i++) wc[i] += wc[i-1];
    for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
    for( j= 1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++)y[p++] = i;
        for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i=0;i<n;i++)wv[i] = x[y[i]];
        for(i=0;i<m;i++) wc[i] = 0;
        for(i=0;i<n;i++) wc[wv[i]] ++;
        for(i=1;i<m;i++) wc[i] += wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
    }
}
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) rak[sa[i]] = i;
    for(i=0;i<n;height[rak[i++]] = k ) {
        for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
    }
}

void init(string s)
{
    int n=s.size();
    SIGMA=0;
    for(int i = 0; i < n; i ++) {
        r[i] = s[i]-'a' + 1; // change s[i] - 'a' when the constrain changes
        SIGMA = max(SIGMA, r[i]);
    }
    r[n] = 0;
    da(r,sa,n+1,SIGMA + 1); // don't forget SIGMA + 1. It will ruin you.
    calheight(r,sa,n);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        string s;
        cin >> s;
        init(s);

        int n = s.size();
        vector<int>left(n+1,0),right(n+1,n+1);

        vector<int>v;
        for(int i = 1;i <= n;i++){
            while(!v.empty() && height[v.back()] >= height[i]) {
                v.pop_back();
            }
            if(!v.empty()) left[i] = v.back();
            v.push_back(i);
        }

        v.clear();
        for(int i = n;i >= 1;i--){
            while(!v.empty() && height[v.back()] >= height[i]) {
                v.pop_back();
            }
            if(!v.empty()) right[i] = v.back();
            v.push_back(i);
        }

        vector<ll>pre(n+1);
        set<pair<int,int> >st;

        for(int i = 1;i <= n;i++){
            int range = right[i] - left[i];
            if(!st.count(make_pair(left[i],right[i]))){
                pre[range] += 1ll * range *
                (height[i] - max(height[left[i]],right[i] == n+1 ? 0 : height[right[i]]));
                st.insert(make_pair(left[i],right[i]));
            }
        }

        for(int i = n-1;i >= 2;i--){
            pre[i] += pre[i+1];
        }
        pre[1] = (1ll * n*(n+1)) / 2;

        int q;
        cin >> q;
        while(q--){
            int x;
            cin >> x;
            if(x <= n) cout << pre[x] << '\n';
            else cout << '0' << '\n';
        }
    }
    return 0;
}
