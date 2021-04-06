#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define mx 50

using namespace std;

int lcm[mx][mx];

int gcd(int a, int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

bool sim(string &s, int x, int y, int dx, int dy)
{
    int n=s.length();
    int m1=max(0,x-(int)(s[x]-'0'));
    int M1=min(n-1,x+(int)(s[x]-'0'));
    int m2=max(0,y-(int)(s[y]-'0'));
    int M2=min(n-1,y+(int)(s[y]-'0'));
    int cx=x;
    int cy=y;
    int t=lcm[2*(M1-m1)][2*(M2-m2)];
    for(int i=1;i<=t;i++)
    {
        if(cx==cy)
            return false;
        if(cx==m1)
            dx=1;
        if(cx==M1)
            dx=-1;
        if(cy==m2)
            dy=1;
        if(cy==M2)
            dy=-1;
        cx=cx+dx;
        cy=cy+dy;
    }
    
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for(int i=1;i<mx;i++)
    {
        for(int j=1;j<mx;j++)
        {
            lcm[i][j]=(i*j)/gcd(i,j);
        }
    }
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        string s;
        cin>>s;
        n=s.length();
        int od=-1;
        int ev=-1;
        int dir[n];
        for(int i=0;i<n;i++)
            dir[i]=0;
        bool flag=true;
        bool v[n];
        for(int i=0;i<n;i++)
            v[i]=false;
        int c=0;
        for(int i=0;i<n;i++)
        {
            if(s[i]!='.'&&s[i]!='0')
            {
                c++;
                if(i%2==1)
                {
                    if(od==-1)
                    {
                        od=i;
                        dir[i]=2;
                        continue;
                    }
                    int m1=max(0,i-(int)(s[i]-'0'));
                    int M1=min(n-1,od+(int)(s[od]-'0'));
                    /*if(m1>M1)
                    {
                        od=i;
                        dir[i]=2;
                        continue;
                    }*/
                    if(dir[od]==2)
                    {
                        bool a1=sim(s,od,i,1,1);
                        bool a2=sim(s,od,i,1,-1);
                        bool a3=sim(s,od,i,-1,-1);
                        bool a4=sim(s,od,i,-1,1);
                        if((a1||a4)&&(a2||a3))
                            dir[i]=2;
                        else if(a1||a4)
                            dir[i]=1;
                        else if(a2||a3)
                            dir[i]=-1;
                        else
                        {
                            flag=false;
                            break;
                        }
                        od=i;
                    }
                    else
                    {
                        bool a1=sim(s,od,i,dir[od],1);
                        bool a2=sim(s,od,i,dir[od],-1);
                        if(a1&&a2)
                            dir[i]=2;
                        else if(a1)
                            dir[i]=1;
                        else if(a2)
                            dir[i]=-1;
                        else
                        {
                            flag=false;
                            break;
                        }
                        od=i;
                    }
                }
                else
                {
                    if(ev==-1)
                    {
                        ev=i;
                        dir[i]=2;
                        continue;
                    }
                    int m1=max(0,i-(int)(s[i]-'0'));
                    int M1=min(n-1,ev+(int)(s[ev]-'0'));
                    /*if(m1>M1)
                    {
                        ev=i;
                        dir[i]=2;
                        continue;
                    }*/
                    if(dir[ev]==2)
                    {
                        bool a1=sim(s,ev,i,1,1);
                        bool a2=sim(s,ev,i,1,-1);
                        bool a3=sim(s,ev,i,-1,-1);
                        bool a4=sim(s,ev,i,-1,1);
                        if((a1||a4)&&(a2||a3))
                            dir[i]=2;
                        else if(a1||a4)
                            dir[i]=1;
                        else if(a2||a3)
                            dir[i]=-1;
                        else
                        {
                            flag=false;
                            break;
                        }
                        ev=i;
                    }
                    else
                    {
                        bool a1=sim(s,ev,i,dir[ev],1);
                        bool a2=sim(s,ev,i,dir[ev],-1);
                        if(a1&&a2)
                            dir[i]=2;
                        else if(a1)
                            dir[i]=1;
                        else if(a2)
                            dir[i]=-1;
                        else
                        {
                            flag=false;
                            break;
                        }
                        ev=i;
                    }
                }
            }
                
            else if(s[i]=='0')
            {
                c++;
                v[i]=true;
            }
        }
        
        if(!flag)
            cout<<"unsafe\n";
        else
        {
            for(int i=0;i<n;i++)
            {
                if(s[i]!='.'&&s[i]!='0')
                {
                    int m1=max(0,i-(int)(s[i]-'0'));
                    int M1=min(n-1,i+(int)(s[i]-'0'));
                    for(int j=m1;j<=M1;j++)
                    {
                        if(v[j])
                        {
                            flag=false;
                            break;
                        }
                    }
                    if(!flag)
                        break;
                }
            }
            if(!flag)
                cout<<"unsafe\n";
            else cout<<"safe\n";
        }
    }
    cout<<endl;
    return 0;
}
