#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    while(cin>>s){
        int ta=0,tb=0,r=0,i,ra=5,rb=5;
        for(i=0;i<10;i++){  
            if(i%2==0){ta+=int(s[i])-'0';ra--;}
            else{tb+=int(s[i])-'0';rb--;}
            //cout<<ta<<' '<<tb<<' '<<i+1<<'\n'
            if((ta-tb)>rb){cout<<"TEAM-A "<<i+1<<'\n'; r=1; break;} 
            if(ra<(tb-ta)){cout<<"TEAM-B "<<i+1<<'\n'; r=1; break;}
        }
        if(r==0 && ta>tb){cout<<"TEAM-A "<<i+1<<'\n'; r=1;}
        else if(r==0 && tb>ta){cout<<"TEAM-B "<<i+1<<'\n'; r=1;}
        else if(r==0 && ta==tb){
            for(i=10;i<20;i+=2){
                ta+=int(s[i])-'0';
                tb+=int(s[i+1])-'0';
                //cout<<ta<<' '<<tb<<' '<<i+1<<'\n';
                if(ta>tb){cout<<"TEAM-A "<<i+2<<'\n'; r=1; break;}
                else if(tb>ta){cout<<"TEAM-B "<<i+2<<'\n'; r=1; break;}
            }
            if(r==0){cout<<"TIE"<<'\n';}
        }
    }
    return 0;
}