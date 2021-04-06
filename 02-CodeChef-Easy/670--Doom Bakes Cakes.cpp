#include<bits/stdc++.h>
using namespace std;
#define fast() ios_base::sync_with_stdio(0);cin.tie(NULL); cout.tie(NULL);
#define file() freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define test_cases() cin>>_;
#define debug(x) cout<<#x<<" = "<<x<<'\n';
#define display(a) for(int i=0;i<a.size();i++) cout<<a[i]<<' '; cout<<'\n';
#define all(a) a.begin(),a.end()
int _;
bool ok(int a,char b)
{
    if(b=='?')
    return true;
    int temp = (int)(b-'0');
    return temp!=a;
}
bool check(string temp,string s)
{
    for(int i=0;i<s.size();i++)
    {
        if(s[i]!='?')
        {
            if(s[i]!=temp[i])
            return false;
        }
    }
    return true;
}
int main()
{
    _=1;
    // file();
    fast();
    test_cases();
    while(_--)
    {
        int k,n;
        cin>>k;
        string s;
        cin>>s;
        n = s.size();
        if(k==1)
        {
            if(n>1)
            cout<<"NO\n";
            else
            cout<<"0\n";
        }
        else if(k==2)
        {
            if(n%2==1)
            {
                if(n>1)
                    cout<<"NO\n";
                else
                {
                    if(s[0]=='?')
                    {
                        cout<<"0\n";
                    }
                    else
                    {
                        cout<<s<<'\n';
                    }
                }
            }
            else
            {
                string temp = s;
                for(int i=0;i<n;i++)
                {
                    if(i%2==0)
                    {
                        temp[i]='0';
                    }
                    else
                    {
                        temp[i]='1';
                    }
                }
                if(check(temp,s))
                {
                    cout<<temp<<'\n';
                }
                else
                {
                    for(int i=0;i<n;i++)
                    {
                        if(i%2==0)
                        {
                            temp[i]='1';
                        }
                        else
                        {
                            temp[i]='0';
                        }
                    }
                    if(check(temp,s))
                    {
                        cout<<temp<<"\n";
                    }
                    else
                    {
                        cout<<"NO\n";
                    }
                }

            }
        }
        else
        {
            bool possible = true;
            for(int i=0;i<n;i++)
            {
                if(  (s[i]==s[(i+1)%n]) &&  s[i]!='?' && n>1)
                {
                    possible = false;
                    break;
                }
            }
            if(!possible)
            {
                cout<<"NO\n";
            }
            else
            {
                for(int i=0;i<n;i++)
                {
                    if(s[i]=='?')
                    {
                        for(int j=0;j<k;j++)
                        {
                            if(  ok(j,s[(i-1+n)%n]) &&  ok(j,s[(i+1+n)%n])  )
                            {
                                s[i]=(char)(j+'0');
                                break;
                            }
                        }
                    }
                }
                bool possible = true;
                for(int i=0;i<n;i++)
                {
                    if(s[i]=='?')
                    {
                        possible=false;
                        break;
                    }
                    if((s[i]==s[(i+1)%n]) &&  s[i]!='?' && n>1)
                    {
                        possible=false;
                        break;
                    }
                }
                if(!possible)
                {
                    cout<<"NO\n";
                }
                else
                {
                    cout<<s<<'\n';
                }
            }
        }

    }
    return 0;
}