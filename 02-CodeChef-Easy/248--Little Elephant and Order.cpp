#include<bits/stdc++.h>
using namespace std;
int main()
{
    int testcases; 
    cin>>testcases; 
    for(int m=0; m<testcases; m++)
    {
        string a,b;
        cin>>a>>b;
        int as=0,bs=0,af=0,bf=0,alf=0,blf=0,afs=0,bfs=0;
        for(int i=0; i<a.length(); i++)
        {
            if(a[i] == '7')
                as++;
            else if(a[i] == '4')
                af++;
            else if(a[i]<'4' && a[i]>='0')
                alf++;
            else if(a[i]<'7' && a[i]>='5')
                afs++;

        }
        for(int i=0; i<b.length() ;i++)
        {
            if(b[i] == '7')
                bs++;
            else if(b[i] == '4')
                bf++;
            else if(b[i]<'4' && b[i]>='0')
                blf++;
            else if(b[i]<'7' && b[i]>='5')
                bfs++;
        }
        string c; 
        while(as)
        {
            
            if(bfs){
              
               c+='7'; bfs--; as--;
            }
            else if(blf)
            {
                c += '7'; blf--; as--;
            }
            else if(bf)
            {
                c += '7'; bf--; as--;
            }
            else if(bs)
            {
                c += '7'; as--; bs--;
            }
            else break;
        }
        while(bs)
        {
            if(afs){
              c += '7'; afs--; bs--;
            }
            else if(alf)
            {
               c += '7'; alf--; bs--;
            }
            else if(af)
            {
               c += '7'; af--; bs--;
            }
            else if(as)
            {
               c += '7'; bs--; as--;
            }
            else break;
        }
        while(af)
        {
            if(blf)
            {
                c += '4'; blf--; af--;
            }
            else if(bf) 
            {
                c += '4';  bf--; af--;
            }
            else break;
        }
        while(bf)
        {
            if(alf)
            {
                c += '4';  alf--; bf--;
            }
            else if(af) 
            {
                c += '4';  af--; bf--;
            }
            else break;
        }
        cout<<c<<endl;
    }
}