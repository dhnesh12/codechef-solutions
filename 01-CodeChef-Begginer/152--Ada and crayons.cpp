#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--){
        string S;
        cin>>S;
        long int cu,cd;
        cu=cd=0;
        for(int i=0;S[i]!='\0';i++){
            if(S[i]=='U' && S[i+1]!='U'){
                cu++;
            }
            else if(S[i]=='D' && S[i+1]!='D'){
                cd++;
            }
        }
        if(cd<cu){
            cout<<cd<<endl;
        }
        else{
            cout<<cu<<endl;
        }
    }
    return 0;
}
