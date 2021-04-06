#include<bits/stdc++.h>
typedef long long LL;
typedef double dl;
#define opt operator
#define pb push_back
#define pii std::pair<LL,LL>
const LL maxn=1e6+9,mod=998244353,inf=0x3f3f3f3f;
LL Read(){
	LL x(0),f(1); char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0' && c<='9'){
		x=(x<<3ll)+(x<<1ll)+c-'0'; c=getchar();
	}return x*f;
}
void Chkmin(LL &x,LL y){
	if(y<x) x=y;
}
void Chkmax(LL &x,LL y){
	if(y>x) x=y;
}
LL add(LL x,LL y){
	return x+=y,x>=mod?x-mod:x;
}
LL dec(LL x,LL y){
	return x-=y,x<0?x+mod:x;
}
LL mul(LL x,LL y){
	return 1ll*x*y%mod;
}
LL Pow(LL base,LL b){
	LL ret(1); while(b){
		if(b&1) ret=mul(ret,base); base=mul(base,base); b>>=1;
	}return ret;
}
LL inv2,ret,N;
LL Calc(LL x){
	LL ret(mul(x,dec(x,1)));
	ret=mul(ret,inv2);
	return ret;
}
namespace Sgt{
	LL root,nod;
	LL son[3000009][2],tag[3000009],sum[3000009];
	LL Query(LL nw,LL l,LL r,LL lt,LL rt){
		if(lt<=l && rt>=r){ 
			//printf("%lld:(%lld,%lld)%lld\n",nw,l,r,sum[nw]);
			//if(sum[nw]>10) exit(0);
			return sum[nw];
	    }
		LL mid(l+r>>1ll),ret(mul((rt-lt+1)%mod,tag[nw]));
		if(rt<=mid) ret=add(ret,Query(son[nw][0],l,mid,lt,rt));
		else if(lt>mid) ret=add(ret,Query(son[nw][1],mid+1,r,lt,rt));
		else{
			ret=add(ret,Query(son[nw][0],l,mid,lt,mid));
			ret=add(ret,Query(son[nw][1],mid+1,r,mid+1,rt));
		}
		return ret;
	}
	void Modify(LL &nw,LL l,LL r,LL lt,LL rt,LL x){
		if(!nw) nw=++nod;
        sum[nw]=add(sum[nw],mul((rt-lt+1)%mod,x));
		/*
		if(sum[nw]>10){
			printf("## (%lld,%lld,%lld)%lld\n",lt,rt,x,(rt-lt+1)*x);
			exit(0);
		}
		*/
		if(lt<=l && rt>=r){
			tag[nw]=add(tag[nw],x);
			return;
		}
		LL mid(l+r>>1ll);
		if(rt<=mid) Modify(son[nw][0],l,mid,lt,rt,x);
		else if(lt>mid) Modify(son[nw][1],mid+1,r,lt,rt,x);
		else{
			Modify(son[nw][0],l,mid,lt,mid,x);
			Modify(son[nw][1],mid+1,r,mid+1,rt,x);
		}
	}
	void Modify(LL l,LL r,LL x){
		LL tmp(x);
		//printf("[%lld,%lld](%lld)\n",l,r,x);
		LL len((r-l+1)%mod);
		x%=mod; x=(x+mod)%mod;
		ret=add(ret,mul(len,Calc(x)));
		//printf("%lld\n",ret);
		ret=add(ret,mul(x,Query(root,0,N-1,l,r)));
		//printf("%lld(%lld)\n",ret,Query(root,0,N-1,l,r));
		//if(ret<0) exit(0);
		Modify(root,0,N-1,l,r,x);
	}
	void Clear(LL nw){
		tag[nw]=0; sum[nw]=0;
		if(!nw) return;
		Clear(son[nw][0]); Clear(son[nw][1]);
		son[nw][0]=son[nw][1]=0;
	}
	void Clear(){
		Clear(root);
		root=0; nod=0;
	}
}
LL K,q,T;
void Modify(LL r,LL flag){
	if(r<0) return;
	LL len(r+1);
	Sgt::Modify(0,N-1,flag*len/N);
	LL U(0);
	for(LL i=1;i<=K/2;++i){
		LL nw(K-i+1);
		if((r>>nw-1)&1) U|=(1<<i-1);
	}
	//printf("# %lld\n",ret);
	if(!(len%N)) return;
	r%=N;
	/*
	printf("%lld:",U);
	for(LL i=K/2;i>=1;--i){
		printf("%lld",(r>>i-1)&1);
	}puts("");
	*/
	//printf("%d\n",r);
	//printf("# %lld\n",ret);
	LL tmp(0);
	for(LL i=K/2;i>=1;--i){
		if((r>>i-1)&1){
			//if((U>>i-1)&1)
            Sgt::Modify(tmp+(1<<i-1)*((U>>i-1)&1),tmp+(1<<i-1)*((U>>i-1)&1)+((1<<i-1)-1),flag*1);
		}
		tmp|=(1<<i-1)*(((r>>i-1)&1)^((U>>i-1)&1));
	}
	Sgt::Modify(U^r,U^r,flag*1);
}
void Del(LL r){
	if(r==-1) return;
}
void Solve(){
	q=Read(); K=Read();
	N=(1<<K/2);
	ret=0;
    for(LL ti=1;ti<=q;++ti){
		LL l(Read()),r(Read());
		//printf("%lld,%lld\n",l,r);
		Modify(r,1);
		//printf("%lld\n",ret);
		//exit(0);
		Modify(l-1,-1);
		printf("%lld\n",ret);
		//if(ti==3) exit(0);
		//exit(0);
	}
}
int main(){
	//freopen("y1.txt","r",stdin);
	inv2=Pow(2,mod-2);
	T=Read();
	while(T--){
		Solve();
		Sgt::Clear();
	}
	return 0;
}



