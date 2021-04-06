#include<cstdio>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cstdlib>
#include<cmath>
#include<string>

using namespace std;

#define REP(n)                  for(int i=0;i<n;i++)
#define s(n)					scanf("%d",&n)
#define sl(n) 					scanf("%lld",&n)
#define sf(n) 					scanf("%lf",&n)
#define ss(n) 					scanf("%s",n)
#define sc(n)                   {char temp[4]; ss(temp); n=temp[0];}
#define INF						(int)1e9
#define LINF					(long long)1e18
#define EPS						1e-9
#define maX(a,b)				((a)>(b)?(a):(b))
#define miN(a,b)				((a)<(b)?(a):(b))
#define abS(x)					((x)<0?-(x):(x))
#define foreach(v,c)            for( typeof((c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define mp						make_pair
#define FF						first
#define SS						second
#define tri(a,b,c)				mp(a,mp(b,c))
#define XX						first
#define YY						second.first
#define ZZ						second.second
#define pb						push_back
#define fill(a,v) 				memset(a,v,sizeof a)
#define all(x)					x.begin(),x.end()
#define SZ(v)					((int)(v.size()))
#define DREP(a)					sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)			(lower_bound(all(arr),ind)-arr.begin())


#define debugger cerr
#define debug(args...)			{mdbg,args; debugger<<endl;}
#define PRINT_CONTAINER(o,v)    {if(v.size()==0) return o<<"{}"; o<<"{"; foreach(it,v) o<<*it<<" "; return o<<"\b}";}
struct multidebug {template<typename T> multidebug& operator , (const T &v) {debugger<<v<<" "; return *this;}} mdbg;
template<class T> ostream& operator << (ostream& o,const vector<T> &v) PRINT_CONTAINER(o,v)
template<class T> ostream& operator << (ostream& o,const set<T> &v) PRINT_CONTAINER(o,v)
template<class A,class B> ostream& operator << (ostream& o,const map<A,B> &v) PRINT_CONTAINER(o,v)
template<class A,class B> ostream& operator << (ostream& o,const pair<A,B> &p) {o<<"("<<p.first<<","<<p.second<<")"; return o;}
template<class T> void debugarr(T* v,int n) {debugger<<"{"; for(int i=0;i<n;i++) debugger<<v[i]<<" "; debugger<<"\b}"<<endl;}


typedef unsigned long long LL;
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<int,PII> TRI;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<ll> vl;
typedef vector<PII> VII;
typedef vector<TRI> VT;

/*Main code begins now */

vector<int> arr[100005];
vector<int> cap;
int k;
int order[100005];
ll sums[100005];
int ma[100005],stma[100005];
bool taken[100005];

bool inSort(int i,int j){
	return cap[i]<cap[j];
}

bool stcmp(int i,int j){
	for(int ind=0;ind<k;ind++){
		int idx=order[ind];
		if(arr[i][idx]!=arr[j][idx]) return arr[i][idx]<arr[j][idx];
	}
	return true;
}

bool smcmp(int i,int j){
	return sums[i]<sums[j];
}

bool canFit(vector<int>a,vector<int>b){
	for(int i=0;i<k;i++) if(a[i]<b[i]) return false;
	return true;
}

void add(vector<int>b){
	for(int i=0;i<k;i++) cap[i]+=b[i];
}

void del(vector<int>b){
	for(int i=0;i<k;i++) cap[i]-=b[i];
}

typedef pair<int,vector<int> > RES;

int main(){
	int t;
	s(t);
	while(t--){
		int n;
		scanf("%d%d",&n,&k);

		for(int i=0;i<100005;i++) arr[i].clear();
		for(int i=0;i<n;i++){
			taken[i]=false;
			sums[i]=0;
			for(int j=0;j<k;j++){
				int r;
				s(r);
				sums[i]+=r;
				arr[i].pb(r);
			}
		}
		cap.clear();
		vector<int> backup;
		ll caps=0;
		for(int j=0;j<k;j++){
			int r;
			s(r);
			caps+=r;
			cap.pb(r);
			backup.pb(r);
		}



		if(n<9) {
			vector<int> chosen;
			double val=0;
			for(int mask=0;mask<(1<<n);mask++){
				int q=0;
				ll sum=0;
				int ok=1;
				vector<int>save(cap);
				vector<int>select;
				for(int j=0;j<n;j++){
					if(mask&(1<<j)){
						q++;
						sum+=sums[j];
						for(int i=0;i<k;i++){
							save[i]-=arr[j][i];
						}
						select.pb(j);
					}
				}
				for(int i=0;i<k;i++) if(save[i]<0) continue;
				double tis=((double)q)/(1+caps-sum);
		        if(tis-val>EPS)	{
		        	val=tis;
		        	chosen.swap(select);
		        }
			}
			printf("%d\n",chosen.size());
			foreach(v,chosen) printf("%d ",*v+1);
			if(chosen.size()>0) printf("\n");
			continue;
		}






		for(int i=0;i<n;i++) {
			order[i]=i;
			ma[i]=i;
			stma[i]=i;
		}
		sort(order,order+k,inSort);
		sort(ma,ma+n,smcmp);
		sort(stma,stma+n,stcmp);

		//debugarr(stma,n);

		int oq=0;

		for(int i=0;i<n;i++){
			if(canFit(cap,arr[stma[i]])){
				del(arr[stma[i]]);
				taken[stma[i]]=true;
				oq++;
			}
		}
		/*printf("%d\n",oq);
		for(int i=0;i<n;i++){
			if(taken[i]) printf("%d ",i+1);
		}
		if(oq>0) printf("\n");
		continue;*/

		int j = n - 1;
        int last = n - 1;

        while (j >= 0) {
            if (!taken[ma[j]]) {
                last = min(last, j);
                while (last >= 0 && !taken[ma[last]]) last--;
                if (last < 0) break;
                add(arr[ma[last]]);
                taken[ma[last]] = false;
                oq--;
                while (j >= last) {
                    if (canFit(cap,arr[ma[j]])) {
                        taken[ma[j]] = true;
                        del(arr[ma[j]]);
                        oq++;
                        break;
                    }
                    j--;
                }
            }
            j--;
        }
        vector<int> chosen;
        ll sum=0;
        for(int i=0;i<n;i++){
			if(taken[i]) {
				chosen.pb(i);
				sum+=sums[i];
			}
		}

        pair<int,vector<int> > ans=mp(oq,chosen);

        double val=((double)oq)/(1+caps-sum);
		int q=oq;
		for(int ii=1;ii<6;ii+=2){
			if(chosen.empty()) break;
			int j = n - 1;
	        int last = n - 1;

	        while (last >= 0 && !taken[ma[last]]) last--;
            if (last < 0) break;
            add(arr[ma[last]]);
            taken[ma[last]] = false;
            q--;

	        while (j >= 0) {
	            if (!taken[ma[j]]) {
	                last = min(last, j);
	                while (last >= 0 && !taken[ma[last]]) last--;
	                if (last < 0) break;
	                add(arr[ma[last]]);
	                taken[ma[last]] = false;
	                q--;
	                while (j >= last) {
	                    if (canFit(cap,arr[ma[j]])) {
	                        taken[ma[j]] = true;
	                        del(arr[ma[j]]);
	                        q++;
	                        break;
	                    }
	                    j--;
	                }
	            }
	            j--;
	        }
	        vector<int> rival;
	        ll sum=0;
	        for(int i=0;i<n;i++){
				if(taken[i]) {
					rival.pb(i);
					sum+=sums[i];
				}
			}

	        double tis=((double)q)/(1+caps-sum);
	        if(tis-val>EPS)	{
	        	val=tis;
	        	ans=mp(q,rival);
	        }
		}
        q=0;
        sum=0;
        vector<int> rival;
        for(int j=n-1;j>=0;j--){
        	if(canFit(backup,arr[ma[j]])){
        		for(int ii=0;ii<k;ii++)
        			backup[ii]+=arr[ma[j]][ii];
        		q++;
        		sum+=sums[ma[j]];
        		rival.pb(ma[j]);
        	}
        }
        sort(rival.begin(),rival.end());

        double tis=((double)q)/(1+caps-sum);
        if(tis-val>EPS)	{
        	val=tis;
        	ans=mp(q,rival);
        }

		printf("%d\n",ans.FF);
		foreach(v,ans.SS){
			printf("%d ",*v+1);
		}
		if(oq>0) printf("\n");

	}
}
