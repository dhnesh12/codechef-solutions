#include <iostream>
#define ll long long
#define MOD 1000000007
using namespace std;
int stree[400005];
char lazy[400005], str[100005];
void build_stree(int arr_s, int arr_e, int i){if(arr_s==arr_e){stree[i]=(str[arr_s]=='A');lazy[i]='X';return;}
	int mid = (arr_s+arr_e)/2;build_stree(arr_s, mid, 2*i);build_stree(mid+1, arr_e, 2*i+1);
	stree[i] = stree[2*i] + stree[2*i+1]; lazy[i] = 'X';}
void update_range (int arr_s, int arr_e, int qs, int qe, int i, char new_val){
	if (lazy[i] != 'X'){
		if (lazy[i] == 'A'){stree[i] = arr_e - arr_s + 1;}
		else{stree[i] = 0;}if (arr_s != arr_e){lazy[2*i] = lazy[2*i+1] = lazy[i];}lazy[i] = 'X';}
	if (arr_e < qs || arr_s > qe){return;}
	if (arr_s >= qs && arr_e <= qe){if (new_val == 'A'){stree[i] = arr_e - arr_s + 1;} else{stree[i] = 0;}
		lazy[2*i] = lazy[2*i+1] = new_val; return;}
	int mid = (arr_s+arr_e)/2; update_range(arr_s, mid, qs, qe, 2*i, new_val);
	update_range(mid+1, arr_e, qs, qe, 2*i+1, new_val); stree[i] = stree[2*i] + stree[2*i+1];}
int get(int arr_s, int arr_e, int qs, int qe, int i){
	if (lazy[i] != 'X'){if (lazy[i] == 'A'){stree[i] = arr_e - arr_s + 1;} else{stree[i] = 0;}
		if(arr_s!=arr_e){lazy[2*i] = lazy[2*i+1] = lazy[i];} lazy[i] = 'X';}
	if (arr_e < qs || arr_s > qe){return 0;} if (arr_s >= qs && arr_e <= qe){return stree[i];}
	int mid = (arr_s+arr_e)/2; return get(arr_s, mid, qs, qe, 2*i) + get(mid+1, arr_e, qs, qe, 2*i+1);}
class matrix{
public:
	ll a00, a01, a10, a11; matrix() = default;
	matrix(ll a00, ll a01, ll a10, ll a11):a00{a00}, a01{a01}, a10{a10}, a11{a11}{}
	matrix operator*(matrix m2){
		matrix ans; ans.a00 = (((a00*m2.a00)%MOD+(a01*m2.a10)%MOD)%MOD+MOD)%MOD;
		ans.a01=(((a00*m2.a01)%MOD+(a01*m2.a11)%MOD)%MOD+MOD)%MOD;
		ans.a10=(((a10*m2.a00)%MOD+(a11*m2.a10)%MOD)%MOD+MOD)%MOD;
		ans.a11=(((a10*m2.a01)%MOD+(a11*m2.a11)%MOD)%MOD+MOD)%MOD; return ans;}};
matrix pow(matrix m, int n){if (n <= 0){return matrix(1, 0, 0, 1);} matrix small_ans = pow(m, n/2);
	if (n&1){return small_ans*small_ans*m;} return small_ans*small_ans;}
void get_ans(int n, int l, int r, ll &p, ll &q){
	int num_of_a = get(0, n-1, l, r, 1), num_of_b = r - l + 1 - num_of_a;
	matrix a(1, -1, 1, 1); matrix b(1, 1, -1, 1); matrix final = pow(a, num_of_a) * pow(b, num_of_b);
	ll final_p=(((final.a00*p)%MOD+MOD)%MOD+((final.a01*q)%MOD+MOD)%MOD)%MOD;
	ll final_q=(((final.a10*p)%MOD+MOD)%MOD+((final.a11*q)%MOD+MOD)%MOD)%MOD; p = final_p; q = final_q;}
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);int t;cin >> t;while(t--){int n;cin >> n;cin >> str;
		build_stree(0, n-1, 1);int q; cin >> q;while(q--){int type, l, r; ll p, q; char c;
			cin >> type >> l >> r; if (type == 1){cin >> c;update_range(0, n-1, l-1, r-1, 1, c);}
			else{cin >> p >> q; get_ans(n, l-1, r-1, p, q); cout << p << " " << q << '\n';}}}}