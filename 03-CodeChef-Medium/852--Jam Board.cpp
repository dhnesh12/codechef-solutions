#include <stdlib.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;


class DSU{
    public:
    vector<int> parent,size,volts;
    DSU(int n){
        parent.resize(n+1);
        for(int i=0;i<=n;i++)
            parent[i]=i;
        size.resize(n+1,1);
        volts.resize(n+1,0);
    }

    int find(int a){
        if(parent[a]==a)
            return a;
        parent[a]=find(parent[a]);
        return parent[a];
    }

    void join(int a,int b){
        a=find(a);
        b=find(b);

        if(a==b)return;
        if(size[a]<size[b]){
            parent[a]=b;
            size[b]+=size[a];
            volts[b]+=volts[a];
        }
        else{
            parent[b]=a;
            size[a]+=size[b];
            volts[a]+=volts[b];
        }
    }
};

int decode(string a){
    int ans=0;
    if(a[0]>='A'&&a[0]<='Z'){
        ans+=52*(a[0]-65);
    }else{
        ans+=52*(a[0]-97+26);
    }
    if(a[1]>='A'&&a[1]<='Z'){
        ans+=(a[1]-65);
    }else{
        ans+=(a[1]-97+26);
    }
    return ans;
}

int linear(int a, int b, int c){
    b=(b-1)/5;
    b++;
    return (b-1)*c+a;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t,n,r,c,a1,b1,a2,b2,temp1;
	string temp;
	char opt;
	cin>>n>>r>>c;
    DSU ds(r*c);
	for(int i=0;i<n;i++){
		cin>>temp;
		opt=temp[0];
		if(opt=='W'){
            a1=decode(temp.substr(1,2));
            b1=decode(temp.substr(3,2));
            a2=decode(temp.substr(5,2));
            b2=decode(temp.substr(7,2));
            ds.join(linear(a1,b1,c),linear(a2,b2,c));
		}else if(opt=='V'){
            a1=decode(temp.substr(1,2));
            b1=decode(temp.substr(3,2));
            temp1=ds.find(linear(a1,b1,c));
            ds.volts[temp1]++;
		}else if(opt=='R'){
            a1=decode(temp.substr(1,2));
            b1=decode(temp.substr(3,2));
            temp1=ds.find(linear(a1,b1,c));
            ds.volts[temp1]--;
		}else{
            a1=decode(temp.substr(1,2));
            b1=decode(temp.substr(3,2));
            a2=decode(temp.substr(5,2));
            b2=decode(temp.substr(7,2));
            a1=ds.find(linear(a1,b1,c));
            a2=ds.find(linear(a2,b2,c));
            if((ds.volts[a1]>0&&ds.volts[a2]==0)||(ds.volts[a1]==0&&ds.volts[a2]>0))
                cout<<"ON\n";
            else
                cout<<"OFF\n";
		}

	}
}