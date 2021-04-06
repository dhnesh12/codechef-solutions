/*                         _
                        _ooOoo_
                       o8888888o
                       88" . "88
                       (| -_- |)
                       O\  =  /O
                    ____/`---'\____
                  .'  \\|     |//  `.
                 /  \\|||  :  |||//  \
                /  _||||| -:- |||||_  \
                |   | \\\  -  /'| |   |
                | \_|  `\`---'//  |_/ |
                \  .-\__ `-. -'__/-.  /
              ___`. .'  /--.--\  `. .'___
           ."" '<  `.___\_<|>_/___.' _> \"".
          | | :  `- \`. ;`. _/; .'/ /  .' ; |
          \  \ `-.   \_\_`. _.'_/_/  -' _.' /
===========`-.`___`-.__\ \___  /__.-'_.'_.-'================

                  god please bestow this  question with AC!
*/
//judge saab kro kush eni aunda kakh!
//create your own file by modifying this file!
//by MIRZA JATT /@sainitushar01..............
#include<bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll long long
#define Epsilon 0.01
#define pb push_back
#define ff first
#define ss second
const ll ten_digp=1e9+7;
const ll nine_digp=999999937;
using namespace std;
int main()
{
IOS
ll t;
cin>>t;
while(t--)
{
ll n,x;
cin>>n>>x;
ll a[n];
for(ll i=0;i<n;i++)
cin>>a[i];
ll m=INT_MIN;
for(ll i=0;i<n;i++)
{
	ll s=0;
	for(ll j=i;j<n;j+=x)
	{
		s+=a[j];
	}
	m=max(s,m);
}
cout<<m<<endl;
}
return 0;
}

