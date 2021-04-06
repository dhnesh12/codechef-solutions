#include<bits/stdc++.h>
using namespace std;
const int M=100005;
struct treap{
	int f,sz,val,lat,pri;
	long long sum;
	treap *par,*ch[2];
	void* operator new(size_t _){
		static treap Pool[M*4],*allc=Pool;
		return allc++;
	}
	inline bool dir(){
		return par->ch[1]==this;
	}
	inline void update_add(int x){
		val+=f*x;
		sum+=sz*x;
		lat+=x;
	}
	inline void push_up(){
		sz=f;
		sum=val;
		if(ch[0]!=nullptr){
			sz+=ch[0]->sz;
			sum+=ch[0]->sum;
		}
		if(ch[1]!=nullptr){
			sz+=ch[1]->sz;
			sum+=ch[1]->sum;
		}
	}
	inline void push_down(){
		if(lat!=0){
			if(ch[0]!=nullptr)
				ch[0]->update_add(lat);
			if(ch[1]!=nullptr)
				ch[1]->update_add(lat);
			lat=0;
		}
	}
};
treap *l[M*2],*r[M*2],*stk[M*2],*arr[M*2];
vector<int>E[M];
long long lastans;
int n,m,top,cnt;
inline void sch(treap*p,treap*q,bool f){
	p->ch[f]=q;
	if(q!=nullptr) q->par=p;
}
inline void rotate(treap*p){
	treap*q=p->par;
	bool f=p->dir();
	if(q->par!=nullptr)
		q->par->ch[q->dir()]=p;
	p->par=q->par;
	sch(q,p->ch[!f],f);
	sch(p,q,!f);
	q->push_up();
}
treap* merge(treap*p,treap*q){
	if(p==nullptr)
		return q;
	if(q==nullptr)
		return p;
	p->push_down();
	q->push_down();
	if(p->pri<q->pri){
		sch(p,merge(p->ch[1],q),1);
		p->push_up();
		return p;
	}else{
		sch(q,merge(p,q->ch[0]),0);
		q->push_up();
		return q;
	}
}
void build(treap**arr,int n){
	for(int i=0;i<n;++i){
		treap*p=arr[i],*last=nullptr;
		while(top!=0 and p->pri<stk[top-1]->pri){
			last=stk[--top];
			last->push_up();
		}
		sch(p,last,0);
		if(top!=0)
			sch(stk[top-1],p,1);
		stk[top++]=p;
	}
	while(top!=0)
		stk[--top]->push_up();
}
void down_to(treap*p){
	while(p!=nullptr){
		stk[top++]=p;
		p=p->par;
	}
	while(top!=0)
		stk[--top]->push_down();
}
void up_to(treap*p){
	while(p!=nullptr){
		p->push_up();
		p=p->par;
	}
}
void insert(treap*p,treap*q){
	down_to(p);
	sch(p,merge(q,p->ch[1]),1);
	p->push_up();
	while(q->par!=nullptr and q->pri<q->par->pri)
		rotate(q);
	up_to(q);
}
void update(treap*p,treap*q,int x){
	long long res=0;
	bool f0=false,f1=true;
	down_to(p);
	down_to(q);
	while(p!=q){
		if(q->pri<p->pri){
			if(!f0){
				if(p->ch[1]!=nullptr)
					p->ch[1]->update_add(x);
				p->val+=p->f*x;
			}
			p->push_up();
			f0=p->dir();
			p=p->par;
		}else{
			if(f1){
				if(q->ch[0]!=nullptr)
					q->ch[0]->update_add(x);
				q->val+=q->f*x;
			}
			q->push_up();
			f1=q->dir();
			q=q->par;
		}
	}
	p->val+=p->f*x;
	up_to(p);
}
long long query(treap*p,treap*q){
	long long res=0;
	bool f0=false,f1=true;
	down_to(p);
	down_to(q);
	while(p!=q){
		if(q->pri<p->pri){
			if(!f0)
				res+=p->val+(p->ch[1]==nullptr?0:p->ch[1]->sum);
			f0=p->dir();
			p=p->par;
		}else{
			if(f1)
				res+=q->val+(q->ch[0]==nullptr?0:q->ch[0]->sum);
			f1=q->dir();
			q=q->par;
		}
	}
	return res+p->val;
}
void clear(treap*p,treap*q){
	bool f0=false,f1=true;
	down_to(p);
	down_to(q);
	while(p!=q){
		if(q->pri<p->pri){
			if(!f0){
				f0=p->dir();
				sch(p->par,p->ch[0],f0);
			}else{
				f0=p->dir();
				p->push_up();
			}
			p=p->par;
		}else{
			if(f1){
				f1=q->dir();
				sch(q->par,q->ch[1],f1);
			}else{
				f1=q->dir();
				q->push_up();
			}
			q=q->par;
		}
	}
	p=q->par;
	if(p!=nullptr){
		sch(p,merge(q->ch[0],q->ch[1]),q->dir());
		up_to(p);
	}else
		merge(q->ch[0],q->ch[1])->par=nullptr;
}
void dfs(int u,int fa){
	arr[cnt++]=l[u];
	for(int i=0;i<(int)E[u].size();++i){
		int v=E[u][i];
		if(v!=fa)
			dfs(v,u);
	}
	arr[cnt++]=r[u];
}
int main(){
	srand(19260817);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int val;
		scanf("%d",&val);
		l[i]=new(treap){1,1,val,0,rand(),val,nullptr,{nullptr,nullptr}};
		r[i]=new(treap){0,0,0,0,rand(),0,nullptr,{nullptr,nullptr}};
	}
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		E[u+1].push_back(v+1);
		E[v+1].push_back(u+1);
	}
	dfs(1,-1);
	build(arr,n*2);
	scanf("%d",&m);
	while(m--){
		int op,val;
		long long key;
		scanf("%d",&op);
		if(op==1){
			scanf("%lld%d",&key,&val);
			key+=lastans+1;
			l[n+1]=new(treap){1,1,val,0,rand(),val,nullptr,{nullptr,nullptr}};
			r[n+1]=new(treap){0,0,0,0,rand(),0,nullptr,{nullptr,nullptr}};
			insert(l[key],l[n+1]);
			insert(l[n+1],r[n+1]);
			++n;
		}else if(op==2){
			scanf("%lld%d",&key,&val);
			key+=lastans+1;
			update(l[key],r[key],val);
		}else if(op==3){
			scanf("%lld",&key);
			key+=lastans+1;
			clear(l[key],r[key]);
		}else if(op==4){
			scanf("%lld",&key);
			key+=lastans+1;
			lastans=query(l[key],r[key]);
			printf("%lld\n",lastans);
		}
	}
	return 0;
}