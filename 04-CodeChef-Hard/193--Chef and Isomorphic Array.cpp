#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <assert.h>
#include <string>
using namespace std;


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
			assert(cnt>0);
			if(is_neg){
				x= -x;
			}
			assert(l<=x && x<=r);
			return x;
		} else {
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

int arr[100100];
int n,q,T;
int sm_n=0,sm_q=0;


int rep[100100];
int ver[100100];
int vern=0;
long long the_hash;

int bl_end[100100];
int BL_s=200;
int BL_n;

long long mod = 1000000007;


long long precalc[200200];
long long block[500][500];
int hsh(int x){
	return precalc[x];
}

int cnt[500][100100];


int get_hash(int l,int r){
	int bl_l = l/BL_s;
	int bl_r = r/BL_s;
	vern++;
	long long ret= 0;
	
	if(bl_l + 1 <= bl_r - 1){
		ret += block[bl_l+1][bl_r-1];
	}
	if(bl_l == bl_r){
		for(int i=l;i<=r;i++){
			if(ver[arr[i]] != vern){
				ver[arr[i]] = vern;
				rep[arr[i]] = 0;
			}
			ret -= hsh(rep[arr[i]]);
			rep[arr[i]]++;
			ret += hsh(rep[arr[i]]);
			
		}
		ret %= mod;
		if(ret< 0){
			ret+= mod;
		}
		return ret;
	}
	for(int i=l;i<(bl_l+1) * BL_s;i++){
		if(ver[arr[i]] != vern){
			ver[arr[i]] = vern;
			rep[arr[i]] = cnt[bl_r-1][arr[i]] - cnt[bl_l][arr[i]];
		}
		ret -= hsh(rep[arr[i]]);
		rep[arr[i]]++;
		ret += hsh(rep[arr[i]]);
		
	}
	ret %= mod;
	for(int i=BL_s * bl_r;i<=r;i++){
		if(ver[arr[i]] != vern){
			ver[arr[i]] = vern;
			rep[arr[i]] = cnt[bl_r-1][arr[i]] - cnt[bl_l][arr[i]];
		}
		ret -= hsh(rep[arr[i]]);
		rep[arr[i]]++;
		ret += hsh(rep[arr[i]]);
		
	}
	ret %= mod;
	if(ret< 0){
			ret+= mod;
		}
	return ret;
}

set<pair<int,int> > hh;

int main(){
	T=readIntLn(1,10);
	for(int i=0;i<=100000;i++){
		precalc[i] = (i + 23452ll) * (i + 23452ll) * (i + 23452ll) % mod;
		precalc[i] *= (i + 23452ll) * (i + 23452ll) * (i + 23452ll) % mod;
		precalc[i] %= mod;
	}
	int maax;
	while(T--){
		maax=0;
		n=readIntLn(1,75000);
		BL_n = (n+BL_s-1)/BL_s;
		sm_n += n;
		assert(sm_n<=150000);
		for(int i=1;i<=n;i++){
			for(int j=0;j<BL_n;j++){
				cnt[j][i] = 0;
			}
		}
		for(int i=0;i<n;i++){
			bl_end[i]=-1;
		}
		for(int i=0;i<BL_n-1;i++){
			bl_end[(i+1)*BL_s -1] = i;
		}
		bl_end[n-1] = BL_n-1; 
		for(int i=0;i<n;i++){
			if(i==n-1){
				arr[i]=readIntLn(1,n);
			} else {
				arr[i]=readIntSp(1,n);
			}
			cnt[i/BL_s][arr[i]]++;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<BL_n;j++){
				cnt[j][i] += cnt[j-1][i];
			}
		}
		for(int i=0;i<BL_n;i++){
			vern++;
			the_hash=0;
			for(int j=BL_s * i;j<n;j++){
				if(ver[arr[j]] != vern){
					ver[arr[j]] = vern;
					rep[arr[j]] = 0;
				}
				the_hash -= hsh(rep[arr[j]]);
				rep[arr[j]]++;
				the_hash += hsh(rep[arr[j]]);
				
				if(bl_end[j]!=-1){
					the_hash %= mod;
					block[i][bl_end[j]]=the_hash;
				}
			}
		}
		q=readIntLn(1,200000);
		sm_q += q;
		assert(sm_q<=400000);
		long long last=0;
		for(int i=1;i<=q;i++){
			int x,y,z,t,k,c,d;
			x=readIntSp(1,n);
			z=readIntSp(1,n);
			k=min(n-x,n-z) + 1;
			c=readIntSp(0,1000000000);
			d=readIntLn(0,1000000000);
			c %= k;
			d %= k;
			y= x + (c + last * d) % k;
			t= z + (c + last * d) % k;
			//cout<<"ER: "<<last<<" "<<x<<" "<<y<<" "<<z<<" "<<t<<endl;
			x--;
			y--;
			z--;
			t--;
			if(get_hash(x,y) == get_hash(z,t)){
				hh.insert(make_pair(x,y));
				hh.insert(make_pair(z,t));
				printf("YES\n");
				maax+=y-x;
				last = i;
			} else {
				printf("NO\n");
			}
		}
		cerr<<hh.size()<<endl;
	}
	assert(getchar()==-1);
}