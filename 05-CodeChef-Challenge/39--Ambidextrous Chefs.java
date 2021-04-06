import java.util.Scanner;
 
class AmbiChef {
	int t1, t2, team;
	AmbiChef() {
		team = 0;
	}
}
 
class Ambidex {
	static int T, N, M;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();
		for(int i=0; i<T; i++) {
			N = sc.nextInt();
			M = sc.nextInt();
			int count[] = new int[N];
			AmbiChef ac[] = new AmbiChef[M];
			for(int k=0; k<M; k++) {
				ac[k] = new AmbiChef();
				ac[k].t1 = sc.nextInt() - 1;
				count[ac[k].t1]++;
			}
			for(int k=0; k<M; k++) {
				ac[k].t2 = sc.nextInt() - 1;
				count[ac[k].t2]++;
			}
			generate(ac, count);
		}
	}
	public static void generate(AmbiChef x[], int count[]) {
		int v[] = new int[N];
		int tn=1;
		boolean ok = true;
		while(true) {
			for(int i=0; i<N; i++) {
				v[i] = 0;
			}
			for(int i=0; i<N; i++) {
				if(v[i]==0) {
					ok = false;
					for(int j=0; j<M; j++) {
						if(x[j].team==0 && (x[j].t1==i || x[j].t2==i) && v[x[j].t1]==0 && v[x[j].t2]==0) {
							x[j].team = tn;
							v[x[j].t1] = v[x[j].t2] = 1;
							count[x[j].t1]--;
							count[x[j].t2]--;
							ok = true;
							break;
						}
					}
					if(ok) continue;
					int tj=0, mc=-1, oth;
					for(int j=0; j<M; j++) {
						if(x[j].team==0 && (x[j].t1==i || x[j].t2==i)) {
							if(x[j].t1==i)
								oth = x[j].t2;
							else
								oth = x[j].t1;
							if(count[oth]>mc) {
								mc = count[oth];
								tj = j;
							}
							ok = true;
						}
					}
					if(ok) {
						x[tj].team = tn;
						v[x[tj].t1] = v[x[tj].t2] = 1;
					} else {
						break;
					}
				}
			}
			if(!ok) break;
			tn++;
		}
		for(int i=0; i<M; i++) {
			System.out.print((x[i].team<tn?x[i].team:0) + " ");
		}
		System.out.println();
	}
}
 