#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

struct Str{
	string str;
	Str(string _st="") {str=_st;}
	friend bool operator < (Str a,Str b) {
		if (a.str.length()==b.str.length()) return a.str<b.str;
		return a.str.length()<b.str.length();
	}
};

multiset<Str> t;

typedef multiset<Str> :: iterator it;

int main() {srand (time (0));
	int n;scanf("%d",&n);
	vector<Str> s(n*(n-1));
	fo(i,0,n*(n-1)-1) cin>>s[i].str;
	sort(s.begin(),s.end());
	fo(len,1,s[0].str.length()-1) {
		bool ok=1;t.clear();
		for(int j=1;j<n*(n-1);j++) t.insert(Str(s[j]));

		string a=s[0].str.substr(0,len);
		string b=s[0].str.substr(len);

		it pos=t.find(Str(b+a));
		if (pos==t.end()) continue;
		else t.erase(pos);

		vector<string> vec({a,b});

		if (b.length()<a.length()) swap(a,b);

		for(int j=1;j<n*(n-1);j++) {
			if (!t.count(Str(s[j]))) continue;
			string a1=s[j].str.substr(0,a.length());
			string c1=s[j].str.substr(a.length());

			string a2=s[j].str.substr(s[j].str.length()-a.length());
			string c2=s[j].str.substr(0,s[j].str.length()-a.length());

			if (a!=a1&&a!=a2) {ok=0;break;}

			string tmp;

			if (a==a1&&a==a2) {
				it p1,p2;
				p1=t.find(c1+a);p2=t.find(a+c2);
				if (p1==t.end()&&p2==t.end()) ok=0;
				else if (p1!=t.end()&&p2!=t.end()) tmp=((rand() & 1)?c1:c2);
				else tmp=p1==t.end()?c2:c1;
			} else tmp=(a==a1)?c1:c2; // 选能匹配的那个；如果都能匹配那么选字典序小的那个
			
			if (!ok) break;

			for(auto st:vec) {
				it pos=t.find(st+tmp);
				if (pos==t.end()) {ok=0;break;}
				else t.erase(pos);
				pos=t.find(tmp+st);
				if (pos==t.end()) {ok=0;break;}
				else t.erase(pos);
			}
			if (!ok) break;
			vec.push_back(tmp);
		}
		if (ok&&vec.size()==n) {
			puts("Yes");
			for(int i=0;i<vec.size();i++) cout<<vec[i]<<endl;
			return 0;
		}
	}
	puts("No");
	return 0;
}
