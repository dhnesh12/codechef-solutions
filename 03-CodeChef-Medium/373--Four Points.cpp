#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")

#define f first
#define s second
#define pb push_back
#define endl '\n'





#define T long double
#define EPS 1e-9
const int N=1e6;
struct PT{
	T x, y;
	PT() {}
	PT(T x, T y) : x(x), y(y) {}
	PT(const PT& p) : x(p.x), y(p.y) {}
	bool operator < (const PT& rhs) const{
		return make_pair(y, x) < make_pair(rhs.y, rhs.x);
	}
	bool operator == (const PT& rhs) const{
		return make_pair(y, x) == make_pair(rhs.y, rhs.x);
	}
	PT operator + (const PT& p) const{
		return PT(x+p.x, y+p.y);
	}
	PT operator - (const PT& p) const{
		return PT(x-p.x, y-p.y);
	}
	PT operator * (T c) const {
		return PT(x*c, y*c);
	}
	PT operator / (T c) const {
		return PT(x/c, y/c);
	}
};

T cross(PT p, PT q){
	return p.x*q.y-p.y*q.x;
}

T area2(PT a, PT b, PT c){
	return cross(a, b)+cross(b, c)+cross(c, a);
}

T dot(PT p, PT q){
	return p.x*q.x+p.y*q.y;
}

T dist2(PT p, PT q){
	return dot(p-q, p-q);
}

bool between(const PT& a, const PT& b, const PT& c){
	return (fabs(area2(a, b, c))<EPS && (a.x-b.x)*(c.x-b.x)<=0 && (a.y-b.y)*(c.y-b.y)<=0);
}

void Con(vector<PT>& pts){
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<PT> up, dn;
	for(int i=0; i<pts.size(); i++){
		while(up.size()>1 && area2(up[up.size()-2], up.back(), pts[i])>=0){
			up.pop_back();
		}
		while(dn.size()>1 && area2(dn[dn.size()-2], dn.back(), pts[i])<=0){
			dn.pop_back();
		}
		up.push_back(pts[i]);
		dn.push_back(pts[i]);
	}
	pts=dn;
	for(int i=up.size()-2; i>=1; i--){
		pts.push_back(up[i]);
	}
	if(pts.size()<=2){
		return;
	}
	dn.clear();
	dn.push_back(pts[0]);
	dn.push_back(pts[1]);
	for(int i=2; i<pts.size(); i++){
		if(between(dn[dn.size()-2], dn[dn.size()-1], pts[i])){
			dn.pop_back();
		}
		dn.push_back(pts[i]);
	}
	if(dn.size()>=3 && between(dn.back(), dn[0], dn[1])){
		dn[0]=dn.back();
		dn.pop_back();
	}
	pts=dn;
}

int LP(PT a, PT b, PT c, PT d){
	return fabs(cross(b-a, c-d))<EPS;
}

int LC(PT a, PT b, PT c, PT d){
	return LP(a, b, c, d) && fabs(cross(a-b, a-c)) < EPS && fabs(cross(c-d, c-a))<EPS;
}


int seg(PT a, PT b, PT c, PT d){
	if(LC(a, b, c, d)){
		if(dist2(a, c)<EPS || dist2(a, d)<EPS || dist2(b, c)<EPS || dist2(b, d)<EPS){
			return 1;
		}
		if(dot(c-a, c-b)>0 && dot(d-a, d-b)>0 && dot(c-b, d-b)>0){
			return 0;
		}
		return 1;
	}
	if(cross(d-a, b-a)*cross(c-a, b-a)>0){
		return 0;
	}
	if(cross(a-c, d-c)*cross(b-c, d-c)>0){
		return 0;
	}
	return 1;
}

PT lin(PT a, PT b, PT c, PT d){
	b=b-a;
	d=c-d;
	c=c-a;
	return a + b*cross(c, d)/cross(b, d);
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout<<fixed<<setprecision(20);
	int t;
	cin>>t;
	while(t--){
		int x[4];
		int y[4];
		for(int i=0; i<4; i++){
			cin>>x[i]>>y[i];
		}
		bool che=0;
		
		for(int i=0; i<4; i++){
			for(int j=0; j<i; j++){
				PT a(x[i], y[i]);
				PT b(x[j], y[j]);
				
				vector<int>v;
				for(int k=0; k<4; k++){
					if(k!=i && k!=j){
						v.pb(k);
					}
				}
				PT c(x[v[0]], y[v[0]]);
				PT d(x[v[1]], y[v[1]]);
				
				if(LP(a, b, c, d)==1){
					if(LC(a, b, c, d)){
						vector<PT>vecs;
						vecs.pb(a);
						vecs.pb(b);
						vecs.pb(c);
						vecs.pb(d);
						sort(vecs.begin(), vecs.end());
						if(che==0){
							cout<<"YES"<<" ";
							cout<<vecs[0].x<<" "<<vecs[0].y<<" ";
							cout<<vecs[1].x<<" "<<vecs[1].y<<" ";
							cout<<vecs[3].x<<" "<<vecs[3].y<<" ";
							cout<<endl;
						}
						che=1;
						continue;
					}
					if(x[i]==x[j]){
						if(y[i]<y[j]){
							swap(a, b);
						}
						if(y[v[0]]<y[v[1]]){
							swap(c, d);
						}
					}
					else{
						if(x[i]<x[j]){
							swap(a, b);
						}
						if(x[v[0]]<x[v[1]]){
							swap(c, d);
						}
					}
					if(che==0){
						cout<<"YES"<<" ";
						T val2=100/(sqrt(dist2(a, b)));
						PT a1=a+(a-b)*val2;
						PT b1=b-(a-b)*val2;
						cout<<a1.x<<" "<<a1.y<<" "<<b1.x<<" "<<b1.y<<" ";
						PT f=lin(a1, c, b1, d);
						cout<<f.x<<" "<<f.y<<endl;
					}
					che=1;
					continue;
				}
				PT f=lin(a, b, c, d);
				PT pt=f;
				if((pt.x>=a.x+EPS && pt.x+EPS<=b.x || pt.y>=a.y+EPS && pt.y+EPS<=b.y) || (pt.x>=c.x+EPS && pt.x+EPS<=d.x || pt.y>=c.y+EPS && pt.y+EPS<=d.y)){
					continue;
				}
				if((pt.x>=b.x+EPS && pt.x+EPS<=a.x || pt.y>=b.y+EPS && pt.y+EPS<=a.y) || (pt.x>=d.x+EPS && pt.x+EPS<=c.x || pt.y>=d.y+EPS && pt.y+EPS<=c.y)){
					continue;
				}
				if(che==0){
					
					cout<<"YES"<<" ";
					cout<<f.x<<" "<<f.y<<" ";
					if(dist2(a, f)<dist2(b, f)){
						swap(a, b);
					}
					if(dist2(c, f)<dist2(d, f)){
						swap(c, d);
					}
					cout<<a.x<<" "<<a.y<<" "<<c.x<<" "<<c.y<<endl;
				}
				che=1;
			}
		}
		if(che==0){
			cout<<"NO"<<endl;
		}
	}
	return 0;
}