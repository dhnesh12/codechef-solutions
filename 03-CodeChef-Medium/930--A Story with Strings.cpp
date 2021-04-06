#include <bits/stdc++.h>
using namespace std;
#define FastRead ios_base::sync_with_stdio(false);cin.tie(NULL);
#define lli long long int
#define sz 250007
lli pow1[sz+1];
lli pow2[sz+1];
struct hash_pair {
   size_t operator()(const pair<lli,lli>&x)const{
   return (lli)x.first * 94 + x.second;
 }
};

void cal_pow(){
    lli base1 = 3207, base2 = 3721;
    lli mod1 = 1000003999, mod2 = 1000000861;
    pow1[0] = 1; pow2[0] = 1;
    for(lli i=1; i<sz; i++){
        pow1[i] = (pow1[i-1] *1L* base1) % mod1;
        pow2[i] = (pow2[i-1] *1L* base2) % mod2;
    }
}
class HASH{
    lli base1; lli base2;
    lli mod1; lli mod2;
    lli hashV1; lli hashV2;
    // lli hash_arr1[2002][2002];
    // lli hash_arr2[2002][2002];
    lli prefix_hash1[sz+1]; // size = len of string
    lli prefix_hash2[sz+1];
    // lli pow1[sz+1];
    // lli pow2[sz+1];
    lli calculate_hash(lli h, lli m, lli b, lli c){
        h = (h*1L*b) % m;
        h = (h*1L+ (c + 1)) % m;// adding 1 so that 0 does not occur
        //h %= m;
        return h;
    }
public:
    HASH(){
        base1 = 3207; base2 = 3721;
        mod1 = 1000003999; mod2 = 1000000861;
        hashV1 = 0; hashV2 = 0;
        // pow1[0] = 1; pow2[0] = 1;
        // for(lli i=1; i<sz; i++){
        //     pow1[i] = (pow1[i-1] *1L* base1) % mod1;
        //     pow2[i] = (pow2[i-1] *1L* base2) % mod2;
        // }
    }
    /*void hash_every_sub_string(string s){ // hash table in 0 base index
    	for(int i=0;i<s.size();i++){
            hashV1 = 0; hashV2 = 0;
            for(int j=i;j< s.size();j++){
                hashV1 = (hashV1*base1) % mod1;
                hashV1 += (s[j] + 1);
                hashV1 %= mod1;
                
                hashV2 = (hashV2*base2) % mod2;
                hashV2 += (s[j] + 1);
                hashV2 %= mod2;
 
                hash_arr1[i][j]  = hashV1; // for this we need 2D hash tables
                hash_arr2[i][j]  = hashV2;
            }
    	}
    }*/
    void create_prefix_hash_table(string s){ // hash table in 0 base index
        lli ln = s.size();
        for(lli i=0; i<ln; i++){
            hashV1 = calculate_hash(hashV1, mod1, base1, s[i]);
            hashV2 = calculate_hash(hashV2, mod2, base2, s[i]);
            prefix_hash1[i] = hashV1;
            prefix_hash2[i] = hashV2;
        }
    }
    // pair<lli,lli> hash_total_string(string s){
    //     hashV1 = 0; hashV2 = 0;
    //     for(lli j=0;j<s.size();j++){
    //         hashV1 = calculate_hash(hashV1, mod1, base1, s[j]);
    //         hashV2 = calculate_hash(hashV2, mod2, base2, s[j]);
    //     }
    //     pair<lli,lli> pr = {hashV1,hashV2};
    //     return pr;
    // }
    pair<lli,lli> hash_val(lli i,lli j){// 0 index based query
        // pair<lli,lli> pr = {hash_arr1[i][j], hash_arr2[i][j]}; // for 2D hash table
        pair<lli,lli> pr = {prefix_hash1[j], prefix_hash2[j]};
        if(i != 0)
            pr = {(mod1*1L + ((prefix_hash1[j] - prefix_hash1[i-1] *1L* pow1[j-i+1]) % mod1)) % mod1,
                (mod2*1L + ((prefix_hash2[j] - prefix_hash2[i-1] *1L* pow2[j-i+1]) % mod2)) % mod2};
        //cout<<"["<<pr.first<<", "<<pr.second<<"] ";
        return pr;
    }
};


int main() {
   // FastRead
    char  s1[sz],s2[sz];
    //cin>>s1>>s2;
    scanf("%s%s",s1,s2);
    cal_pow();
    HASH hs1, hs2;
    hs1.create_prefix_hash_table(s1);
    hs2.create_prefix_hash_table(s2);
    ////// binary search on the length
    lli l1 = strlen(s1);
    lli l2 = strlen(s2);
    lli l = 0, h = l2;
    pair<lli,lli> res = {-1,-1}; // <pos,len>
    while(l<=h){
        lli m = (l+h) / 2;
        //unordered_map< pair<int,int>, bool, hash_pair> mp;
        unordered_set<pair<lli, lli>, hash_pair> st;
        lli p = l1-m+1;
        for(lli i=0; i+m-1 < l1; i++){
           // mp[hs1.hash_val(i, i+m-1)] = true;
           st.insert( hs1.hash_val(i, i+m-1) );
        }
        bool flg = false;
        p = l2-m+1;
        for(lli i=0; i+m-1 < l2; i++){
            //if(mp[hs2.hash_val(i, i+m-1)] == true){
            if(st.find(hs2.hash_val(i, i+m-1) ) != st.end()){
                res  = {i,i+m-1};
                flg = true;
                break;
            }
        }
        if(flg == true) l = m+1;
        else h = m-1;
    }
    if(res.second == -1){
        printf("0");
    }else{
        for(lli i=res.first; i<=res.second; i++){
            printf("%c",s2[i]);
        }printf("\n%lld",res.second-res.first+1);
    }
    // cout<<endl<<res.first;
}