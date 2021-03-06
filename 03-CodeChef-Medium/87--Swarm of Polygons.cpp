#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
 
#define INT_MAX 1000000000
using namespace std;
 
#define Mx 2*1000005
#define Mod 1000000007
#define rep( i, n ) for( int i = 0 ; i < n ; i ++ )
 
typedef long long ll;
 
int N, K, a, b, c, m;
 
ll val[Mx], chk[Mx];
ll x[25], z[25], y[25], p[25], q[25], r[25], o[25];
 
int Q;
 
int E;
 
int nx, ny, nz;
int cnt, res;
 
int make(){
	memset( x, 0, sizeof( x ) );
	x[0] = 1;
}
 
int init(){
	Q ++;
	cnt = 0, res = INT_MAX;
	for( int i = 0; i < N ; i ++ ){
		if( cnt == 0 ) val[cnt] = a, chk[a] = Q;
		else{
			val[cnt] = val[cnt -1] * b + c;
			val[cnt] %= m;
			if( chk[val[cnt]] == Q ){ res = val[cnt]; break;}
			chk[val[cnt]] = Q;
		}
		cnt ++;
	}
 
	int i;
	for( i = 0 ; i < cnt ; i ++ ) if( val[i] == res ) break;
	
	E = i - 1;
	 
	return cnt - i;
} 
		
int find( int st, int en ){
	
	if( st > en ) return make();
	if( en == -1 ) return make();
	
	memset( x, 0, sizeof( x ) );
	x[0] = 1, x[1] = val[st];
	for( int i = st + 1 ; i <= en ; i ++ ){
		int k, j;
		for (k = K; k >= 1; k --) {
			x[k] += x[k - 1] * val[i];
			x[k] %= Mod;
		}
	}
}	
 
int Multi( ll* s, ll* t ){
	memset( z, 0, sizeof( z ) );
	for( int i = 0 ; i <= K ; i ++ ) 
	for( int j = 0 ; j <= K ; j ++ ){
		z[i + j] += s[i] * t[j];
		z[i + j] %= Mod;
	}
	memcpy( x, z, sizeof( z ) );
}
 
 
int pow( int n ){
	if( n == 1 ) return 1;
	memcpy( p, o, sizeof( o ) );
	int mid = n/2;
	pow( mid );
	Multi( x, x );
	if( n%2 ) Multi( x, p );
}
 
int main(){
	
//	freopen( "in.txt", "r", stdin );
//	freopen( "out.txt", "w", stdout );
	
	int T;
	scanf( "%d", &T );
	
	while( T -- ){
		
		scanf( "%d%d%d%d%d%d", &N, &K, &a, &b, &c, &m );
		
		int C = init();
		
		find( 0, E );
		
		if (C) {
			
			memcpy( r, x, sizeof( x ) );
			
			find( E + 1, cnt - 1 );
			memcpy( o, x, sizeof( x ) );
			
			int num = ( N - E - 1 ) / C;
			
			if( num ) pow( num );
			else make();
			
			memcpy( p, x, sizeof( x ) );
			
			int mod = ( N - E - 1 ) % C;
			
			if( mod ) find( E + 1, E + mod );
			else make();
			
			memcpy( q, x, sizeof( x ) );
			Multi( r, p );
			Multi( x, q );
		}
		cout << x[K] << endl;
		
	}
	
	return 0;
}  