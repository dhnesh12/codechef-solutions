

struct hdd
{
    int p,r,w,c;
};
#include<bits/stdc++.h>
using namespace std;
 
void request()
{
    cout<<"g"<<'\n';
}
 
int main()
{
    int n,h;
    cin>>n>>h;
    hdd arr[h];
    int i;
    for(i=0;i<h;i++)
    {
        cin>>arr[h].p>>arr[h].r>>arr[h].w>>arr[h].c;
    }
    int up;
    cin>>up;
    fflush(stdout);
    while(n--)
    {
        request();
        int j,k;
        cin>>i;
        if(i==0)
        {
            cin>>j>>k;
            cout<<"p "<<"s "<<-1<<" "<<-1<<'\n';
            fflush(stdout);
        }
        else if(i==1)
        {
            cin>>j>>k;
            cout<<"p "<<"i "<<"-1"<<" "<<"-1"<<"\n";
            fflush(stdout);
        }
       /* else
        {
            cin>>j;
        }*/
    }
    cout<<"end"<<"\n";
    fflush(stdout);
 
    return 0;
}