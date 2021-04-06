#include <bits/stdc++.h>
#define inp_out_work ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define testCase    int T; cin>>T; while(T--)
#define fr(i,n) for(int i=0;i<n;i++)
#define debug(P) cout<<#P<<' '<<P<<endl
#define endl '\n'

using namespace std;

typedef long long ll;

struct sub {
  ll cnt;
  ll len;
  ll left;
  ll right;

  sub(ll lef, ll rgt, ll ct, ll ln) {
    left = lef;
    right = rgt;
    cnt = ct;
    len = ln;
  }

  sub() {
    left = 0;
    right = 0;
    cnt = 0;
    len = 0;
  }

  void setVal(ll lef, ll rgt, ll ct, ll ln) {
    left = lef;
    right = rgt;
    cnt = ct;
    len = ln;
  }
};

template<typename T>
class SegTree{  //generic segment Tree
    private:

        T *tree;
        int N;
        T ZERO; // Zero value for query

        void combine(T x, T y, T &z){    //combines x, y and puts that in z
            z.left = x.left;
            z.right= y.right;
            z.len = x.len + y.len;

            if(x.left == x.len) z.left = x.left + y.left;

            if(y.right == y.len) z.right = y.right + x.right;

            z.cnt = x.cnt + y.cnt + x.right * y.left;
        }

        void build(){
            for(int i = N-1; i > 0; i--){
                combine(tree[i<<1] , tree[i<<1|1], tree[i]);
            }
        }

    public:

        SegTree(int real_n, int n){
            ZERO = sub(0, 0, 0, 0); // define zero value here
            tree = new T[2*n];

            for(int i = n; i < n + real_n; ++i) {
              tree[i].setVal(1, 1, 1, 1);
            }

            N = n;
            build();
        }

        T query(int l, int r){
            
            if(r < l) return ZERO;

            l += N;
            r += N;

            T rt = ZERO;
            T lf = ZERO;

            while(l <= r){
                if(l&1)combine(lf, tree[l++], lf);
                if(!(r&1))combine(tree[r--], rt, rt);
                l >>= 1;
                r >>= 1;
            }

            combine(lf, rt, rt);

            return rt;
        }

        void pointUpdate(int pos, T val){
            pos += N;
            tree[pos] = val;
            while(pos > 1){
                pos >>= 1;
                combine(tree[pos<<1], tree[pos<<1|1], tree[pos]);
            }
        }

};

int main() {
  inp_out_work
  
  int n, q, l, r;
  cin>>n>>q>>l>>r;

  int sz = 1;

  while(sz < n) {
    sz <<= 1;
  }

  SegTree<sub> st1(n, sz), st2(n, sz);

  while(q--) {
    int t, x, y;
    cin>>t>>x>>y;

    if(t == 1) {
      sub val;

      if(y <= l-1) {
        val.setVal(1, 1, 1, 1);
      } else {
        val.setVal(0, 0, 0, 1);
      }
      st1.pointUpdate(x-1, val);

      if(y <= r) {
        val.setVal(1, 1, 1, 1);
      } else {
        val.setVal(0, 0, 0, 1);
      }
      st2.pointUpdate(x-1, val);
    } else {
      sub val1 = st1.query(x-1, y-1);
      sub val2 = st2.query(x-1, y-1);

      /*debug(val1.cnt); debug(val2.cnt);
      
      for(int i = 0; i < n; ++i) {
        cout<< st1.query(i, i).cnt<<' ';
      }cout<< endl;

      for(int i = 0; i < n; ++i) {
        cout<< st2.query(i, i).cnt<<' ';
      }cout<<endl;*/

      cout<< val2.cnt - val1.cnt << endl;
    }
  }

}
