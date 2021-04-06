#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

#define TIME_LIMIT_1 3.85//4.93
#define TIME_LIMIT 4.93
#define MAX_TESTS 40
#define NMAX 302
#define MAX_NODES 10001

int bsol[MAX_TESTS][MAX_NODES], nbsol[MAX_NODES], bscore[MAX_TESTS], bbused[MAX_TESTS];
vector<pair<int, int> > vec[MAX_TESTS][NMAX];
int N[MAX_TESTS], B[MAX_TESTS], NRUNS[MAX_TESTS], NSUM;
int T, TEND1, TEND;

void ReadInput() {
	int i, j, c, k, t, M;

	//freopen("x.txt", "r", stdin);
	scanf("%d", &T);
	for (NSUM = t = 0; t < T; t++) {
		scanf("%d %d %d", &N[t], &M, &B[t]);
		if (0&&N[t] <= 17) {
			int tnext = (int) (clock() + 0.5 * CLOCKS_PER_SEC);
			while (clock() < tnext);
		}
	
		for (k = 0; k < M; k++) {
			scanf("%d %d %d", &i, &j, &c);
			vec[t][i].push_back(make_pair(j, c));
		}
		nbsol[t] = 0;
		bscore[t] = 1;
		bbused[t] = 0;
		NSUM += N[t];
	}
}

int d[MAX_TESTS][NMAX][NMAX], pred[MAX_TESTS][NMAX][NMAX];
char dcomputed[MAX_TESTS][NMAX];
priority_queue<pair<int, int> > dset;
int visited[NMAX];
int csol[MAX_NODES], ncsol;
int ptmp[NMAX], nptmp, cc[NMAX];
int cand[NMAX], ncand, cmax;
int nonv[NMAX], nnonv;

int UpdateSol(int t, int csol[], int ncsol, int cscore, int BUSED) {
	int i, j;
	if (cscore > bscore[t] || (cscore == bscore[t] && BUSED < bbused[t])) {
		fprintf(stderr, "t=%d new bscore=%d bused=%d/%d\n", t, cscore, BUSED, B[t]);
		bscore[t] = cscore;
		bbused[t] = BUSED;
		memcpy(bsol[t], csol, ncsol * sizeof(int));
		nbsol[t] = ncsol;
		return 1;
	}	
	return 0;
}

void Dijkstra(int t, int s) {
	int i, j, k, c;
	pair<int, int> p;

	if (dcomputed[t][s])
		return;

	for (i = 0; i < N[t]; i++)
		d[t][s][i] = B[t] + 1;
	
	d[t][s][s] = 0;
	dset.push(make_pair(0, s));
	
	while (dset.size() > 0) {
		p = dset.top();
		dset.pop();
		i = p.second;

		if (-p.first != d[t][s][i])
			continue;
	
		for (k = 0; k < vec[t][i].size(); k++) {
			j = vec[t][i][k].first;
			c = vec[t][i][k].second;
			if (d[t][s][i] + c < d[t][s][j]) {
				d[t][s][j] = d[t][s][i] + c;
				pred[t][s][j] = i;
				dset.push(make_pair(-d[t][s][j], j));
			}
		}
	}

	dcomputed[t][s] = 1;
}

#define SMALL_NMAX 16
int bmin[1 << SMALL_NMAX][SMALL_NMAX], ipred[1 << SMALL_NMAX][SMALL_NMAX];

void DP(int t) {
	int conf, i, j, k, nmax, bconf, bi;

	for (i = 0; i < N[t]; i++)
		Dijkstra(t, i);

	for (conf = 0; conf < (1 << N[t]); conf++)
		for (i = 0; i < N[t]; i++)
			bmin[conf][i] = B[t] + 1;

	bmin[1][0] = 0;
	ipred[1][0] = -1;
	
	for (conf = 1; conf < (1 << N[t]); conf++) {
		for (i = 0; i < N[t]; i++)
			if ((conf & (1 << i)) && bmin[conf][i] <= B[t]) {
				//fprintf(stderr, "conf=%d i=%d: %d\n", conf, i, bmin[conf][i]);
				for (j = 0; j < N[t]; j++) {
					if ((conf & (1 << j)) == 0 && bmin[conf][i] + d[t][i][j] < bmin[conf | (1 << j)][j]) {
						bmin[conf | (1 << j)][j] = bmin[conf][i] + d[t][i][j];
						ipred[conf | (1 << j)][j] = i;
					}
				}
			}
	}

	nmax = 0;
	for (conf = 1; conf < (1 << N[t]); conf++)
		for (i = 0; i < N[t]; i++)
			if (bmin[conf][i] <= B[t]) {
				k = 0;
				for (j = 0; j < N[t]; j++)
					if (conf & (1 << j))
						k++;
				if (k > nmax) {
					nmax = k;
					bconf = conf;
					bi = i;
				}
			}

	nptmp = 0;
	while (bi >= 0) {
		ptmp[nptmp++] = bi;
		i = bi;
		bi = ipred[bconf][bi];
		bconf ^= (1 << i);
	}

	ncsol = 0;
	for (i = nptmp - 1; i >= 0; i--)
		csol[ncsol++] = ptmp[i];
	
	UpdateSol(t, csol, ncsol, nmax, -1);
}

int TryInsert(int t, int a, int b, int x, int op) {
	int j = b, escore = 0;

	while (j != a) {
		visited[j] -= op;
		if (visited[j] == 0)
			escore--;
		j = pred[t][a][j];
	}

	j = x;
	while (j != a) {
		visited[j] += op;
		if (visited[j] == 1)
			escore++;
		j = pred[t][a][j];
	}

	j = b;
	while (j != x) {
		visited[j] += op;
		if (visited[j] == 1)
			escore++;
		j = pred[t][x][j];
	}

	return escore;
}

int TryRemove(int t, int a, int b, int x, int op) {
	int j = b, escore = 0;

	while (j != a) {
		visited[j] += op;
		if (visited[j] == 1)
			escore++;
		j = pred[t][a][j];
	}

	j = x;
	while (j != a) {
		visited[j] -= op;
		if (visited[j] == 0)
			escore--;
		j = pred[t][a][j];
	}

	j = b;
	while (j != x) {
		visited[j] -= op;
		if (visited[j] == 0)
			escore--;
		j = pred[t][x][j];
	}

	return escore;
}

int cscore, BUSED;

void ImproveSol(int t) {
	int i, j, k, escore, bnewscore, bnewbused;

	/*
	for (j = 0; 0&&j < N[t]; j++)
		if (!visited[j] && BUSED + d[t][csol[ncsol - 1]][j] <= B[t]) {
			k = j;
			while (k != csol[ncsol - 1]) {
				if (!visited[k])
					cscore++;
				visited[k]++;
				k = pred[t][csol[ncsol - 1]][k];
			}
			BUSED += d[t][csol[ncsol - 1]][j];
			csol[ncsol++] = j;
		}
	*/
	
	for (i = 0; i + 1 < ncsol; i++)
		for (j = 0; j < N[t]; j++)
			if (!visited[j] && BUSED - d[t][csol[i]][csol[i + 1]] + d[t][csol[i]][j] <= B[t]) {
				Dijkstra(t, j);
				if (BUSED - d[t][csol[i]][csol[i + 1]] +
					d[t][csol[i]][j] <= B[t] - d[t][j][csol[i + 1]]) {
					escore = TryInsert(t, csol[i], csol[i + 1], j, 1);

					bnewbused = BUSED - d[t][csol[i]][csol[i + 1]] + d[t][csol[i]][j] + d[t][j][csol[i + 1]];
					bnewscore = cscore + escore;
					if (bnewscore > cscore || (bnewscore == cscore && bnewbused < BUSED)) {
						cscore = bnewscore;
						BUSED = bnewbused;
						for (k = ncsol - 1; k > i; k--)
							csol[k + 1] = csol[k];
						ncsol++;
						csol[i + 1] = j;
					} else
						TryInsert(t, csol[i], csol[i + 1], j, -1);
				}
			}

	UpdateSol(t, csol, ncsol, cscore, BUSED);
}

void DP2(int t, int start, int v[], int nv) {
	int conf, i, j, k, nmax, busedmin, bconf, bi;

	for (i = 0; i < nv; i++)
		Dijkstra(t, v[i]);

	for (conf = 0; conf < (1 << nv); conf++)
		for (i = 0; i < nv; i++)
			bmin[conf][i] = B[t] + 1;
	
	for (i = 0; i < nv; i++) {
		bmin[1 << i][i] = BUSED + d[t][start][v[i]];
		ipred[1 << i][i] = -1;
	}
	
	for (conf = 1; conf < (1 << nv); conf++) {
		for (i = 0; i < nv; i++) {
			if ((conf & (1 << i)) && bmin[conf][i] <= B[t]) {
				for (j = 0; j < nv; j++) {
					if ((conf & (1 << j)) == 0 && bmin[conf][i] + d[t][v[i]][v[j]] < bmin[conf | (1 << j)][j]) {
						bmin[conf | (1 << j)][j] = bmin[conf][i] + d[t][v[i]][v[j]];
						ipred[conf | (1 << j)][j] = i;
					}
				}
			}
		}
	}

	nmax = 0;
	busedmin = 0;
	bi = -1;

	for (conf = 1; conf < (1 << nv); conf++) {
		k = 0;
		for (j = 0; j < nv; j++)
			if (conf & (1 << j))
				k++;
		if (k < nmax)
			continue;

		for (i = 0; i < nv; i++)
			if (bmin[conf][i] <= B[t] &&
				(k > nmax || (k == nmax && bmin[conf][i] < busedmin))) {
				nmax = k;
				busedmin = bmin[conf][i];
				bconf = conf;
				bi = i;
			}
	}

	if (nmax == 0) {
		exit(3);
		return;
	}
	
	cscore += nmax;
	BUSED = busedmin;
	
	nptmp = 0;
	while (bi >= 0) {
		ptmp[nptmp++] = v[bi];
		i = bi;
		bi = ipred[bconf][bi];
		bconf ^= (1 << i);
	}

	for (i = nptmp - 1; i >= 0; i--)
		csol[ncsol++] = ptmp[i];
}

vector<pair<int, int> > vc, vd;
int dmin[NMAX + 1][NMAX + 1], cm[NMAX + 1], dm[NMAX + 1];
//double r[NMAX];

void Greedy1(int t) {
	int i, j, jidx, jj, jjidx, k, p, q, c, jcmax, jcsum, tmpcmax, cnt, mincscore, updated, escore;

	NRUNS[t]++;

	visited[0] = 1;
	for (i = 1; i < N[t]; i++)
		visited[i] = 0;
	
	BUSED = 0;
	cscore = 1;
	ncsol = 1;
	csol[0] = 0;

	mincscore = bscore[t] - 2;

	while (BUSED < B[t]) {
		i = csol[ncsol - 1];
		Dijkstra(t, i);

		nnonv = 0;
		for (j = 0; j < N[t]; j++)
			if (!visited[j] && BUSED + d[t][i][j] <= B[t])
				nonv[nnonv++] = j;

		if (nnonv == 0)
			break;

		//if (nnonv <= 10) {
		//	DP2(t, i, nonv, nnonv);
		//	break;
		//}
	
		tmpcmax = 0;
		//double rmin = B[t] + 1;
	
		vc.resize(nnonv);
		for (jidx = 0; jidx < nnonv; jidx++) {
			j = nonv[jidx];
			k = j;
			cc[j] = 0;
			while (k != i) {
				if (!visited[k])
					cc[j]++;
				k = pred[t][i][k];
			}
			
			if (cc[j] > tmpcmax)
				tmpcmax = cc[j];

			//r[j] = (double) d[t][i][j] / (double) cc[j];
			//if (r[j] < rmin)
			//	rmin = r[j];
	
			vc[jidx].first = -cc[j];
			vc[jidx].second = j;
		}

		if (tmpcmax == 0)
			break;
	
		ncand = cmax = 0;

		//rmin = (rmin + 0.1) * 3.0;

		sort(vc.begin(), vc.end());
		for (jidx = 0; jidx < vc.size(); jidx++) {
			j = vc[jidx].second;
			if ((cc[j] <= 0) || (cc[j] < tmpcmax - 1))
				break;
	
			BUSED += d[t][i][j];
			Dijkstra(t, j);

			k = j;
			while (k != i) {
				visited[k]++;
				k = pred[t][i][k];
			}

			jcmax = 0;
			for (jjidx = 0, cnt = 0; jjidx < nnonv; jjidx++) {
				jj = nonv[jjidx];
				if (jj == j || visited[jj])
					continue;

				if (BUSED + d[t][j][jj] <= B[t]) {
					cnt++;
					k = jj;
					c = 0;
					while (k != j) {
						if (!visited[k])
							c++;
						k = pred[t][j][k];
					}
	
					if (c > jcmax)
						jcmax = c;
				}
			}

			if (0&&cnt <= 15) {
				sort(vd.begin(), vd.end());			
				for (k = 0; k < cnt; k++) {
					dmin[k][1] = vd[k].first;
					//cm[k] = 1;
					//dm[k] = vd[k].first;
					Dijkstra(t, vd[k].second);
				}	

				for (k = 2, updated = 1; k <= cnt && updated; k++) {
					updated = 0;
					for (p = 0; p + 1 < k; p++)
						dmin[p][k] = B[t] - BUSED + 1;
					for (p = k - 1; p < cnt; p++) {
						dmin[p][k] = B[t] - BUSED + 1;
						if (dmin[p][k - 1] == dmin[p][k])
							continue;
						for (q = k - 2; q < p; q++)
							if (dmin[q][k - 1] + d[t][vd[q].second][vd[p].second] < dmin[p][k]) {
								dmin[p][k] = dmin[q][k - 1] + d[t][vd[q].second][vd[p].second];
								updated = 1;
							}
					}
				}
				k--;

				/*
				for (p = 1; p < cnt; p++)
					for (q = p - 1; q >= 0; q--) {
						k = BUSED + dm[q] + d[t][vd[q].second][vd[p].second];
						if (k > B[t])
							continue;
						k = dm[q] + d[t][vd[q].second][vd[p].second];
						if (cm[q] + 1 > cm[p] ||
							(cm[q] + 1 == cm[p] && k < dm[p])) {
							cm[p] = cm[q] + 1;
							dm[p] = k;
						}
					}
	
				for (k = 0, p = 0; p < cnt; p++)
					if (cm[p] > k)
						k = cm[p];
				*/
				jcmax = cc[j] + k;	
			} else {
				k = jcmax;
				jcmax = cc[j] + k + ((cnt - k) / 12);
			}

			if (cscore + cc[j] + cnt < mincscore)
				jcmax = -1;
			//if (cscore + cc[j] + cnt < bscore[t] - 15)
			//	continue;

			if (jcmax > cmax) {
				cand[0] = j;
				ncand = 1;
				cmax = jcmax;
			} else if (jcmax == cmax)
				cand[ncand++] = j;

			k = j;
			while (k != i) {
				visited[k]--;
				k = pred[t][i][k];
			}

			BUSED -= d[t][i][j];
		}

		if (cmax == 0)
			break;

		if (NRUNS[t] == 1) {
			j = cand[0];
			for (k = 1; k < ncand; k++)
				if (d[t][i][cand[k]] < d[t][i][j])
					j = cand[k];
		} else {
			vc.resize(ncand);
			for (k = 0; k < ncand; k++) {
				vc[k].first = d[t][i][cand[k]];
				vc[k].second = cand[k];
			}

			sort(vc.begin(), vc.end());

			if (cscore <= N[t] / 5) {
				if (vc.size() >= 4)
					vc.resize(4);
			} else if (cscore <= N[t] / 2) {
				if (vc.size() >= 2)
					vc.resize(2);
			} else {
				vc.resize(1);
			}
			
			j = vc[rand() % vc.size()].second;
		}

		BUSED += d[t][i][j];
		csol[ncsol++] = j;

		while (j != i) {
			if (!visited[j])
				cscore++;
			visited[j]++;
			j = pred[t][i][j];
		}

		for (i = 2; i < ncsol; i++) {
			escore = TryRemove(t, csol[i - 2], csol[i], csol[i - 1], 1);

			if (escore >= 0) {
				cscore += escore;
				BUSED = BUSED - d[t][csol[i - 2]][csol[i - 1]] - d[t][csol[i - 1]][csol[i]] + d[t][csol[i - 2]][csol[i]];
				for (k = i; k < ncsol; k++)
					csol[k - 1] = csol[k];
				ncsol--;
			} else
				TryRemove(t, csol[i - 2], csol[i], csol[i - 1], -1);
		}
	}

	if (cscore >= mincscore)
		ImproveSol(t);
}

int o[NMAX], stk[NMAX + 1], nstk;
int pm[NMAX];

void ImproveSol2(int t) {
	int i, j, k, p, q, M;

	visited[0] = 1;
	for (i = 1; i < N[t]; i++)
		visited[i] = 0;

	o[0] = 0;
	M = 1;

	for (i = 1; i < nbsol[t]; i++) {
		nstk = 0;
		j = bsol[t][i];
		while (j != bsol[t][i - 1]) {
			if (!visited[j]) {
				nstk++;
				stk[nstk] = j;
				visited[j] = 1;
			}
			j = pred[t][bsol[t][i - 1]][j];
		}

		while (nstk > 0) {
			o[M++] = stk[nstk];
			nstk--;
		}
	}

	while (M < N[t]) {
		do {
			i = rand() % N[t];
		} while (visited[i]);
		visited[i] = 1;
		o[M++] = i;
	}

	cm[0] = 1;
	dm[0] = 0;

	for (p = 1; p < M; p++) {
		Dijkstra(t, o[p]);

		dm[p] = B[t] + 1;
		cm[p] = 0;
		for (q = p - 1; q >= 0; q--) {
			k = dm[q] + d[t][o[q]][o[p]];
			if (k > B[t])
				continue;
			if (cm[q] + 1 > cm[p] ||
				(cm[q] + 1 == cm[p] && k < dm[p])) {
				cm[p] = cm[q] + 1;
				dm[p] = k;
				pm[p] = q;
			}
		}
	}

	for (k = 0, p = 0; p < M; p++)
		if (cm[p] > k) {
			k = cm[p];
			q = p;
		}
	
	if (k > bscore[t]) {
		exit(1);

		bscore[t] = k;
		bbused[t] = dm[q];

		nbsol[t] = k;
		while (q > 0) {
			bsol[t][k - 1] = o[q];
			k--;
			q = pm[q];
		}

		bsol[t][0] = 0;
	}
}

int predd[NMAX + 1][NMAX + 1];

void ImproveSol3(int t) {
	int i, j, k, lp, lk, p, q, qmin, M, updated;

	if (bscore[t] == 1)
		return;

	visited[0] = 1;
	for (i = 1; i < N[t]; i++)
		visited[i] = 0;

	o[0] = 0;
	M = 1;

	for (i = 1; i < nbsol[t]; i++) {
		nstk = 0;
		j = bsol[t][i];
		while (j != bsol[t][i - 1]) {
			if (!visited[j]) {
				nstk++;
				stk[nstk] = j;
				visited[j] = 1;
			}
			j = pred[t][bsol[t][i - 1]][j];
		}

		while (nstk > 0) {
			o[M++] = stk[nstk];
			nstk--;
		}
	}

	while (M < N[t]) {
		do {
			i = rand() % N[t];
			j = rand() % (M + 1);
		} while (visited[i]);
		visited[i] = 1;

		for (k = M - 1; k >= j; k--)
			o[k + 1] = o[k];
		o[j] = i;
		M++;		
	}

	dmin[0][1] = 0;
	dmin[0][2] = B[t] + 1;
	
	for (k = 1; k < N[t]; k++) {
		dmin[k][1] = B[t] + 1;
		dmin[k][2] = d[t][0][o[k]];
		predd[k][2] = 0;
		Dijkstra(t, o[k]);
	}

	lp = lk = -1;

	for (k = 3, updated = 1; k <= N[t] && updated; k++) {
		updated = 0;
		for (p = 0; p + 1 < k; p++)
			dmin[p][k] = B[t] + 1;
		for (p = k - 1; p < N[t]; p++) {
			dmin[p][k] = B[t] + 1;
			if (dmin[p][k - 1] == dmin[p][k])
				continue;
			//if (p < bscore[t])
				qmin = max(k - 2, p - 40);
			//else
			//	qmin = k - 2;

			for (q = p - 1; q >= qmin; q--)
				if (dmin[q][k - 1] + d[t][o[q]][o[p]] < dmin[p][k]) {
					dmin[p][k] = dmin[q][k - 1] + d[t][o[q]][o[p]];
					updated = 1;
					predd[p][k] = q;
					lp = p;
					lk = k;
				}

			if (lp >= 0 && dmin[lp][lk] > B[t])
				exit(2);
		}
		
		if (!updated)
			break;
	}

//	return;

	k--;
	if (k > bscore[t]) {
		for (p = k - 1; p < N[t]; p++)
			if (dmin[p][k] <= B[t])
				break;

		nbsol[t] = k;
		while (p > 0) {
			bsol[t][k - 1] = o[p];
			p = predd[p][k];
			k--;
		}
	
		bsol[t][0] = 0;
	}
}

void Solve() {
	int t, i, tnext;
	double mnext, m;
	
	srand(6667);

	for (t = 0; t < T; t++) {
		NRUNS[t] = 0;
		if (N[t] <= SMALL_NMAX)
			DP(t);
		else {
			//Dijkstra(t, 0);
			//for (i = 1; i < N[t]; i++)
			//	if (d[t][0][i] < B[t])
			//		Dijkstra(t, i);
			Greedy1(t);
		}
	}

//	tnext = 0;
	while (clock() < TEND1) {
		tnext = -1;
		mnext = -1.0;
		for (t = 0; t < T; t++) {
			if (bscore[t] == N[t] || N[t] <= SMALL_NMAX)
				continue;
			m = (double) (N[t] - bscore[t]) / (double) NRUNS[t];
			if (m > mnext) {
				mnext = m;
				tnext = t;
			}
		}
		
//		tnext = (tnext + 1) % T;
//		while (bscore[tnext] == N[tnext] || N[tnext] <= SMALL_NMAX) 
//			tnext = (tnext + 1) % T;
	
		Greedy1(tnext);
	}

	for (t = 0; t < T; t++)
		if (N[t] > SMALL_NMAX && bscore[t] < N[t])
			ImproveSol3(t);
}

int nprinted;

void PrintShortestPath(int t, int s, int d) {
	if (s == d)
		return;
	PrintShortestPath(t, s, pred[t][s][d]);
	printf("%d ", d);
	nprinted++;
}

void WriteOutput() {
	int i, t;
	for (t = 0; t < T; t++) {
		nprinted = 0;
		for (i = 1; i < nbsol[t]; i++)
			PrintShortestPath(t, bsol[t][i - 1], bsol[t][i]);
		printf("-1\n");

		if (nprinted > 10000)
			exit(1);
	}
}

int main() {
	TEND1 = (int) (clock() + TIME_LIMIT_1 * CLOCKS_PER_SEC);
	TEND = (int) (clock() + TIME_LIMIT * CLOCKS_PER_SEC);
	ReadInput();
	Solve();
	WriteOutput();
	return 0;
}
