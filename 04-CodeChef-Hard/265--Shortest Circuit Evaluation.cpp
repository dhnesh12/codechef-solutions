#include <bits/stdc++.h>
using namespace std;
#define nc getchar
#define DB double
#define LD long double
#define ULL unsigned long long

const int N=1e5+50;
map <ULL,int> mp;
struct atom {
	int type;
	LD E,p;
	atom() {}
	atom(int type,DB E,DB p) : type(type), E(E),p(p) {}
	inline atom opt() {return atom(type,E,1-p);}
};
typedef vector <atom> ls;
int A[N],B[N],top,m,len;  DB p[N]; 
char ch[N]; 
inline atom calc(ls &vec,int type) {
	if(type==-3) {
		sort(vec.begin(),vec.end(),[](atom c,atom d) {return c.E*d.p<d.E*c.p;});
		DB s1=0, s2=0, sp=1;
		for(int i=0;i<vec.size();i++) {
			s1+=sp*vec[i].E; 
			s2+=sp*vec[i].p;
			sp*=(1-vec[i].p);
		} return atom(1,s1,s2);
	} else {
		sort(vec.begin(),vec.end(),[](atom c,atom d) {return c.E*(1-d.p)<d.E*(1-c.p);});
		DB s1=0, s2=0, sp=1;
		for(int i=0;i<vec.size();i++) {
			s1+=sp*vec[i].E;
			s2+=sp*(1-vec[i].p);
			sp*=vec[i].p;
		} return atom(1,s1,1-s2);
	}
}
inline atom calc(ls &vec) { //没有括号，not 
	reverse(vec.begin(),vec.end());
	for(int i=vec.size()-1,j;i;i=vec.size()-1) {
		ls t; j=i-1; int type=vec[j].type; 
		t.push_back(vec[i]); vec.pop_back();
		while(j>=0 && vec[j].type==type) 
			t.push_back(vec[j-1]), vec.pop_back(), vec.pop_back(), j-=2;
		vec.push_back(calc(t,type));
	} return vec[0];
}
inline atom get_atom(int l,int r) {//转化成没有括号,not的形式 
	ls vec;
	for(int i=l,j;i<=r;i=j+1) {
		if(A[i]==-1) {
			j=B[i];
			atom t=get_atom(i+1,j-1);
			vec.push_back(t);
		} else if(A[i]>0) {
			vec.push_back(atom(1,1,p[A[i]])); j=i;
		} else {
			vec.push_back(atom(A[i],0,0)); j=i;
		}
 	}
	ls vec2;
	for(int i=0,j;i<vec.size();i=j+1) {
		if(vec[i].type==-5) {
			vec2.push_back(vec[i+1].opt()); j=i+1;
		} else {
			vec2.push_back(vec[i]); j=i;
		}
	} return calc(vec2);
}
inline void solve() {
	m=top=0; char c=nc(); 
	mp.clear();
	while(isspace(c)) c=nc();
	while(c!='\n') {
		if(c=='(') A[++top]=-1, c=nc();
		else if(c==')') A[++top]=-2, c=nc();
		else if(isalpha(c)) {
			len=0;
			while(isalpha(c)) ch[++len]=c, c=nc();	
			if(len==2 && ch[1]=='o' && ch[2]=='r') A[++top]=-3;
			else if(len==3 && ch[1]=='a' && ch[2]=='n' && ch[3]=='d') A[++top]=-4;
			else if(len==3 && ch[1]=='n' && ch[2]=='o' && ch[3]=='t') A[++top]=-5;
			else {
				ULL val=0; A[++top]=++m; 
				for(int i=1;i<=len;i++) val=val*30+ch[i]-'a'+1;
				mp[val]=m;
			} 
		} else c=nc();
	}
	for(int i=1;i<=m;i++) {
		scanf("%s",ch+1); 
		len=strlen(ch+1);
		ULL val=0;
		for(int i=1;i<=len;i++) val=val*30+ch[i]-'a'+1;
		scanf("%lf",&p[mp[val]]);
	}
	vector <int> vec;
	for(int i=1;i<=top;i++) {
		if(A[i]==-1) vec.push_back(i);
		else if(A[i]==-2) B[vec.back()]=i, vec.pop_back();
	}
	printf("%.6lf\n",(DB)get_atom(1,top).E);
}

int main() {
	int T; cin>>T;
	while(T--) solve();
}