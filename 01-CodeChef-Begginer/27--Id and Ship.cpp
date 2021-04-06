#include <iostream>
using namespace std;

int main() 
{
int t;
cin>>t;
char ch;
while(t--)
{
    cin>>ch;
   
    if(ch=='b'||ch=='B')
    {
        cout<<"BattleShip"<<"\n";
    }
    if(ch=='f'||ch=='F')
    {
        cout<<"Frigate"<<"\n";
    }
    if(ch=='c'||ch=='C')
    {
        cout<<"Cruiser"<<"\n";
    }
    if(ch=='d'||ch=='D')
    {
        cout<<"Destroyer"<<"\n";
    }
}
	return 0;
}
