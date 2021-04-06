	#include<bits/stdc++.h>
	using namespace std;

	#define double long double
	#define int long long
	#define ALL(x) x.begin(),x.end()
	typedef pair<int, int> ii;
	typedef vector<int> vi;
	typedef vector<ii> vii;
	#define pb(x) push_back(x)
	#define eb emplace_back
	#define SORT(ls) sort(ls.begin(), ls.end())
	#define DESC(ls) sort(ls.rbegin(), ls.rend()) 
	#define mp(x, y) make_pair(x, y)
	#define INF 1000000000
	#define F(i, a, n) for(i=a;i<n;i++)
	#define SI(x) cin>>x
	#define DI(x, y) cin>>x>>y
	#define TI(x, y, z) cin>>x>>y>>z
	#define FI(w, x, y, z) cin>>w>>x>>y>>z
	#define SO(x) cout<<x<<"\n"
	#define DO(x, y) cout<<x<<" "<<y<<"\n"
	#define TO(x, y, z) cout<<x<<" "<<y<<" "<<z<< "\n"
	#define FO(w, x, y, z) cout<<w<<" "<<x<<" "<<y<<" "<<z<<"\n"
	#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

	const int MOD = 3046201;
	const int MAXN = 4e6 + 10;
	 
	int factorial[MAXN];
	int inv[MAXN];

	long long binpow(long long a, long long b, long long m = MOD) 
	{
	    a %= m;
	    long long res = 1;
	    while (b > 0) {
	        if (b & 1)
	            res = res * a % m;
	        a = a * a % m;
	        b >>= 1;
	    }
	    return res;
	}
	 
	int inverse(int x)
	{
	    return binpow(x, MOD - 2, MOD);
	}
	 
	void fillFactorial()
	{
	    int i;
	    factorial[0] = 1;
	    inv[0] = inverse(1);
	    F(i, 1, MAXN)
	    {
	        factorial[i] = (factorial[i - 1] * i) % MOD;
	    	inv[i] = inverse(factorial[i]);
	    }
	}
	 

	struct SegmentTreeNode {
		int sum;
	  void assignLeaf(int value) 
	  {
	  		sum = value;
	  }
	  
	  void merge(SegmentTreeNode& left, SegmentTreeNode& right) 
	  {
	  	sum = left.sum + right.sum;
	  }
	  
	  int getValue() 
	  {
	 	return sum; 	
	  }
	  
	};


	template<class T, class V>
	class SegmentTree {
	  SegmentTreeNode* nodes;
	  int N;

	public:
	  SegmentTree(T arr[], int N) {
	    this->N = N;
	    nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
	    buildTree(arr, 1, 0, N-1);
	  }
	  
	  ~SegmentTree() {
	    delete[] nodes;
	  }
	  
	  V getValue(int lo, int hi) {
	    SegmentTreeNode result = getValue(1, 0, N-1, lo, hi);
	    return result.getValue();
	  }
	  
	  void update(int index, T value) {
	    update(1, 0, N-1, index, value);
	  }
	  
	  private:	
	  void buildTree(T arr[], int stIndex, int lo, int hi) {
	    if (lo == hi) {
	      nodes[stIndex].assignLeaf(arr[lo]);
	      return;
	    }
	    
	    int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
	    buildTree(arr, left, lo, mid);
	    buildTree(arr, right, mid + 1, hi);
	    nodes[stIndex].merge(nodes[left], nodes[right]);
	  }
	  
	  SegmentTreeNode getValue(int stIndex, int left, int right, int lo, int hi) {
	    if (left == lo && right == hi)
	      return nodes[stIndex];
	    	
	    int mid = (left + right) / 2;
	    if (lo > mid)
	      return getValue(2*stIndex+1, mid+1, right, lo, hi);
	    if (hi <= mid)
	      return getValue(2*stIndex, left, mid, lo, hi);
	    	
	    SegmentTreeNode leftResult = getValue(2*stIndex, left, mid, lo, mid);
	    SegmentTreeNode rightResult = getValue(2*stIndex+1, mid+1, right, mid+1, hi);
	    SegmentTreeNode result;
	    result.merge(leftResult, rightResult);
	    return result;
	  }
	  
	  int getSegmentTreeSize(int N) {
	    int size = 1;
	    for (; size < N; size <<= 1);
	    return size << 1;
	  }
	  
	  void update(int stIndex, int lo, int hi, int index, T value) {
	    if (lo == hi) {
	    nodes[stIndex].assignLeaf(value);
	    return;
	    }
	    
	    int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
	    if (index <= mid)
	      update(left, lo, mid, index, value);
	    else
	      update(right, mid+1, hi, index, value);
	    
	    nodes[stIndex].merge(nodes[left], nodes[right]);
	  }
	};

	inline int mul(int a, int b)
	{
	    return ((a%MOD) * (b % MOD)) % MOD;
	}


	int32_t main(void)
	{
	    FASTER;
	    #ifndef ONLINE_JUDGE
	        freopen("input.txt", "r", stdin);
	        freopen("output.txt", "w", stdout);
	    #endif
	    int i, j;
	    fillFactorial();
	    int n;
	    SI(n);
	    int num[n];
	    for(int i = 0; i < n; i++)
	    	SI(num[i]);
	    SegmentTree<int, int> st(num, n);
	    int q;
	    SI(q);
	    while(q--)
	    {
	    	string type;
	    	int a, b;
	    	TI(type, a, b);
	    	if(type[0] == 'c')
	    	{
	    		st.update(a - 1, b);
	    	}
	    	else
	    	{
	    		int len = b - a + 1;
	    		int sum = st.getValue(a - 1, b - 1);
	    		if(sum == 0)
	    		{
	    			SO(1);
	    			continue;
	    		}
	    		int type1 = sum/len;
	    		int type2 = type1 + 1;
	    		int numType2 = sum % len;
	    		int numType1 = len - numType2;
	    		int ans = mul(factorial[sum], factorial[len]);
	    		ans = mul(ans, binpow(inverse(factorial[type1]), numType1));
	    		ans = mul(ans, binpow(inverse(factorial[type2]), numType2));
	    		ans = mul(ans, inv[numType1]);
	    		ans = mul(ans, inv[numType2]);
	    		SO(ans%MOD);
	    	}
	    }
	    


	    #ifdef LOCAL
	    	cout<<endl<<endl<<"Time: "<<(float)clock()/CLOCKS_PER_SEC<<" seconds"<<endl;
	    #endif
	    return 0;
	}