#include<bits/stdc++.h>
using namespace std;
// template<typename T>
#define ll 				long long int
#define ld				long double
#define mod             1000000007
#define inf             1e18
#define vi              vector<ll>
#define vs				vector<string>
#define pii             pair<ll,ll>
#define ump				unordered_map
#define mp 				map
#define pq_max          priority_queue<ll>
#define pq_min          priority_queue<ll,vi,greater<ll> >
#define ff 				first
#define ss 				second
#define mid(l,r)        (l+(r-l)/2)
#define loop(i,a,b) 	for(int i=(a);i<=(b);i++)
#define looprev(i,a,b) 	for(int i=(a);i>=(b);i--)


void file_i_o()
{
    #ifndef ONLINE_JUDGE
        freopen("/Users/burhankapdawala/Desktop/C++14/input.txt","r",stdin);
        freopen("/Users/burhankapdawala/Desktop/C++14/output.txt","w",stdout);
    #endif
}



int main(int argc, char const *argv[])
{
    // clock_t begin  = clock();
    // file_i_o();

    // write your code here

     int t;
     cin>>t;
     cin.ignore();
     while(t--)
     {  
        int a[26][2];
        loop(i,0,25)
        {
            a[i][0]=0;
            a[i][1]=i;
        }
        string s1,s2;
        getline(cin,s1);
        getline(cin,s2);
        loop(i,0,s2.length()-1)
        {
            int c = (int)(s2[i]);
            if(c <= 90 && c >= 65)
                c = c - 65;
            else if( c >= 97 && c <= 122)
                c -= 97;
            else
                continue;
            a[c][0]++;
        }
        int temp;
        loop(i,0,25)
        {
            for(int j=0; j<25-i; j++)
            {
                if(a[j][0] > a[j+1][0])
                {
                    temp = a[j][0];
                    a[j][0] = a[j+1][0];
                    a[j+1][0] = temp;
                    
                    temp = a[j][1];
                    a[j][1] = a[j+1][1];
                    a[j+1][1] = temp;
                }
            }
        }
        int m;
        loop(i,0,25)
        {
            if(a[i][0]>0)
            {
                m=i;
                break;
            }    
        }
        loop(i,0,s2.length()-1)
        {
            loop(j,m,25)
            {
                int c = (int)(s2[i]);
                if(c>=97 && c<=122)
                {
                    if(s2[i]==(char)(a[j][1]+97))
                    {
                        cout<<s1[j];
                        break;
                    }
                }
                else if(c>=65 && c<=90)
                {
                    if(s2[i]==(char)(a[j][1]+65))
                    {
                        cout<<(char)(s1[j]-32);
                        break;
                    }
                }
                else
                {
                    cout<<s2[i];
                    break;
                }
            }
            
        }
        cout<<endl;
     }

    // #ifndef ONLINE_JUDGE
    //     clock_t end = clock();
    //     cout<<"\n\nExecuted in: "<<double(end-begin) / CLOCKS_PER_SEC*1000<<" ms";
    // #endif
    return 0;
}