#include <iostream>
#include<climits>
using namespace std;

int main() 
{
    int t;
    cin>>t;
    while(t--)
    {
        bool a;
        string s;
        cin>>s;
        string finalanswer="";
        int finaloperations=INT_MAX;
        int operations;
        if(s.length()>=9)
        {
            for(int i=0;i+5<=s.length();i++)
            {
                a=1;
                string t=s;
                operations=0;
                if(t[i]!='l')
                {
                    t[i]='l';
                    //cout<<s[0]<<endl;
                    operations++;
                }
                if(t[i+1]!='u')
                {
                    t[i+1]='u';
                    //cout<<s[1]<<endl;
                    operations++;
                }
                if(t[i+2]!='c')
                {
                    t[i+2]='c';
                    //cout<<s[2]<<endl;
                    operations++;
                }
                
                if(t[i+3]!='k')
                {
                    t[i+3]='k';
                    //cout<<s[3]<<endl;
                    operations++;
                }
                if(t[i+4]!='y')
                {
                    t[i+4]='y';
                   // cout<<s[4]<<endl;
                    operations++;
                }
                int st=0;
                int e=s.length()-1;
                while(st<e)
                {
                    if(t[st]==t[e])
                    {
                        st++;
                        e--;
                        continue;
                    }
                    if(st>=i and st<i+5 and e>=i and e<i+5)
                    {
                        a=0;
                        break;
                    }
                    if(st>=i and st<i+5)
                    {
                        t[e]=t[st];
                        operations++;
                    }
                    else if(e>=i and e<i+5)
                    {
                        t[st]=t[e];
                        operations++;
                    }
                    else if(t[st]<t[e])
                    {
                        t[e]=t[st];
                        operations++;
                    }
                    else if(t[st]>t[e])
                    {
                        t[st]=t[e];
                        operations++;
                    }
                    st++;
                    e--;
                }
              //  cout<<" a= "<<a<<" Before FInal Answer="<<finalanswer<<" ";
                if((a==1) and ((finaloperations>operations) or (finaloperations==operations and (finalanswer>t or finalanswer==""))))
                {
                    finalanswer=t;
                    finaloperations=operations;
                }
                st++;
                e--;
            }
            cout<<finalanswer<<" "<<finaloperations<<endl;
        }
        else
        {
            cout<<"unlucky"<<endl;
        }
    }
}