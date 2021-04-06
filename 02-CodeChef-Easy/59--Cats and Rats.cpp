#include<iostream>
#include<climits>
using namespace std;
typedef long long int lli;
struct cat{lli pos_s,pos_e,time_s,time_e;bool forward;};
struct rat{lli pos_s,pos_e,time_s,time_e;bool forward;lli e = -1, eat = LLONG_MAX;};
void check_rat_for_every_cat(rat &r,cat &c, lli j){
	lli time_s = max(r.time_s,c.time_s), time_e = min(r.time_e,c.time_e); if (time_s <= time_e){
		if(c.forward && r.forward){lli t1=c.pos_s-c.time_s, t2=r.pos_s-r.time_s;
			if(t1 == t2){if (time_s < r.eat){r.eat = time_s;r.e = j+1;}}}
		else if(!(c.forward) && !(r.forward)){lli t1=c.pos_s+c.time_s, t2=r.pos_s+r.time_s;
			if (t1 == t2){if (r.eat > time_s){r.e = j+1;r.eat = time_s;}}}
		else if (c.forward && !(r.forward)){lli t1 = c.pos_s-c.time_s+time_s, t2 = r.pos_s+r.time_s-time_s;
			if (t1 <= t2){double f = ((double)abs(t1-t2)/2.0)+time_s;
				if (f <= time_e && r.eat >= f){r.eat = f;r.e = j+1;}}}
		else{lli t1 = c.pos_s+c.time_s-time_s, t2 = r.pos_s-r.time_s+time_s;
			if (t2 <= t1){double f = ((double)abs(t1-t2)/2.0)+time_s;
				if (f <= time_e && r.eat >= f){r.eat = f;r.e = j+1;}}}}}
int main(){int t; cin >> t; while (t--){int N, M; cin >> N >> M; cat c[N]; rat r[M];
		for (int i = 0; i < N; i++){cin >> c[i].pos_s >> c[i].pos_e >> c[i].time_s;
			c[i].time_e = c[i].time_s + abs(c[i].pos_s - c[i].pos_e);
			if (c[i].pos_s > c[i].pos_e){c[i].forward = false;} else{c[i].forward = true;}}
		for (int i = 0; i < M; i++){cin >> r[i].pos_s >> r[i].pos_e >> r[i].time_s;
			r[i].time_e = r[i].time_s + abs(r[i].pos_s - r[i].pos_e);
			if(r[i].pos_s > r[i].pos_e){r[i].forward = false;} else{r[i].forward = true;}}
	    for (int i = 0; i < M; i++){for (int j = 0; j < N; j++){check_rat_for_every_cat(r[i],c[j],j);}}
	    for (int i = 0; i < M; i++){cout << r[i].e << endl;}}return 0;}