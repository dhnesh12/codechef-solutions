#include<bits/stdc++.h>

using namespace std;

/***template***/
#define ll                   long long
#define dd                   double
#define scl(n)               scanf("%lld",&n)
#define scd(n)               scanf("%lf",&n)
#define pi                   pair<ll,ll>
#define pb                   push_back
#define mp                   make_pair
#define uu                   first
#define vv                   second
#define FOR(i,n)             for(ll i=1;i<=n;i++)
#define LOOP(i,n)            for(ll i=0;i<n;i++)
#define FOOR(i,a,b)          for(ll i=a;i<=b;i++)
#define LOP(i,a,b)           for(ll i=a;i<b;i++)
#define sorted(s)            sort(s.begin(),s.end())
#define reversed(s)          reverse(s.begin(),s.end())
#define contains(a,b)        (find((a).begin(), (a).end(), (b)) != (a).end())
#define MAXN                 10004
#define pii                  3.1415926536
#define mod                  1000000007
#define eps                  0.0000000001
#define inf                  9000000000000000
#define mstt(a,b)            memset((a),(b),sizeof (a))

//priority_queue<ll, vector<ll>, greater<ll> >q


vector< string > seg[105];

vector< pi >cntvec;

map<string, ll> m;

ll check(ll i,ll j)
{
    ll cnt = cntvec[i].vv;

    ll tot = 1;

    ll od = 0, ev = 0;


    LOOP(k, seg[j].size() - 1)
    {
        if(seg[j][k] == "odd")
            od++;
        else
        {
//            cout<<"hoy na"<<endl;
            if(seg[j][k] == "even")
                ev++;
            else
                tot *= m[seg[j][k]];
        }
        if(tot > cnt)
            break;
    }

    if(seg[j][seg[j].size() - 1] == "odd")
    {
        if(cntvec[i].uu % 2 == 0)
            return 0;
    }
    else
    {
        if(seg[j][seg[j].size() - 1] == "even")
        {
//            cout<<"dhuktese "<<endl;
            if(cntvec[i].uu % 2 == 1)
                return 0;
        }
        else
        {
            if(m[seg[j][seg[j].size() - 1]] != cntvec[i].uu)
                return 0;
        }
    }

//    cout<<"ekhane more"<<endl;

    if(tot == 0)
        return 0;

    if((cnt % tot) != 0)
        return 0;

//    cout<<"ashe na"<<endl;

    ll last = 0;

    cnt /= tot;

//    cout<<"r koto"<<endl;

//    cout<<cnt<<endl;

    while(cnt % 2 == 0)
    {
//        cout<<last<<endl;
        cnt /= 2;
        last++;
    }


    if(last > 3 * ev)
        return 0;

    if(ev > last)
        return 0;

    last = last - ev;

    while(last > 0)
    {
//        cout<<last<<endl;
        last -= 2;
        ev--;
    }

    last = cnt;

//    cout<<"vai"<<endl;

    tot = 3;

    while(tot > 1 && ev > 0 && last > 1)
    {
        if(last % tot == 0)
        {
            last /= tot;
            ev--;
        }
        else
            tot -= 2;
    }

    tot = 9;

    while(tot > 1 && od > 0 && last > 1 )
    {
        if(last % tot == 0)
        {
            last /= tot;
            od--;
        }
        else
            tot -= 2;
    }

    if(last != 1)
        return 0;


    return 1;
}


int main()
{
    m["zero"] = 0;
    m["one"] = 1;
    m["two"] = 2;
    m["three"] = 3;
    m["four"] = 4;
    m["five"] = 5;
    m["six"] = 6;
    m["seven"] = 7;
    m["eight"] = 8;
    m["nine"] = 9;

    ll test;
    scl(test);

    FOR(cs,test)
    {
        cntvec.clear();

        seg[1].clear();

        string s;

        ll cnt = 1;

        while(1)
        {
            cin>>s;

            ll sz = s.size();

            if(s[sz - 1] != '.' && s[sz - 1] !=',' )
            {
                seg[cnt].pb(s);
                continue;
            }

            string str;

            if(s[sz - 1] == ',')
            {
                LOOP(j, sz - 1)
                    str+=s[j];

                seg[cnt++].pb(str);

                seg[cnt].clear();
            }
            else
            {
                LOOP(j, sz - 1)
                    str+=s[j];

                seg[cnt].pb(str);

                break;
            }
        }

        ll n;

        scl(n);

        string str;

        cin>>str;

        cntvec.pb(mp(str[0] - '0', 1));

        FOR(i, n - 1)
        {
            if(str[i] == str[i - 1])
                cntvec.back().vv++;
            else
                cntvec.pb(mp(str[i] - '0', 1));
        }

        if(cnt < cntvec.size())
        {
            printf("Case %lld: NO\n",cs);
            continue;
        }

        ll a = 0, b = 1;

        while(a < cntvec.size() && b <= cnt)
        {
            if(check(a,b))
            {
//                cout<<a<<" "<<b<<endl;
                a++;
            }

            b++;
        }


        if(a == cntvec.size())
            printf("Case %lld: MAY BE\n",cs);
        else

            printf("Case %lld: NO\n",cs);
    }

}
