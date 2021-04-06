#include <iostream>
using namespace std;

void CalculateStuff(int s,int e,int *a,int *t,int *l,int *r ){
    for(int i=s-1;i<e;i++){
        if(t[i]==1){
            for(int j=l[i]-1;j<r[i];j++ ){
                a[j]=(a[j]+1)%(1000000007);
            }
        }else{
            CalculateStuff(l[i],r[i],a,t,l,r);
        }
    }
}

int main() {
	// your code goes here
	int T;
	cin>>T;
	for(int i=0;i<T;i++){
	    int n,m;
	    cin>>n;
	    cin>>m;
	    int a[n]={0};
	    int t[m];
	    int l[m];
	    int r[m];
	    for(int i=0;i<m;i++){
	        cin>>t[i]>>l[i]>>r[i];
	        
	        
	    }
	    CalculateStuff(1,m,a,t,l,r);
	    for(int i=0;i<n;i++){
	        cout<<a[i]<<" ";
	        
	    }
	    cout<<endl;
	    
	    
	    
	    
	}
	return 0;
}
