#include <iostream>
#include <fstream>
#define NMX 100005
#define NMX1 300005
#define fin cin
#define fout cout

using namespace std;

int n,k,p,x,s,arb[NMX1];

int add (int st, int dr, int pz, int nod)
{
    if(st==dr)
    {
        arb[nod]=st;
        return 0;
    }

    int mid=(st+dr)>>1;

    if(pz<=mid)
        add(st,mid,pz,(nod<<1));
    else add(mid+1,dr,pz,((nod<<1)+1));

    arb[nod]=max(arb[(nod<<1)],arb[(nod<<1)+1]);

    return 0;
}

int query (int st, int dr, int start, int finish, int nod)
{
    if(st>finish || dr<start)
        return -1;

    if(start<=st && dr<=finish)
        return arb[nod];

    int mid=(st+dr)>>1;

    return max(query(st,mid,start,finish,(nod<<1)),query(mid+1,dr,start,finish,(nod<<1)+1));
}

int build (int st, int dr, int nod)
{
    if(st==dr)
    {
        arb[nod]=-1;
        return 0;
    }

    int mid=(st+dr)>>1;

    build(st,mid,(nod<<1));
    build(mid+1,dr,((nod<<1)+1));

    arb[nod]=-1;

    return 0;
}

int main()
{
    //ifstream fin ("test.in");
    //ofstream fout ("test.out");

    fin>>n>>k>>p;

    p=min(p,NMX-5);
    int mx=NMX-5,sx,mi=p;

    build(0,p,1);

    for(int i=1;i<=n;i++)
    {
        fin>>x;

        s+=x;
        s%=p;

        //s>=sx
        if((s-k)>=0)
        {
            sx=query(0,p,0,s-k,1);

            if(sx!=-1)
                mi=min(mi,s-sx);
        }

        //s<sx
        //s-sx+p=k

        if(s+p-k>=s+1)
        {
            sx=query(0,p,s+1,s+p-k,1);

            if(sx!=-1)
                mi=min(mi,s-sx+p+1);
        }

        if(s>=k)
            mi=min(mi,s);

        add(0,p,s,1);
    }

    if(k>=p)
        fout<<0;
    else fout<<mi;

    return 0;
}
