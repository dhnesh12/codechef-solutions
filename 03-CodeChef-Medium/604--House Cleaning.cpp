#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl '\n'
#define mxN 2005
vector<string>gcode;
void generateGraycode(int n){
    gcode.clear();
    if(n<=0){
        return;
    }
    gcode.push_back("0");
    gcode.push_back("1");
    int i,j;
    for(int i=2;i<(1<<n);i=i<<1){
        for(int j=i-1;j>=0;j--){
            gcode.push_back(gcode[j]);
        }
        for(j=0;j<i;j++) gcode[j]="0"+gcode[j];
        for(j=i;j<2*i;j++) gcode[j]="1"+gcode[j];
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n,d;
        cin>>n>>d;
        int a[n];
        string s="";
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]==-1) s+="0";
            else s+="1";
        }
        if(d<4) {cout<<"-2\n";continue;}
        generateGraycode(n);
        int p=gcode.size();
        int x;
        for(int i=0;i<p;i++){
            if(gcode[i]==s) {x=i;break;}
        }
        //cout<<s<<" "<<gcode[x]<<endl;
        for(int i=0;i<p;i++){
            for(int j=0;j<n;j++){
                int l=s[j]-'0';
                int m=gcode[i][j]-'0';
                (l^m)==1?cout<<"1 ":cout<<"-1 ";//xor
            }
            cout<<endl;
        }
        //cout<<endl;


    }
    

    return 0;
    
}