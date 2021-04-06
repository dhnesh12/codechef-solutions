#include <iostream>
#include <string>
using namespace std;

int main() {
	int t,n;
	cin>>t;
	while(t--)
	{   
	    long r[102],mn[102],mx[102],rtw[102],wait[102];
	    string rt[102],c[102];
	    cin>>n;
	    for(int i=1;i<=n;i++){
	        cin>>r[i]>>mn[i]>>mx[i]>>rtw[i]>>rt[i]>>c[i];
	        bool f=0;
	        wait[i]=0;
	         for(int j=1;j<i;j++){
	             if(wait[j]){
	                 continue;
	             }
	             if( mn[j]<=r[i]&&mx[j]>=r[i]&&mn[i]<=r[j]&& mx[i]>=r[j])
	             {
	                 if(rtw[i]==rtw[j]){
	                     if(rt[i]==rt[j]){
	                         if(c[i]=="random"){
	                         if(c[j]=="random"){
	                             f=1;
	                             wait[i]=1;
	                              wait[j]=1;
	                              cout<<j<<"\n";
	                              break;
	                         }}
	                          else if(c[i]=="white"){
	                                 if(c[j]=="black"){ f=1;
	                             wait[i]=1;
	                              wait[j]=1;
	                              cout<<j<<"\n";
	                              break;
	                             }}
	                         else
	                         {
	                           if(c[j]=="white"){  
	                          f=1;
	                             wait[i]=1;
	                              wait[j]=1;
	                              cout<<j<<"\n";
	                              break;
	                           }
	                     }}
	                 }
	             }
	         }if(!f)
	         cout<<"wait"<<"\n";
	    }
	}
	return 0;
}
