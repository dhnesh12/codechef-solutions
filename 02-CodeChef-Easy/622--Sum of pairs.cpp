#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class Node{
    public:
    bool visited;
    int data;

};



int main() {
int N;
cin>>N;

Node*arr=new Node[N];

for(int i=0;i<N;i++)
{
    cin>>arr[i].data;
    arr[i].visited=false;
}

vector<int>v;

int ans;


for(int i=0;i<N;i++)
{for(int j=i+1;j<N;j++)
{
    v.push_back(arr[i].data+arr[j].data);
}

}

//we have entered all possible sums in vector

for(int i=0;i<v.size();i++)
{int sum=v[i];
int num=0;

   for(int j=0;j<N;j++)
    {
        for(int k=j+1;k<N;k++)
        {
            if(arr[k].data+arr[j].data==sum&&arr[k].visited==false)
            {
                num++;
                arr[k].visited=true;
                break;

            }

        }


    }

    if(num>ans)
    {
        ans=num;
    }

    for(int i=0;i<N;i++)
    {
        arr[i].visited=false;
    }
}
cout<<2*ans;

	return 0;
}
