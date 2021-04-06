#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,m,T,a[N],b[N],c[N],d[N];
inline int lowbit(int x){return x&-x;}
inline void add(int x,int y){for(int i=x;i<N;i+=lowbit(i))c[i]+=y;}
inline int sum(int x){int ans=0;for(int i=x;i;i-=lowbit(i))ans+=c[i];return ans;}

long long readInt(long long l,long long r,char endd){
    long long x=0;
    int cnt=0;
    int fi=-1;
    bool is_neg=false;
    while(true){
        char g=getchar();
        if(g=='-'){
            assert(fi==-1);
            is_neg=true;
            continue;
        }
        if('0'<=g && g<='9'){
            x*=10;
            x+=g-'0';
            if(cnt==0){
                fi=g-'0';
            }
            cnt++;
            assert(fi!=0 || cnt==1);
            assert(fi!=0 || is_neg==false);
           
            assert(!(cnt>19 || ( cnt==19 && fi>1) ));
        } else if(g==endd){
            if(is_neg){
                x= -x;
            }
            assert(l<=x && x<=r);
            return x;
        } else {
            if((int)g==13)
                continue;
            assert(false);
        }
    }
}
string readString(int l,int r,char endd){
    string ret="";
    int cnt=0;
    while(true){
        char g=getchar();
        assert(g!=-1);
        if(g==endd){
            break;
        }
        cnt++;
        ret+=g;
    }
    assert(l<=cnt && cnt<=r);
    return ret;
}
long long readIntSp(long long l,long long r){
    return readInt(l,r,' ');
}
long long readIntLn(long long l,long long r){
    return readInt(l,r,'\n');
}
string readStringLn(int l,int r){
    return readString(l,r,'\n');
}
string readStringSp(int l,int r){
    return readString(l,r,' ');
}

int main(){
	T = readIntLn(1,7);
	while (T--){
	    n=readIntSp(1,100000);
	    m=readIntLn(1,100000);
	    memset(c,0,sizeof(c));
	    for(int i=0;i<n;i++)
	        if(i+1<n)
	            a[i+1] = readIntSp(1,100000);
	       else
	            a[i+1] = readIntLn(1,100000);
	            
	    for(int i=0;i<m;i++)
	        if(i+1<m)
	            b[i+1] = readIntSp(1,100000);
	       else
	            b[i+1] = readIntLn(1,100000);
		long double aa=0;memset(d,0,sizeof(d));
		for (int i=1;i<=n;i++){
			aa=aa+1.0*(sum(N-1)-sum(a[i]));
			add(a[i],1);
		}
		long double bb=0;
		for (int i=1;i<=m;i++) d[b[i]]++;
		for (int i=1;i<N;i++) if (d[i]) bb+=1.0*d[i]*(m-d[i]);bb=bb/4.0;
		for (int i=1;i<N;i++) d[i]+=d[i-1];
		long double ab=0;
		for (int i=1;i<=n;i++){
			ab+=1.0*(n-i+1)*(d[a[i]-1]);
			ab+=1.0*i*(m-d[a[i]]);
		}
		ab/=(long double)(n+1);
		printf("%.15Lf\n",ab+aa+bb);
	}
	 assert(getchar()==-1);
	return 0;
}