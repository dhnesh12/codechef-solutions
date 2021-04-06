#include<bits/stdc++.h>
using namespace std;
struct{
	int sum,left,right;
} seg[2400005];
int n,q,cnt=0,freq[600005],a[100005],idx[500005],typ[500005],val[500005],num[600005];
map<int,int> my;
map<int,int> :: iterator it;
void update(int node,int start,int end,int i){
	if(start>end||i<start||end<i) return;
	if(start==end){
		seg[node].sum = seg[node].left = seg[node].right = freq[i];
		return ;
	}
	int mid=(start+end)/2;
	update(node<<1,start,mid,i);
	update(node<<1|1,mid+1,end,i);
	if(num[mid+1]==num[mid]+1 && freq[mid] && freq[mid+1]){
		seg[node].sum = seg[node<<1].sum + seg[node<<1|1].sum - seg[node<<1].right - seg[node<<1|1].left + min(seg[node<<1].right,seg[node<<1|1].left);
		seg[node].right = (seg[node<<1|1].right==seg[node<<1|1].sum ? min(seg[node<<1].right,seg[node<<1|1].right) : seg[node<<1|1].right);
		seg[node].left = (seg[node<<1].left==seg[node<<1].sum ? min(seg[node<<1].left,seg[node<<1|1].left) : seg[node<<1].left) ;
	}else{
		seg[node].sum = seg[node<<1].sum + seg[node<<1|1].sum ;
		seg[node].right = seg[node<<1|1].right;
		seg[node].left = seg[node<<1].left;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		my[a[i]]=1;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&typ[i]);
		if(typ[i]==1){
			scanf("%d%d",&idx[i],&val[i]);
			my[val[i]]=1;
		}
	}
	for(it = my.begin();it!=my.end();it++){
		it->second = ++cnt;
		num[cnt] = it->first;
	}
	for(int i=0;i<=cnt;i++){
		seg[i].sum=seg[i].left=seg[i].right=0;
	}
	for(int i=1;i<=n;i++){
		a[i] = my[a[i]];
		freq[a[i]]++;
	}
	for(int i=1;i<=q;i++){
		if(typ[i]==1){
			val[i] = my[val[i]];
		}
	}
	for(int i=1;i<=cnt;i++){
		update(1,1,cnt,i);
	}
	for(int i=1;i<=q;i++){
		if(typ[i]==1){
			freq[a[idx[i]]]--;
			update(1,1,cnt,a[idx[i]]);
			a[idx[i]] = val[i];
			freq[a[idx[i]]]++;
			update(1,1,cnt,a[idx[i]]);
		}else{
			printf("%d\n",seg[1].sum);
		}
	}
	return 0;
}