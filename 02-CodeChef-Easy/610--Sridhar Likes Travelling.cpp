#include<bits/stdc++.h>

using namespace std;

int main(){

	int t;
	
	cin>>t;

	vector< pair < vector< pair < pair < string , string > , int > > , int >  > vfinal;

	while( t--){

		int n, s=0;

		string st;

		cin>>n;

		map< string , pair< string, int>> paiir;

		vector< pair < pair < string , string > , int > > vv;

		map< string, int > count;
		map< string, int > location;

		for( int i=0; i<n-1; i++){

			string a,b,c;

			int d;

			cin >> a >> b >> c;
			
			c.pop_back();

			stringstream ss;

			ss << c;

			ss >> d;

			paiir[a]= make_pair( b,d);
			count[a]++;
			count[b]++;

			location[a]=1;
			location[b]=2;

			s+=d;
		}

		for( auto it : count){

			if( ( it.second == 1 ) && ( location[ it.first] == 1 ) ){

				st=it.first;

				break;
			}
		}

		for( int i=0; i<n-1; i++){

			vv.push_back( make_pair( make_pair( st, paiir[st].first), paiir[st].second));
			st = paiir[st].first;
		}

		vfinal.push_back( make_pair ( vv, s));
	}

	for( auto it : vfinal){

		for( auto it1 : it.first){

			cout<< it1.first.first<<" "<< it1.first.second << " " << it1.second <<"$"<< endl;
		}

		cout<< it.second<<"$"<<endl;
	}

	return 0;
}
