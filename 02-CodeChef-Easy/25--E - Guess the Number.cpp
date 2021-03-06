#define ll long long
#define maxn 1000001
#define INF 1e17
#define FOR(i,a,n) for(ll i = a ; i < n ; i++)
#define FORN(i,n) for(ll i = 0 ; i < n ; i++)
#define revFOR(i,b,a) for(ll i = b ; i >= a ; i--)
#define revFORN(i,n) for(ll i = n ; i >= 0 ; i--)

/*

                Name: Kartik Gupta
                IIT-Guwahati

*/

#include <bits/stdc++.h>
#define vll vector<ll>
#define pll pair<ll,ll>
#define plll pair<ll,pair<ll,ll>>


using namespace std;


ll askQuery(ll m)
{
      cout << 1 << " " << m << endl ; 
    ll res ; 
    cin >> res ;

    if(res == 0)
    {
        return INF ; 
    } 

    return res ; 
}

ll askQuery2(ll m)
{
    cout << 1 << " " << m << endl ; 
    ll res ; 
    cin >> res ;

    if(res == 0)
    {
        return 0 ; 
    } 

    return res ; 
}



int main( int argc , char ** argv )
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;

    long long T = 1 ; 
    cin >> T ; 

    while(T--)
    {
        ll N,X ; 
        cin >> N >> X ;



        ll left = 1 ; 
        ll right = maxn ;

        bool foundAns = false ; 
        ll ans = -1 ; 

        while(left < right)
        {
            ll mid = (right-left)/2 + left ; 
            if(mid % 2 == 0)
            {
                mid-- ; 
            }

            ll qRes = askQuery(mid) ; 


            if(qRes == X)
            {
                ans = mid ; 
                foundAns = true ; 
                break ; 
            }

            if(qRes < X)
             {
                if(mid == left)
                {
                    break ; 
                }
                left = mid ; 
            }
            else
            {
                right = mid ; 
            }
        }


        if(left == right && !foundAns)
        {
            foundAns = true ; 
            ans = -1 ; 
        }

        if(!foundAns)
        {
            /* My answer exists between l and r */
            ll qL = askQuery2(left) ;
            ll qR = askQuery2(left+2) ; 

            if(qL == X || qR == X)
            {
                foundAns = true ; 
                ans = (qL == X ? left : (left + 2)) ; 
            }
            else
            {
                ll curr = left + 1 ;
                ll pow2 = 0 ; 

                while(curr % 2 == 0)
                {
                    curr = curr / 2 ; 
                    pow2++ ; 
                }
                ll sub = 0 ;
                  pow2-- ;  

                curr = left + 1 ; 
                while(pow2 >= 0)
                {
                    sub += askQuery2( curr + (1 << (pow2)) ) ; 
                    pow2-- ; 
                }

                ll qCurr = askQuery2(curr) ;
                ll currEl = qCurr - sub ; 

                //cout << "sub currEl " << sub << " " << currEl << endl ;  

                if(currEl == X)
                {
                    foundAns = true ; 
                    ans = curr ; 
                }

            }

        }


        cout << 2 << " " << ans << endl ;
        string s ; 
        cin >> s ; 

        if(s != "YES")
        {
            break ; 
        }

    }
    
  return 0 ; 
}




