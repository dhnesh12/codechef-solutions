#include<stdio.h>
#include<algorithm>
#include<iostream>
#define M 15
#define oo 2000000000
using namespace std;
template <class T>
inline void Rd(T &res){
	char c;res=0;int k=1;
	while(c=getchar(),c<48&&c!='-');
	if(c=='-'){k=-1;c='0';}
	do{
		res=(res<<3)+(res<<1)+(c^48);
	}while(c=getchar(),c>=48);
	res*=k;
}
template <class T>
inline void Pt(T res){
	if(res<0){
		putchar('-');
		res=-res;
	}
	if(res>=10)Pt(res/10);
	putchar(res%10+48);
}
void swap(int &a,int &b){
	int t=a;a=b;b=t;
}
struct node{
	int L,R;
	bool operator <(const node &tmp)const{
		if(L!=tmp.L)return L<tmp.L;
		return R>tmp.R;
	}
}s[2];
int T,n,h[M],m[M];
int main(){
	Rd(T);
	while(T--){
		Rd(n);
		for(int i=1;i<=n;i++){
			Rd(h[i]);Rd(m[i]);
		}
		bool f=false,ok=true;//trueè¡¨ç¤ºå��ä¸�,falseè¡¨ç¤ºå��ä¸�
		int L=0,R=oo;
		int cnt=0;
		for(int i=1;i<n;i++){
			int a=h[i],b=h[i+1],va=m[i],vb=m[i+1];
			if(f){
				if(va<vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0);
					else L=max(L,(b-a)/(va-vb)+1);
				}else if(va>vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0)ok=false;
					if((b-a)%(va-vb)==0)R=min(R,(b-a)/(va-vb)-1);
					else R=min(R,(b-a)/(va-vb));
				}else if(a>=b)ok=false;
			}else{
				if(va<vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0)ok=false;
					if((b-a)%(va-vb)==0)R=min(R,(b-a)/(va-vb)-1);
					else R=min(R,(b-a)/(va-vb));
				}else if(va>vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0);
					else L=max(L,(b-a)/(va-vb)+1);
				}else if(a<=b)ok=false;
			}
			f=!f;
		}
		if(ok&&L<=R){
			s[cnt++].L=L;
			s[cnt-1].R=R;
		}
		f=true;
		ok=true;
		L=0,R=oo;
		for(int i=1;i<n;i++){
		int a=h[i],b=h[i+1],va=m[i],vb=m[i+1];
			if(f){
				if(va<vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0);
					else L=max(L,(b-a)/(va-vb)+1);
				}else if(va>vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0)ok=false;
					if((b-a)%(va-vb)==0)R=min(R,(b-a)/(va-vb)-1);
					else R=min(R,(b-a)/(va-vb));
				}else if(a>=b)ok=false;
			}else{
				if(va<vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0)ok=false;
					if((b-a)%(va-vb)==0)R=min(R,(b-a)/(va-vb)-1);
					else R=min(R,(b-a)/(va-vb));
				}else if(va>vb){
					if((b-a)/(va-vb)==0&&1LL*(b-a)*(va-vb)<0);
					else L=max(L,(b-a)/(va-vb)+1);
				}else if(a<=b)ok=false;
			}
			f=!f;
		}
		if(ok&&L<=R){
			s[cnt++].L=L;
			s[cnt-1].R=R;
		}
		if(cnt==2){
			sort(s,s+cnt);
			if(s[0].L<=s[1].L&&s[0].R>=s[1].R)cnt--;
			else if(s[0].R>=s[1].L-1&&s[0].R<=s[1].R){
				cnt--;
				s[0].R=s[1].R;
			}
		}
		Pt(cnt);putchar('\n');
		for(int i=0;i<cnt;i++){
			Pt(s[i].L);putchar(' ');
			if(s[i].R==oo)puts("Inf");
			else{Pt(s[i].R);putchar('\n');}
		}
	}
	return 0;
} 