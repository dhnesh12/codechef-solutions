#include "bits/stdc++.h"
#include<unordered_map>
#include<unordered_set>
#pragma warning(disable:4996)

using namespace std;
using ld=long double;
const ld eps=1e-9;

#define WHATS(var)// cout<<__LINE__<<' '<<#var<<"="<<var<<endl;

template<class S, class T> ostream& operator <<(ostream &os, const pair<S, T> v){
  os << "( " << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<T> &v){
  for(int i = 0; i < v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<vector<T>> &v){
  for(int i = 0; i < v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<set<T>> &v){
  for(int i = 0; i < v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const set<T> &v){
	int i=0;
  	for(auto it:v){
		if(i > 0){os << ' ';}
		os << it;
		i++;
	} 
	return os;
}
using ll =long long ;



int mod =1000003;
struct Mod {
public:
	int num;
	Mod() : Mod(0) { ; }
	Mod(long long int n) : num((n % mod + mod) % mod) {

}
	Mod(int n) : Mod(static_cast<long long int>(n)) { ; }
	operator int() { return num; }
};

Mod operator+(const Mod a, const Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator+(const long long int a, const Mod b) { return Mod(a) + b; }
Mod operator+(const Mod a, const long long int  b) { return b + a; }
Mod operator++(Mod &a) { return a + Mod(1); }
Mod operator-(const Mod a, const Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator-(const long long int a, const Mod b) { return Mod(a) - b; }
Mod operator--(Mod &a) { return a - Mod(1); }
Mod operator*(const Mod a, const Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator*(const long long int a, const Mod b) { return Mod(a)*b; }
Mod operator*(const Mod a, const long long int b) { return Mod(b)*a; }
Mod operator*(const Mod a, const int b) { return Mod(b)*a; }
Mod operator+=(Mod &a, const Mod b) { return a = a + b; }
Mod operator+=(long long int &a, const Mod b) { return a = a + b; }
Mod operator-=(Mod &a, const Mod b) { return a = a - b; }
Mod operator-=(long long int &a, const Mod b) { return a = a - b; }
Mod operator*=(Mod &a, const Mod b) { return a = a * b; }
Mod operator*=(long long int &a, const Mod b) { return a = a * b; }
Mod operator*=(Mod& a, const long long int &b) { return a = a * b; }
Mod operator^(const Mod a, const int n) {
	if (n == 0) return Mod(1);
	Mod res = (a * a) ^ (n / 2);
	if (n % 2) res = res * a;
	return res;
}
Mod mod_pow(const Mod a, const int n) {
	if (n == 0) return Mod(1);
	Mod res = mod_pow((a * a), (n / 2));
	if (n % 2) res = res * a;
	return res;
}
Mod inv(const Mod a) { return a ^ (mod - 2); }
Mod operator/(const Mod a, const Mod b) {
	assert(b.num != 0);
	return a * inv(b);
}
Mod operator/(const long long int a, const Mod b) {
	return Mod(a) / b;
}
Mod operator/=(Mod &a, const Mod b) {
	return a = a / b;
}

#define MAX_MOD_N 1024000

Mod fact[MAX_MOD_N], factinv[MAX_MOD_N];
void init(const int amax = MAX_MOD_N) {
	fact[0] = Mod(1); factinv[0] = 1;
	for (int i = 0; i < amax - 1; ++i) {
		fact[i + 1] = fact[i] * Mod(i + 1);
		factinv[i + 1] = factinv[i] / Mod(i + 1);
	}
}
Mod comb(const int a, const int b) {
	return fact[a] * factinv[b] * factinv[a - b];
}

using Table=vector<int>;
map<char,int>mp;

Table tak(char ch,Table lt){
	assert(ch=='!');
	Table ans(lt.size());
	transform(lt.begin(),lt.end(),ans.begin(),[](const int a){return !a;});
	return ans;
}
Table tak(char ch,Table lt,Table rt){
	
	Table ans(lt.size());
	assert(lt.size()==rt.size()&&lt.size()==16);
	for(int i=0;i<16;++i){
		if(ch=='v'){
			ans[i]=lt[i]||rt[i];
			
		}else if(ch=='\\'){
			ans[i]=lt[i]&&(!rt[i]);
		}else if(ch=='^'){
			ans[i]=lt[i]&&rt[i];
		}else{
			assert(false);
		}
	}
	return ans;
}
Table getnum(string&st,int& a){
	WHATS(a);
	WHATS(st[a]);
	assert(mp.find(st[a])!=mp.end());
	auto k=mp[st[a]];
	Table tab(16);
	for(int i=0;i<16;++i){
		if(i&(1<<k)){
			tab[i]=true;
		}
	}
	a++;
	return tab;
}
Table term(string &st,int& a);
Table calc(string &st,int& a){
	WHATS(a);
	if(st[a]=='('){
		a++;
		Table tab=term(st,a);
		assert(st[a]==')');
		a++;
		return tab;
	}else{ 
		if(st[a]=='!'){
			a++;
			Table tab=calc(st,a);
			return tak('!',tab);
		}else{
			Table tab=getnum(st,a);
			return tab;
		}
	}
}
Table term(string &st,int& a){
	WHATS(a);
	Table ltab=calc(st,a);
	while(a!=st.size()){
		char ch=st[a];
		WHATS(ch);
		if(ch=='^'||ch=='v'||ch=='\\'){
			a++;
		}else{
			break;
		}
		Table rtab=calc(st,a);
		ltab=tak(ch,ltab,rtab);
	}

	return ltab;
}
Mod v[16];
Mod w[16];
int N;
void init2(){
	mp['Z']=0;
	mp['P']=1;
	mp['D']=2;
	mp['A']=3;
	mod--;
	v[0]=mod_pow(2,N);
	v[1]=mod_pow(2,N)-Mod(1);
	v[2]=mod_pow(2,N)-Mod(1);
	v[3]=mod_pow(2,N)-Mod(2);
	v[4]=mod_pow(2,N-1);
	v[5]=v[4]-Mod(1);
	v[6]=v[4]-Mod(1);
	v[7]=v[4]-Mod(1);
	v[8]=N+1;
	v[9]=N;
	v[10]=N;
	v[11]=N-1;
	v[12]=N;
	v[13]=N-1;
	v[14]=N-1;
	v[15]=N-1;

	mod++;
	for(int i=0;i<16;++i)v[i]=mod_pow(2,v[i]);

	for(int i=0;i<16;++i){
		for(int j=i;j<16;++j){
			int i_cnt=0;
			int j_cnt=0;
			for(int k=0;k<4;++k){
				if(i&(1<<k))i_cnt++;
				if(j&(1<<k))j_cnt++;
			}
			{
				if((i&j)==i){
					if((i_cnt-j_cnt)%2)w[i]-=v[j];
					else w[i]+=v[j];
				}
			}
		}
	}

}
int main(){
	cin>>N;
	init2();
	int Q;cin>>Q;
	while(Q--){
		string st;cin>>st;
		int a=0;
		Table tab=term(st,a);
		Mod answer=0;
		for(int i=0;i<16;++i){
			if(tab[i])answer+=w[i];
		}
		cout<<answer<<endl;
		WHATS(tab);
	}
	
	return 0;
}
