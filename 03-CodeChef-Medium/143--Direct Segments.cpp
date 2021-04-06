#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'
#define T long double
#define EPS 1e-9





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







int n;//2*N
vector<vector<int>>adj;
vector<vector<int>>g, gt;//g stores implication, gt stores reverse edges
vector<bool>used;
vector<int>order, comp;
vector<bool>assignment;//resize all to n, //assignment is for i=1 to (n/2)

void dfs1(int v){
	used[v]=1;
	for(int u:g[v]){
		if(!used[u]){
			dfs1(u);
		}
	}
	order.pb(v);
}

void dfs2(int v, int c1){
	comp[v]=c1;
	for(int u:gt[v]){
		if(comp[u]==-1){
			dfs2(u, c1);
		}
	}
}


bool f(){
	used.assign(n, false);
	for(int i=0; i<n; i++){
		if(!used[i]){
			dfs1(i);
		}
	}
	
	comp.assign(n, -1);
	for(int i=0, j=0; i<n; ++i){
		int v=order[n-i-1];
		if(comp[v]==-1){
			dfs2(v, j++);
		}
	}
	
	assignment.assign(n/2, false);
	for(int i=0; i<n; i=i+2){
		if(comp[i]==comp[i+1]){
			
			return false;
		}
		assignment[i/2]=comp[i]>comp[i+1];
	}
	return true;
}

void add(int i, int j, int b1, int b2){
	
	if(b1==0 && b2==0){
		g[2*i+1].pb(2*j);
		g[2*j+1].pb(2*i);
		gt[2*j].pb(2*i+1);
		gt[2*i].pb(2*j+1);
	}
	if(b1==1 && b2==1){
		g[2*i].pb(2*j+1);
		g[2*j].pb(2*i+1);
		gt[2*j+1].pb(2*i);
		gt[2*i+1].pb(2*j);
	}
	if(b1==0 && b2==1){
		g[2*i+1].pb(2*j+1);
		g[2*j].pb(2*i);
		gt[2*j+1].pb(2*i+1);
		gt[2*i].pb(2*j);
	}
	if(b1==1 && b2==0){
		g[2*i].pb(2*j);
		g[2*j+1].pb(2*i+1);
		gt[2*j].pb(2*i);
		gt[2*i+1].pb(2*j+1);
	}
}


main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int gs;
	cin>>gs;
	
	while(gs--){
		int N;
		cin>>N;
		int x1[N];
		int y1[N];
		int x2[N];
		int y2[N];
		for(int i=0; i<N; i++){
			cin>>x1[i]>>y1[i]>>x2[i]>>y2[i];
		}
		n=2*N;
		g.clear();
		gt.clear();
		g.resize(n);
		gt.resize(n);
		order.clear();
		used.clear();
		comp.clear();
		assignment.clear();
		bool che=1;
		
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				PT a(x1[i], y1[i]);
				PT b(x2[i], y2[i]);
				PT c(x1[j], y1[j]);
				PT d(x2[j], y2[j]);
				bool b1=LP(a, b, c, d);
				bool b2=LC(a, b, c, d);
			
				if(b1 && !b2){
					continue;
				}
				int x=seg(a, b, c, d);
				if(x){
					che=0;
					break;
				}
				PT pt=lin(a, b, c, d);
				bool pos[2][2];
				T d1=sqrt((pt.x-x1[i])*(pt.x-x1[i])+(pt.y-y1[i])*(pt.y-y1[i]));
				T d2=sqrt((pt.x-x2[i])*(pt.x-x2[i])+(pt.y-y2[i])*(pt.y-y2[i]));
				T d3=sqrt((pt.x-x1[j])*(pt.x-x1[j])+(pt.y-y1[j])*(pt.y-y1[j]));
				T d4=sqrt((pt.x-x2[j])*(pt.x-x2[j])+(pt.y-y2[j])*(pt.y-y2[j]));
				bool ch1=between(a, pt, b);
				bool ch2=between(c, pt, d);
				if(!ch1 && !ch2){
					T d11=min(d1, d2);
					T d22=max(d1, d2);
					T d33=min(d3, d4);
					T d44=max(d3, d4);
					T d55=max(d11, d33);
					T d66=min(d22, d44);
					if(d55+EPS>=d66){
						continue;
					}
					bool dir1;
					bool dir2;
					if(d1>d2){
						dir1=0;
					}
					else{
						dir1=1;
					}
					if(d3>d4){
						dir2=0;
					}
					else{
						dir2=1;
					}
					add(i, j, dir1, dir2);
					continue;
				}
				if(!ch1){
					bool dir1;
					bool dir2;
					if(d1>d2){
						dir1=0;
					}
					else{
						dir1=1;
					}
					if(min(d1, d2)<=d3+EPS){
						add(i, j, dir1, 0);
					}
					if(min(d1, d2)<=d4+EPS){
						add(i, j, dir1, 1);
					}
					continue;
				}
				bool dir2;
				if(d3>d4){
					dir2=0;
				}
				else{
					dir2=1;
				}
				if(min(d3, d4)<=d1+EPS){
					add(i, j, 0, dir2);
				}
				if(min(d3, d4)<=d2+EPS){
					add(i, j, 1, dir2);
				}
				
			}
		}
		
		bool val=f();
	
		if(val && che){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}