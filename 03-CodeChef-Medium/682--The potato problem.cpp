#include<bits/stdc++.h>

using namespace std;

#define ios               ios_base::sync_with_stdio(false);
#define ifs               ifstream cin; cin.open ("D:\\PPI\\EasyForm\\ccc\\input.txt");
#define ofs               ofstream cout; cout.open ("D:\\PPI\\EasyForm\\ccc\\output.txt");
#define iof               ifs ofs
#define ll                long long
#define ld                long double
#define da(x,i)           cout << #x << "[" << i << "] = " << x[i] << "\n"
#define da2(x,i,y,j)      cout << #x << "[" << i << "] = " << x[i] << " ! " << #y << "[" << j << "] = " << y[j] << "\n"
#define d2a(x,i,j)        cout << #x << "[" << i << "][" << j << "] = " << x[i][j] << "\n"
#define db(x)             cout << #x << " = " << (x) << "\n"
#define db2(x,y)          cout << #x << " = " << (x) << " ! " << #y << " = " << (y) << "\n"
#define db3(x,y,z)        cout << #x << " = " << (x) << " ! " << #y << " = " << (y) << " ! " << #z << " = " << (z) << "\n"
#define db4(w,x,y,z)      cout << #w << " = " << (w) << " ! " << #x << " = " << (x) << " ! " << #y << " = " << (y) << " ! " << #z << " = " << (z) << "\n"
#define inf               LLONG_MAX

const ld zero = 1e-15;

struct PT
{
        ld x,y;
        const ll in = 1e10;

        void operator = (const PT &a)
        {
                x = a.x; y = a.y;
        }

        bool operator == (const PT &a) const
        {
                return y == a.y and x == a.x;
        }

        bool operator < (const PT &a) const
        {
                return y < a.y or
                       (y == a.y and x < a.x);
        }

        PT operator + (const PT &a) const
        {
                return {y+a.x,y+a.y};
        }

        PT operator - (const PT &a) const
        {
                return {x-a.x,y-a.y};
        }

        PT operator * (const ld &a) const
        {
                return {x*a,y*a};
        }

        PT operator / (const ld &a) const
        {
                return {x/a,y/a};
        }

        ld operator ^ (const PT &a) const // dot
        {
                return x*a.x + y*a.y;
        }

        ld operator & (const PT &a) const // cross
        {
                return x*a.y - y*a.x;
        }

        ld dal()
        {
                if(x) return y/x;
                return in;
        }

        ld val()
        {
                return sqrt(x*x + y*y);
        }

        PT unit()
        {
                PT a = *this;
                return a/a.val();
        }

        void inp()
        {
                cin >> x >> y;
        }

        void oup()
        {
                cout << x << " " << y << "\n";
        }
};



ll ori(PT a,PT b,PT c)
{
        PT ab = b-a, bc = c-b;
        ld sin_b = ab&bc;
        if(sin_b > 0) return 1; //ccw
        if(sin_b < 0) return -1; //cw
        return 0;
}

ll area(vector<PT> &a)
{
        ll sum = 0;
        for(ll i = 0; i < a.size(); i++)
        {
                PT p = i ? a[i-1] : a.back();
                PT q = a[i];
                sum += p & q;
        }
        return abs(sum);
}

ll tarea(PT a,PT b,PT c)
{
        vector<PT> t = {a,b,c};
        return area(t);
}

ll convex_hull(vector<PT> &a,vector<PT> &b)
{
        sort(a.begin(),a.end());
        vector<PT> ri,le;
        ri = le = {a[0]};
        for(ll i = 0; i < a.size(); i++)
        {
                if(i+1 == a.size() or ori(a[0],a[i],a.back()) == 1)
                {
                        for( ; ri.size() >= 2 and
                        ori(ri[ri.size()-2],ri.back(),a[i]) != 1;
                        b.push_back(ri.back()), ri.pop_back());

                        ri.push_back(a[i]);
                }
                if(i+1 == a.size() or ori(a[0],a[i],a.back()) == -1)
                {
                        for( ; le.size() >= 2 and
                        ori(le[le.size()-2],le.back(),a[i]) != -1;
                        b.push_back(le.back()), le.pop_back());

                        le.push_back(a[i]);
                }
        }
        a = ri;
        for(ll i = le.size()-2; i; i--) a.push_back(le[i]);
}

int main()
{
        ll tt, tc = 0; cin >> tt;
        while(tt--)
        {
                ll n; cin >> n;
                vector<PT> a(n),b,ul;
                for(ll i = 0; i < n; i++) a[i].inp();

                convex_hull(a,b);
                ll bz = b.size(), az = a.size();
                if(!bz or az < 3)
                {
                        cout << -1 << "\n"; continue;
                }

                ll se = area(a);
                ll tsz = inf;

                convex_hull(b,ul);
                bz = b.size();

                ll po = 0;
                ll mini = inf, mipo;
                for(po = 0; po < bz; po++)
                {
                        ll z = tarea(b[po],a[0],a[1]);
                        if(z < mini)
                        {
                                mini = z; mipo = po;
                        }
                }
                po = mipo;
                for(ll j = 0; j < az; j++)
                {
                        ll nxt = (po+1)%bz, k = (j+1)%az;
                        for( ; tarea(b[po],a[j],a[k]) > tarea(b[nxt],a[j],a[k]);
                                po = nxt, nxt = (po+1)%bz);

                        tsz = min(tsz,tarea(b[po],a[j],a[k]));
                }

                tsz == inf ? cout << -1 << "\n" : cout << se-tsz << "\n";
        }
}




































































