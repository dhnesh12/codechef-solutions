#include<bits/stdc++.h>
using namespace std;
#define fastio std::ios_base::sync_with_stdio(false)
long long int func(vector<long long int> &b,long long int x,long long int num)
{
       long long int i=0,j=0;
       auto z=b.begin();
	    b.insert(z+x,0);
	    while(num!=2)
	    {
	       if(i==x)
	          i=(x+1)%num;
	        j=(i+1)%num;
	        if(j==x)
	        {
	            b[x]=b[x]+b[i];
	            i=(i+1)%num;
	            continue;
	        }
	        if(j<x)
	        x--;
	        z=b.begin();
	        b.erase(z+j);
	        num=b.size();
	        i++;
	        if(i>=num)
	         i=0;
	    }
	    return b[x];
}
int main() {
    fastio;
	int t;
	cin>>t;
	while(t--)
	{
	    long long int n,i=0,f=0,pos=0,m=0,min=LONG_MAX,ch=0,check=0;
	    cin>>n;
	    vector<long long int> v(n-1,0);
	    vector<long long int> a;
	    for(i=0;i<n-1;i++)
	      cin>>v[i];
	    cin>>f;
	    for(i=0;i<n-1;i++)
	    {
	       if(f==v[i])
	         a.push_back(i);
	        if(f>v[i])
	        {
	            a.push_back(i);
	            m++;
	        }
	    }
	    if(m==0)
	    {
	        cout<<"impossible"<<endl;
	        continue;
	    }
	    long long int p = (long long int)log2(n); 
          ch=(long long int)pow(2, p);  
          check=((n-ch-1)*2)+1;
          if(check==-1)
            check=n-1;
          if(v[check-1]<f)
          {
                 cout<<"possible"<<endl<<check<<" "<<f<<endl;
                 continue;
          }
	    for(auto it=a.begin();it!=a.end();it++)
	    {
	       vector<long long int> b(v);
	       m=n;
	      long long int res=func(b,*it,m);
	      if(res<min)
	      {
	          min=res;
	          pos=*it+1;
	      }
	    }
	  cout<<"possible"<<endl;
     cout<<pos<<" "<<min+f<<endl;
	}
	return 0;
}