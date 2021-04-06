#include<bits/stdc++.h>
using namespace std;
#define MAXLEN 400001

int a[MAXLEN];

int main(){
    int t,n,w,countS=0;

    deque<pair<int,int> > minq,maxq;
    cin>>n>>w;

    countS = 0;
    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int i=0;i<=w-2;i++){
        while(!minq.empty() && minq.back().first>a[i])
            minq.pop_back();

        minq.push_back(make_pair(a[i],i));

        while(!maxq.empty() && maxq.back().first<a[i])
            maxq.pop_back();

        maxq.push_back(make_pair(a[i],i));

    }

    for(int i = w-1;i<n;i++){
        while(!minq.empty() && minq.front().second<=i-w)
            minq.pop_front();

        while(!minq.empty() && minq.back().first>a[i])
            minq.pop_back();

        minq.push_back(make_pair(a[i],i));

        while(!maxq.empty() && maxq.front().second<=i-w)
            maxq.pop_front();

        while(!maxq.empty() && maxq.back().first<a[i])
            maxq.pop_back();

        maxq.push_back(make_pair(a[i],i));

        if(maxq.front().first-minq.front().first+1 == w)
            countS++;
    }

    cout<<countS<<endl;

}
