
	#include<iostream>
using namespace std;
int main()
{
    int n; 
    cin >> n;
    int ax = -1000, ay = 1000, bx = -1000, by = -1000, cx = 1000, cy = -1000;
	cout << ax << " " << ay << endl << bx << " " << by << endl << cx << " " << cy << endl;
	for (int i = 0; i < n-3; i++)
	{
	    switch(i%3)
	{
			case 0:
				ax += 20; ay -= (40+i); cout << ax << " " << ay << endl; break;
			case 1:
	            bx += (20 + i); by += 20; cout << bx << " " << by << endl; break;
			case 2:
				cx -= (40 + i); cy += 20; cout << cx << " " << cy << endl; break;
	    
	}
	    
	}
    return 0;
}
