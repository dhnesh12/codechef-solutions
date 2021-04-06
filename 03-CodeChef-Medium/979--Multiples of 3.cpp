#include<bits/stdc++.h>
using namespace std;
#define ll int
#define vl vector<ll>
#define  mp map<ll>
#define fi first
#define si second
#define f(a,b) for(ll i=a;i<b;i++)
#define pb push_back
const ll nax=1e5+3;
struct node{
	ll a[3];
};
node st[400004];
ll lazy[400004];

void shift(ll si){
ll  x=st[si].a[2];
st[si].a[2]=st[si].a[1];
st[si].a[1]=st[si].a[0];
st[si].a[0]=x;
}
void build(ll si,ll ss,ll se){

if(ss==se){
	st[si].a[0]=1;
		st[si].a[1]=0;
		st[si].a[2]=0;
		return;
}

ll mid=(ss+se)/2;
build(2*si,ss,mid);
build(2*si+1,mid+1,se);
st[si].a[0]=st[2*si].a[0]+st[2*si+1].a[0];
st[si].a[1]=st[2*si].a[1]+st[2*si+1].a[1];
st[si].a[2]=st[2*si].a[2]+st[2*si+1].a[2];


}
ll query(ll si,ll ss,ll se,ll qs,ll qe){

if(lazy[si]!=0){

ll add=lazy[si];
lazy[si]=0;
if(ss!=se){
	lazy[2*si]+=add;
	lazy[2*si+1]+=add;
}
add=add%3;
for(ll i=0;i<add;i++){
	shift(si);}}
if(ss>qe||qs>se){
	return 0;
}

if(ss>=qs&&se<=qe){
	return st[si].a[0];
}

int mid=(ss+se)/2;

return query(2*si,ss,mid,qs,qe)+query(2*si+1,mid+1,se,qs,qe);

}

void update(ll si,ll ss,ll se,ll qs,ll qe){


if(lazy[si]!=0){

int add=lazy[si];
lazy[si]=0;
if(ss!=se){
	lazy[2*si]+=add;
	lazy[2*si+1]+=add;
}
add=add%3;
for(ll i=0;i<add;i++){
	shift(si);}}
if(ss>qe||qs>se){
	return ;
}

if(ss>=qs&&se<=qe){
shift(si);

if(ss!=se){
lazy[2*si]++;
lazy[2*si+1]++;}
return ;
}
int mid=(ss+se)/2;

update(2*si,ss,mid,qs,qe);
update(2*si+1,mid+1,se,qs,qe);

st[si].a[0]=st[2*si].a[0]+st[2*si+1].a[0];
st[si].a[1]=st[2*si].a[1]+st[2*si+1].a[1];
st[si].a[2]=st[2*si].a[2]+st[2*si+1].a[2];


}




int main(){
	
ll n,q;
cin>>n>>q;

build(1,1,n);
while(q--){
ll x,b,c;
scanf("%d %d %d",&x,&b,&c);
if(x==0){
update(1,1,n,b+1,c+1);

}else{
	cout<<query(1,1,n,b+1,c+1)<<'\n';
}


}


return 0;
}