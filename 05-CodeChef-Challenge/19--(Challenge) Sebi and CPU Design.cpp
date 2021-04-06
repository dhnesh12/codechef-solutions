#include<bits/stdc++.h>
#define fo(i,a,b)for(int i=a,_e=b;i<=_e;++i)
#define fd(i,a,b)for(int i=b,_e=a;i>=_e;--i)
#define put putchar
#define pp printf
#define ul unsigned long long
#define np(a,b) next_permutation(a,b)
#define ct(x) __builtin_popcountll(x)
using namespace std;
const int N=100;
const ul _8=(1<<8)-1,_16=(1<<16)-1,_32=((ul)1<<32)-1;
int n,os,O;
ul a[N][4],s[N];
struct oper{
	int op,a,c,b,c1;
}o[100000];
struct nod{
	ul a,b,c,d;
	ul get(int op){
		if(op==1)return a<<32|b<<16|c<<8|d;
		if(op==2)return b<<16|c<<8|d;
		if(op==3)return c<<8|d;
		if(op==4)return d;
		return c;
	}
	void in(int op,ul x){
		if(op==1){
			a=x>>32;
			b=x<<32>>48;
			c=(x&_16)>>8;
			d=x&_8;
			return;
		}
		if(op==2){
			b=x<<32>>48;
			c=(x&_16)>>8;
			d=x&_8;
			return;
		}
		if(op==3){
			c=(x&_16)>>8;
			d=x&_8;
			return;
		}
		if(op==4){
			d=x&_8;
			return;
		}
		c=x&_8;
	}
}x[5];
void put_v(int a,int c){
	if(c==1)put('r');
	if(c==2)put('e');
	putchar('a'+a-1);
	if(c<=3)put('x');
	if(c==4)put('l');
	if(c==5)put('h');
	put(' ');
}
ul op1_(int op,ul a){
	if(op==1)return a-1;
	if(op==2)return a+1;
	return ~a;
}
void op1(int op,int a,int c){
	if(op==1)pp("dec ");
	if(op==2)pp("inc ");
	if(op==3)pp("not ");
	put_v(a,c);put('\n');
}
void _op1(int op,int a,int c){
	x[a].in(c,op1_(op,x[a].get(c)));
}
ul op2_(int op,ul a,ul b){
	if(op==1)return a&b;
	if(op==2)return a|b;
	if(op==3)return a^b;
	if(op==4)return a<<b;
	if(op==5)return a>>b;
	if(op==6)return a+b;
	if(op==7)return a-b;
	if(op==8)return a*b;
	if(op==9||op==10)assert(b>0);
	if(op==9)return a/b;
	if(op==10)return a%b;
	if(op==11)return b;
}
void op2(int op,int a,int c,int b,int c1){
	if(op==1)pp("and ");
	if(op==2)pp("or ");
	if(op==3)pp("xor ");
	if(op==4)pp("shl ");
	if(op==5)pp("shr ");
	if(op==6)pp("add ");
	if(op==7)pp("sub ");
	if(op==8)pp("mul ");
	if(op==9)pp("div ");
	if(op==10)pp("mod ");
	if(op==11)pp("mov ");
	put_v(a,c);put_v(b,c1);put('\n');
}
void _op2(int op,int a,int c,int b,int c1){
	x[a].in(c,op2_(op,x[a].get(c),x[b].get(c1)));
}
void add(int op,int a,int c,int b=0,int c1=0){
	if(b){
		_op2(op,a,c,b,c1);
	}else{
		_op1(op,a,c);
	}
	o[++os]=(oper){op,a,c,b,c1};
}
void dg(ul x){
	if(x==1){
		add(2,3,1);
		return;
	}
	dg(x>>1);
	add(6,3,1,3,1);
	if(x&1)add(2,3,1);
}
void P(){
	printf("%d\n",os);
	fo(i,1,os)
		if(o[i].b)op2(o[i].op,o[i].a,o[i].c,o[i].b,o[i].c1);
		else op1(o[i].op,o[i].a,o[i].c);
}
void work3(){
	O=3;
	fo(i,1,n)s[i]=a[i][2]-a[i][1];
	if(s[1]!=s[2]){
		O=1;
	}
//	fo(i,1,8)
//		fo(j,1,7)if(s[(i-1)*8+j]!=s[i*8]){
//			O=1;break;
//		}
	if(O==3){
		printf("%d\n",n*1000);
		exit(0);
		add(2,4,1);
		fo(ii,1,8){
			if(ii>1)add(7,3,1,3,1);
			dg(a[ii*8][2]-a[ii*8][1]);
			add(11,2,1,3,1);
			fo(jj,1,8){
				int i=(ii-1)*8+jj;
				int mxx=1e9,w=i;
				fo(j,i,ii*8){
					int sum=0,mx=0;
					fo(k,1,1){
						ul s=x[k].get(1)^a[j][k];
						sum+=__builtin_popcountll(s);
						fd(l,0,63)if(s&((ul)1<<l)){
							mx=max(mx,l);
							break;
						}
					}
					sum+=mx+1;
					if(sum<mxx){
						mxx=sum;
						w=j;
					}
				}
				swap(a[w],a[i]);
				int mx=0;
				fo(k,1,1){
					ul s=x[k].get(1)^a[i][k];
					fd(j,0,63)if(s&((ul)1<<j)){
						mx=max(mx,j);
						break;
					}
				}
				fo(j,0,mx){
					fo(k,1,1)if((x[k].get(1)^a[i][k])&((ul)1<<j))
						add(3,k,1,4,1);
					if(j<mx){
						add(6,4,1,4,1);
					}else{
						if(i<n)add(9,4,1,4,1);
					}
				}
				add(6,2,1,1,1);
				add(6,3,1,2,1);
				fo(k,1,3)
					assert(x[k].get(1)==a[i][k]);
				if(jj<8){
					add(7,3,1,2,1);
					add(7,2,1,1,1);
				}
			}
		}
		P();
		exit(0);
	}
}
void work5(){
	O=5;
	fo(i,1,n)s[i]=a[i][1]+a[i][2]+a[i][3];
	fo(i,2,n)if(s[i]!=s[1]){O=1;break;}
	if(O==5){
		dg(s[1]);
		int p[4]={0,1,2,3};
		ul p2[4];
		add(2,4,1);
		fo(i,1,n){
			int mxx=1e9,w=i;
			fo(j,i,n){
				p2[1]=0;
				fo(jc,1,6){
					int sum=0,mx=0;
					fo(k,1,2){
						ul s=x[k].get(1)^a[j][p[k]];
						sum+=__builtin_popcountll(s);
						fd(l,0,63)if(s&((ul)1<<l)){
							mx=max(mx,l);
							break;
						}
					}
					sum+=mx+1;
					if(sum<mxx){
						fo(l,1,3)p2[l]=p[l];
						mxx=sum;
						w=j;
					}
					np(p+1,p+4);
				}
				if(p2[1]){
					fo(l,1,3)p2[l]=a[j][p2[l]];
					fo(l,1,3)a[j][l]=p2[l];
				}
			}
			swap(a[w],a[i]);
			int mx=0;
			fo(k,1,2){
				ul s=x[k].get(1)^a[i][k];
				fd(j,0,63)if(s&((ul)1<<j)){
					mx=max(mx,j);
					break;
				}
			}
			fo(j,0,mx){
				fo(k,1,2)if((x[k].get(1)^a[i][k])&((ul)1<<j))
					add(3,k,1,4,1);
				if(j<mx){
					add(6,4,1,4,1);
				}else{
					if(i<n)add(9,4,1,4,1);
				}
			}
			add(7,3,1,1,1);
			add(7,3,1,2,1);
			fo(k,1,3)
				assert(x[k].get(1)==a[i][k]);
			if(i<n){
				add(6,3,1,1,1);
				add(6,3,1,2,1);
			}
		}
		P();
		exit(0);
	}
}
void work2(){
	O=2;
	fo(i,1,n){
		int cnt=ct(a[i][1]^a[i][2])+ct(a[i][1]^a[i][3]);
		if(cnt>4){O=1;break;}
	}
	if(O==2){
		int p[4]={0,1,2,3};
		ul p2[4];
		add(2,4,1);
		fo(i,1,n){
			int mxx=1e9,w=i;
			fo(j,i,n){
				p2[1]=0;
				fo(jc,1,6){
					int sum=0,mx=0;
					fo(k,1,3){
						ul s=k==1?x[k].get(1)^a[j][p[k]]:a[i][p[1]]^a[i][p[k]];
						sum+=__builtin_popcountll(s);
						fd(l,0,63)if(s&((ul)1<<l)){
							mx=max(mx,l);
							break;
						}
					}
					sum+=mx+1;
					if(sum<mxx){
						fo(l,1,3)p2[l]=p[l];
						mxx=sum;
						w=j;
					}
					np(p+1,p+4);
				}
				if(p2[1]){
					fo(l,1,3)p2[l]=a[j][p2[l]];
					fo(l,1,3)a[j][l]=p2[l];
				}
			}
			swap(a[w],a[i]);
			int mx=0;
			fo(k,1,3){
				ul s=k==1?x[k].get(1)^a[i][k]:a[i][1]^a[i][k];
				fd(j,0,63)if(s&((ul)1<<j)){
					mx=max(mx,j);
					break;
				}
			}
			add(7,2,1,2,1);
			add(7,3,1,3,1);
			fo(j,0,mx){
				fo(k,1,3){
					ul s=k==1?x[k].get(1)^a[i][1]:a[i][1]^a[i][k];
					if(s&((ul)1<<j))
						add(3,k,1,4,1);
				}
				if(j<mx){
					add(6,4,1,4,1);
				}else{
					if(i<n)add(9,4,1,4,1);
				}
			}
			add(3,2,1,1,1);
			add(3,3,1,1,1);
			fo(k,1,3)
				assert(x[k].get(1)==a[i][k]);
		}
		P();
		exit(0);
	}
}
void work1(){
	if(O==1){
		int p[4]={0,1,2,3};
		ul p2[4];
		add(2,4,1);
		fo(i,1,n){
			int mxx=1e9,w=i;
			fo(j,i,n){
				p2[1]=0;
				fo(jc,1,6){
					int sum=0,mx=0;
					fo(k,1,3){
						ul s=x[k].get(1)^a[j][p[k]];
						sum+=__builtin_popcountll(s);
						fd(l,0,63)if(s&((ul)1<<l)){
							mx=max(mx,l);
							break;
						}
					}
					sum+=mx+1;
					if(sum<mxx){
						fo(l,1,3)p2[l]=p[l];
						mxx=sum;
						w=j;
					}
					np(p+1,p+4);
				}
				if(p2[1]){
					fo(l,1,3)p2[l]=a[j][p2[l]];
					fo(l,1,3)a[j][l]=p2[l];
				}
			}
			swap(a[w],a[i]);
			int mx=0;
			fo(k,1,3){
				ul s=x[k].get(1)^a[i][k];
				fd(j,0,63)if(s&((ul)1<<j)){
					mx=max(mx,j);
					break;
				}
			}
			fo(j,0,mx){
				fo(k,1,3)if((x[k].get(1)^a[i][k])&((ul)1<<j))
					add(3,k,1,4,1);
				if(j<mx){
					add(6,4,1,4,1);
				}else{
					if(i<n)add(9,4,1,4,1);
				}
			}
			fo(k,1,3)
				assert(x[k].get(1)==a[i][k]);
		}
		P();
	}
}
int main(){
	#ifndef ONLINE_JUDGE
		freopen("c.in","r",stdin);
		freopen("c.out","w",stdout);
	#endif
	cin>>n;
	fo(i,1,n)cin>>a[i][1]>>a[i][2]>>a[i][3];
	O=1;
	work3();
	work5();
	work2();
	work1();
}