#include<bits/stdc++.h>
using namespace std;
///Persistent Trie
struct Trie
{
    const static int N = 2;//Binary numbers.
    struct node
    {
        int next[N];
        int freq,ended;
        node():freq(0),ended(0)
        {
            for(int i=0; i<N; i++) next[i]=-1;
        }
    };
    vector<node>data;
    Trie()
    {
        data.push_back(node());
    }
    ///return location of new head
    int add(int head, int val)
    {
        //cout<<"ADD:"<<head<<' '<<val<<endl;
        int old = head;
        int now = data.size();
        data.push_back(node());
        int newHead =now;
        for(int i = 30; i>=0; i--)
        {
            int id = (val>>i)&1;
            if(old ==-1)
            {
                data[now].next[id] = data.size();
                data.push_back(node());
                data[now].freq++;
                now = data[now].next[id];
                continue;
            }
            data[now] = data[old];
            data[now].next[id] = data.size();
            data.push_back(node());
            old = data[old].next[id];
            now = data[now].next[id];
        }
        data[now].freq++;
        data[now].ended++;
        return newHead;
    }
    int Search(int head,int val)
    {
        int cur=head;
        for(int i = 30; ~i; i--)
        {
            int id=(val>>i)&1;
            if(data[cur].next[id]==-1) return 0;
            cur=data[cur].next[id];
        }
        return data[cur].ended;
    }
    int maxXor(int head,int x)
    {
        int cur =head;
        int ans = 0;
        for(int i=30; ~i; i--)
        {
            int b = (x>>i)&1;
            if(data[cur].next[!b]+1 && data[data[cur].next[!b]].freq>0)
            {
                ans+=(1LL<<i);
                cur = data[cur].next[!b];
            }
            else cur = data[cur].next[b];
        }
        return ans;
    }

    int minXor(int head,int x)
    {
        int cur =head;
        int ans = 0;
        for(int i=30; ~i; i--)
        {
            int b = (x>>i)&1;
           // cout<<"Min"<<i<<' '<<b<<' '<<data[cur].next[b]<<endl;
            if(data[cur].next[b]+1 && data[data[cur].next[b]].freq>0)
                cur = data[cur].next[b];
            else
            {
                ans+=(1LL<<i);
                cur = data[cur].next[!b];
            }
        }
        return ans;
    }
} Troy;
vector<int>adj[100005];
map<int,int>actualVal;
int headId[100005];
int enKey[100005];
void dfs(int u,int p)
{
    //cout<<"DFS:"<<u<<' '<<enKey[u]<<endl;
    headId[u] = Troy.add(headId[p],enKey[u]);
    for(int v:adj[u])
    {
        if(v!=p)
            dfs(v,u);
    }
}
int main()
{
    int n,q;
    cin>>n>>q;
    int r,KEY;
    cin>>r>>KEY;
    actualVal[r] = 1;
    enKey[actualVal[r]] =KEY;
    int mcnt = 1;
    for(int i=1; i<n; i++)
    {
        int u,v,k;
        cin>>v>>u>>k;
        if(actualVal[v]==0) actualVal[v] = ++mcnt;
        u = actualVal[u];
        v = actualVal[v];
        adj[u].push_back(v);
        enKey[v] = k;
    }

    dfs(1,0);
    //for(int i=1;i<=n;i++) cout<<i<<' '<<actualVal[i]<<' '<<headId[i]<<endl;
    int last_answer = 0;
    for(int i=0; i<q; i++)
    {
        int t;
        cin>>t;
        t ^=last_answer;
        if(t==0)
        {
            int u,v,k;
            cin>>u>>v>>k;
            u^=last_answer;
            v^=last_answer;
            k^=last_answer;
            if(actualVal[u]==0) actualVal[u] = ++mcnt;
            if(actualVal[v]==0) actualVal[v] =++mcnt;
            u = actualVal[u];
            v = actualVal[v];
            headId[v]=Troy.add(headId[u],k);
        }
        else
        {
            int v,k;
            cin>>v>>k;
            v^=last_answer;
            k^=last_answer;
            v = actualVal[v];
           // cout<<"ACVAL:"<<v<<' '<<k<<headId[v]<<endl;
            int min_ans = Troy.minXor(headId[v],k);
            int max_ans = Troy.maxXor(headId[v],k);
            cout<<min_ans<<' '<<max_ans<<endl;
            last_answer = min_ans ^ max_ans;
        }
    }
}

