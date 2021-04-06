#include<bits/stdc++.h>
using namespace std;

#define ll long long
ll R,C,sr,sc,tr,tc;

ll find(){
	if(sr==tr && tc>=sc) return tc-sc+1; // jika target 1 row dan disebelah kanan src
	if(sr==R && sc!=C){ //paling bawah dan ada celah
		ll base=0;
		
		if(tr < sr-(sc-1)){ // sector clear
			ll temp = sr-tr; //kotak lagi
			base += ( temp * C ); 
			if(temp%2==0) return base + tc;
			else return base + C-tc+1;
		}
		
		ll l,r;
		r = C-sc+1;
		l = C-r;
		
		ll dist = sr-tr;
		l -= dist;
		r += dist;
		
		int Case = (dist)%2;
		base += (dist)*C;
		
		if(Case){ // Case 1, l kanan, r kiri
			if(tc <= l) return base + tc + r;
			else return base -(l+1) + C-tc+1;
		}
		else{ // Case 2, l kiri, r kanan
			if(tc > l) return base + tc-l;		
			else{
				if(tr!=1) return base + (r*2)+1 + (l-tc)+1; 
				return base + C -tc+1; // kalau udah mentok diatas
			}
		}
		
	}
	if(sr <= tr){ // jika target ada dibawah / dikiri src
		ll base = C-sc+1 + R-sr+1 -1;  // bentuk L (kanan bawah)
		
		if(tc==C){ // target ada di col terakhir
			if(tr==R) return base; // dan di row terakhir
			return base - (R-tr);
		}
		ll box = ( (C-1) * (R-tr) ); // kotak bawah
		base += box;
		
		int lastDirect; //arah terakhir kotak
		if((R-tr)%2) lastDirect = 1; // kiri;
		else lastDirect = 0; // kanan;
	
		//exactly dibawah
		if(sr < tr){
			if(lastDirect) return base + tc; //odd -> kanan
			else return base + C-tc; //even -> kiri	
		}
		else{
			//target 1 baris dengan src dan ada di kiri
			if(lastDirect) return base + tc;
			else return base + sc-tc; 
		}
	}
	if(tr < sr){ // target ada diatas src
		ll base = ( C * (R-sr+1) ); // base = full box
		int lastDirect; //arah terakhir kotak
		if(sc==1){ // sc ada diujung kiri
			base += ( (sr-(tr+1)) * C );
			if((sr-tr)%2) return base + C-tc+1; 
			else return base + tc;	
		}
		
		//ada celah
		if((R-sr+1)%2 || sc==2) lastDirect = 1; // kiri; sc==2 -> celah cuma 1
		else lastDirect = 0; // kanan
		
		if(lastDirect){
			ll last2nd; //arah tearkhir ke target (1 baris sesudahnya)
			if((sr-tr)%2) last2nd = 1; //kiri
			else last2nd = 0; //kanan
			
			base += ( (sr-(tr+1)) * C ); //kotak lagi
			if(last2nd) return base + tc;
			else return base + C-tc+1;
		}
		else{
			// check position
			if(tr < sr-(sc-1)){ // sector clear
				ll temp = sr-(tr+1); //kotak lagi
				base += ( temp * C ); 
				if(temp%2) return base + C-tc+1;
				else return base + tc;
			}
			else{
				// trap
				ll l,r;
				r = C-sc+1;
				l = C-r;
				
				ll dist = sr-tr;
				l -= dist;
				r += dist;
				
				int Case = (dist+1)%2;
				base += (dist-1)*C;
				
				if(Case){ // Case 1, l kanan, r kiri
					if(tc <= l) return base + tc + r;
					else return base -(l+1) + C-tc+1;
				}
				else{ // Case 2, l kiri, r kanan
					if(tc > l) return base + tc-l;		
					else{
						if(tr!=1) return base + (r*2)+1 + (l-tc)+1; 
						return base + C -tc+1; // kalau udah mentok diatas
					}
				}
			}
		}
	}		
	return -1;
}

int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%lld %lld %lld %lld %lld %lld",&R,&C,&sr,&sc,&tr,&tc);
		printf("%lld\n",find());
	}
	return 0;
}
