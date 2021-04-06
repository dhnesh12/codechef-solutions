#include <bits/stdc++.h>
using namespace std;

int main() {

	int t,i,len,flag;
	string s,temp;
	cin>>t;
    cin.ignore();
	while(t--)
    {
        temp="";
        getline(cin,s);
        len=s.length();
        flag=0;
        for(i=0;i<len;i++)
        {
            if(s[i]==' ')
            {
                if(temp.compare("not")==0)
                {
                    cout<<"Real Fancy\n";
                    flag=1;
                    break;
                }
                else
                    temp="";
            }
            else
                temp+=s[i];
        }
        if(temp.compare("not")==0&&flag==0)
           cout<<"Real Fancy\n";
        else if(flag==0)
           cout<<"regularly fancy\n";

    }
}
