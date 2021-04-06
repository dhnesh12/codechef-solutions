#include <iostream>
using namespace std;

int main() {
    
    
    
    int N;
    int r;
    int l;
    
    cin>>N;
    while(N--)
    {
     cin>>r;
     cin>>l;
     
    // if(r>=2&&l>=2/*&&r<=50&&l<=50*/)
     //{
     
       if(r%2==0&&l%2==0)
     {
         cout<<"YES"<<endl;
         
     }
      else if(r%2!=0&&l%2==0)
     {
         cout<<"YES"<<endl;
         
     }
     
      else if(r%2==0&&l%2!=0)
     {
         cout<<"YES"<<endl;
         
     }
    else if(r%2!=0&&l%2!=0)
    {
         cout<<"NO"<<endl;
     }
     else{
         //
     }
       
       
    // }
     
        
    
    }
	// your code goes here
	return 0;
}
