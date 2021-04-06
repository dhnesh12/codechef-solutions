#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;

const ll mod = 1e9+7;
const int maxn = 1e6 + 5;



int n;
int a[maxn];

int sum[maxn];

void add_lin(int l, int r) {
    int cur=r-l+1;
    for (int i=l; i<=r; i++) {
	sum[i] += (cur--);
    }
}

int range_gcd(int l, int r) {
    int g = a[l];
    for (int i=l; i<=r; i++) g = __gcd(g, a[i]);
    return g;
}


int count() {
    int res=0;
    for (int i=1; i<=n; i++) {
	int g=0;
	for (int j=i; j<=n; j++) {
	    g=__gcd(g,a[j]);
	    if (g>1) res++;
	}
    }
    return res;
}

int brute() {
    int res = 0;
    for (int i=1; i<=n; i++) {
	for (int b=1; b<=5000; b++) {
	    int tmp=a[i];
	    a[i]=b;
	    res=max(res,count());
	    //if (res==16 && b<=500) cout<<"!! "<<i<<": "<<a[i]<<endl;
	    a[i]=tmp;
	}
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    cin>>n;
    for (int i=1; i<=n; i++) {
	cin>>a[i];
    }

    assert(n<=100);

    if (n<=2) {
	if (n==1) out(1);
	if (n==2) out(3);
	assert(false);
    }

    deque<pair<int,int>> qq;
    for (int i=1,j=1; i<=n; i++) {
	while (j<=n && (qq.empty() || __gcd(qq.back().second,a[j])>1)) {
	    int curg = a[j];
	    if (!qq.empty()) curg = __gcd(a[j], qq.back().second);
	    qq.push_back({j, curg});
	    j++;
	}
	assert(!qq.empty() && qq.front().first==i);
	int r = qq.back().first;
	add_lin(i, r);
	qq.pop_front();
    }



    int all = 0;
    for (int i=1; i<=n; i++) {
	all += sum[i];
    }
    
    int mx = 0;


    for (int i=1; i<=n; i++) {
	int gL = 0;
	int L=i;
	while (L>1 && gL!=1) {
	    if (__gcd(gL, a[L-1]) ==1) {
		gL=max(1,gL);
		break;
	    }
	    gL=__gcd(gL, a[--L]);
	}

	int gR = 0;
	int R=i;
	while (R<n && gR!=1) {
	    if (__gcd(gR, a[R+1])==1) {
		gR=max(1,gR);
		break;
	    }
	    gR=__gcd(gR,a[++R]);
	}

	//cout<<i<<": "<<"["<<L<<","<<R<<"]"<<endl;

	// [gL, gR]
	int need = 0;
	if (gL>0 && gR>0) {
	    //cout<<i<<": "<<gL<<" "<<gR<<endl;
	    need = gL*gR/__gcd(gL,gR);
	} else if (gL>0) {
	    need = gL;
	} else if (gR>0) {
	    need = gR;
	} else {
	    assert(false);
	}

	assert(need <= int(5e5));
	int save = a[i];
	a[i] = need;
	int cur = count();
	a[i] = save;
	//int cur = all - sum[i] + 1 + (i-L)*(R-i);
	// cout<<i<<": "<<cur<<endl;
	// watch(need);
	mx = max(mx, cur);
    }

    // watch(brute());
    // watch(mx);
    // assert(mx == brute());
    
    cout<<mx<<endl; 
    return 0;
}
