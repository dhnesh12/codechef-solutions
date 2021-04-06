#include <iostream>
using namespace std;
const int N=500000*22;
struct node
{
 int lf,rg,cnt;
};
node trie[N];
int new_ptr;
int root[N];
int insert(int prev,int x)
{
    int temp=new_ptr++;
    int cur=temp;

    trie[cur]=trie[prev];
    for(int bit=20;bit>=0;bit--)
    {
        int set=(x>>bit)&1;
        if(set)
        {
            trie[cur].rg=new_ptr++;
            trie[trie[cur].rg]=trie[trie[prev].rg];
            trie[trie[cur].rg].cnt++;
           // cout<<trie[trie[cur].rg].cnt;
            cur=trie[cur].rg;
            prev=trie[prev].rg;
        }
        else{
            trie[cur].lf=new_ptr++;
            trie[trie[cur].lf]=trie[trie[prev].lf];
            trie[trie[cur].lf].cnt++;
           // cout<<trie[trie[cur].lf].cnt;
            cur=trie[cur].lf;
            prev=trie[prev].lf;
        }

    }

    return temp;
}
int maxxor(int prev,int cur,int x)
{ int y=0;
    for(int bit=20;bit>=0;bit--)
    {
        int set=(x>>bit)&1;
        if(set)
        {
          if(trie[trie[cur].lf].cnt>trie[trie[prev].lf].cnt)
          {
            cur=trie[cur].lf;
            prev=trie[prev].lf;
           

          }
          else{
              cur=trie[cur].rg;
            prev=trie[prev].rg;
             y+=(1<<bit);
            
            
          }
        }
        else
        {
           if(trie[trie[cur].rg].cnt>trie[trie[prev].rg].cnt)
          {  
            cur=trie[cur].rg;
            prev=trie[prev].rg;
            y+=(1<<bit);

          }
          else{
              cur=trie[cur].lf;
            prev=trie[prev].lf;
          }
        }
    }
    return y;
}
int lessthanequalto(int prev,int cur,int x)
{   int ans=0;
    for(int bit=20;bit>=0;bit--)
    {
        int set=(x>>bit)&1;
        if(set)
        {  ans+=trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt;
            cur=trie[cur].rg;
            prev=trie[prev].rg;

        }
        else{
            
            cur=trie[cur].lf;
            prev=trie[prev].lf;

        }
    }
    ans+=trie[cur].cnt-trie[prev].cnt;
    return ans;
}
int Kthsmallest(int prev,int cur,int k)
{  int ans=0;
    for(int bit=20;bit>=0;bit--)
    {
        if(trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt>=k)
        {
            cur=trie[cur].lf;
            prev=trie[prev].lf;
        }
        else{
            k-=(trie[trie[cur].lf].cnt-trie[trie[prev].lf].cnt);
            cur=trie[cur].rg;
            prev=trie[prev].rg;
            ans+=(1<<bit);

        }
    }
    return ans;
}
int main() {
    int n=1;
    root[0]=0;
    trie[0].lf=trie[0].rg=trie[0].cnt=0;
    int m;
    new_ptr=1;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        int type;
        cin>>type;
        if(type==0)
        {
            int x;
            cin>>x;
            root[n]=insert(root[n-1],x);
            
            n++;
        }
        else if(type==1)
        {
            int l,r,x;
            cin>>l>>r>>x;
            cout<<maxxor(root[l-1],root[r],x)<<"\n";

        }
          else if(type==2)
        {
            int k;
            cin>>k;
            n-=k;
            
        }
          else if(type==3)
        {
             int l,r,x;
            cin>>l>>r>>x;
            cout<<lessthanequalto(root[l-1],root[r],x)<<"\n";

        }
          else if(type==4)
        {
            int l,r,k;
            cin>>l>>r>>k;
            cout<<Kthsmallest(root[l-1],root[r],k)<<"\n";
        }

    }
}

