#include<bits/stdc++.h>
// #pragma optimize("-O3")
//  #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,avx,mmx,tune=native")
using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define INF 1e9
#define BIG_INF 1e18
#define vi vector<ll>
#define sz(a) ll((a).size())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1)
// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
// typedef tree<
// ll,
// null_type,
// less<ll>,
// rb_tree_tag,
// tree_order_statistics_node_update>
// ordered_set;
 
typedef long long ll;
ll mod = 998244353;
 long long fast_exp(long long a, long long b)
{
    if(b <= 0)
       return 1;
    else
    {
       long long res = 1;
       res = fast_exp(a,b/2);
       res = (res*res)%mod;
       if(b%2 == 1)
          res = (res*a)%mod;
       return res;
 
    }
}

typedef long double ld;
const long long N = 3e5+10;

// struct node{
//     int random = 0;
//     int dist = 0;
//     int num;

//     bool operator < (node b)
//     {
//         if(a.)
//     }
// }

bool dp[50][70][3000];
int par[50][70][3000];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //freopen("elimination_input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    
    dp[0][0][0] = true;
    for(int i = 1; i<50; i++)
    {
        for(int j = i; j<70; j++)
        {
            for(int choice = 0; choice < 3000; choice++)
            {
                for(int put_here = 1; put_here <= j; put_here++)
                {

                    if(choice - put_here * put_here >= 0 && dp[i-1][j-put_here][choice- put_here * put_here] == true)
                    {
                        dp[i][j][choice] = true;
                        par[i][j][choice] = put_here;
                    }
                }
            }
        }
    }

    // int a , b, c;
    // cin >> a >> b >> c;
    // cout << dp[a][b][c] << '\n';

    int t;
    cin >> t;
    int p[600] = {};
    int sum = 0;
    for(int i = 1; i + sum <= 500; i++)
    {
        sum+=i;
        p[sum] = i;
    }

    int start = 1;
    while(t--)
    {
        int k;
        cin >> k;
        //k = start;
        //cout << "k: "<< k << '\n';
        //start++;

        
        if(k == 1)
        {
            cout << 2 << '\n';
            cout << 1 << " " << 2 << '\n';

        }
        else if(p[k] > 0)
        {
            cout << p[k]+2 << '\n';
            for(int i = 2; i<= p[k]+2; i++)
                cout << 1 << " " << i << '\n';
        }
        else
        {
            int cost_type_1 = 10000;
            int chosen_i = 1;
            for(int i = 1; i<=k; i++)
            {
                if(k % i == 0)
                {
                    int cur_cost = k/i + i + 2;
                    
                    if(cur_cost <  cost_type_1)
                    {
                        cost_type_1 = cur_cost;
                        chosen_i = i;
                    }
                }
            }
        

            int cost_type_2 = 10000;
            int ch_left, ch_right, ch_cen, ch_cenjoin;
            vector <int> final_distribution;
            for(int left = 1; left <= 500 ; left++)
            {
                for(int right = 1; right <= 500; right++)
                {
                    if(left * right > k)
                        break;
                    for(int centre = 1; centre <= 500; centre++)
                    {
                        if((centre * (centre-1))/2  + centre * (left + right) + left * right > k)
                            break;
                        for(int cen_joined = 0; cen_joined <= 500 ; cen_joined++)
                        {
                            int cur_cost = 2 * centre + right + left + 3 + cen_joined;
                            int paths = (centre * (centre-1))/2  + centre * (left + right) + left * right + cen_joined * (left + right);
                            if(paths > k)
                                break;
                            paths -= (centre * (centre-1))/2;
                            int cen_sum = centre + cen_joined;
                            paths = 2 * paths + (cen_sum * cen_sum);
                            int asquare = paths - 2*k;
                            if(asquare >= 3000)
                                break;
                            if(dp[centre][cen_sum][asquare] && cur_cost < cost_type_2)
                            {
                                ch_left =  left;
                                ch_right = right;
                                ch_cen = centre;
                                cost_type_2 = cur_cost;
                                ch_cenjoin = cen_joined;
                                vector <int> distro;
                                int ci = centre, cj = cen_sum, tasq = asquare;
                                while(ci > 0)
                                {
                                    int val_placed  = par[ci][cj][tasq];
                                    distro.pb(val_placed);
                                    ci -= 1;
                                    cj -= val_placed;
                                    tasq -= val_placed * val_placed;
                                }
                                final_distribution = distro;

                            }
                        }
                    }
                }
            }
            if(cost_type_1 <= cost_type_2)
            {
                cout << cost_type_1 << '\n';
                    
                    for(int i = 2; i<= chosen_i+1; i++)
                        cout << 1 << " " << i << '\n';
                    cout << 1 << " " << chosen_i + 2 << '\n';
                    for(int i = chosen_i+3; i<chosen_i+3+k/chosen_i; i++)
                        cout << chosen_i+2 << " " << i << '\n';
                
            }
            else
            {
                cout << cost_type_2 << '\n';
                int left = 1;
                int centre = left + ch_left + 1;
                int right = centre + 2 * ch_cen + 1;
                cout << left << " " << centre << '\n';
                cout << centre << " " << right << '\n';
                for(int i = left+1; i<centre; i++)
                    cout << left << " " << i << '\n';
                for(int i = centre+1; i<right; i+=2)
                {
                    cout << centre << " " << i << '\n';
                    cout << i << " " << i+1 << '\n';
                }
                for(int i = right+1; i<right+1+ch_right; i++)
                    cout << right << " " << i << '\n';
                int ptr = 0;
                int latest_node = right+1+ch_right;
                for(int i = centre+1; i<right; i+=2)
                {
                    while(final_distribution[ptr] > 1)
                    {
                        final_distribution[ptr]--;
                        cout << i << " " << latest_node << '\n';
                        latest_node++;
                    }
                    ptr++;
                }
                






                // for(int i = right+1+ch_right; i< right+1+ch_right+ch_cenjoin; i++)
                //     cout << centre+1 << " " << i << '\n';
             }
        }
    }




    // cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
    return 0;
    
    
}











