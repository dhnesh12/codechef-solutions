#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define REP(i,n) FOR(i,0,n)
int n, k, N, n1;
int arr[901][901];
int p[901 * 901 + 1];
LL row[1000][20], col[1000][20], grid[1000][20], max1;
void update(int x, int y, int val){
	val--;
	int c = val / 60, v = val % 60;
	row[x][c] |= (1LL << v);
	col[y][c] |= (1LL << v);
	grid[(x / n1)*n1 + (y / n1)][c] |= (1LL << v);
	return;
}
int firstZero(LL x){
	int cnt = 0;
	while (x){
		if (!(x & 1))return cnt;
		cnt++; x /= 2;
	}
	return cnt;
}
int getOption(int x, int y, int overlap){
	int gr = (x / n1)*n1 + (y / n1);
	if (overlap == 3){
		REP(i, n){
			LL tmp = (row[x][i]) | (col[y][i]) | (grid[gr][i]);
			if (tmp == max1)continue;
			int cal = firstZero(tmp);

			if (60 * i + cal >= N)return 0;
				return 60 * i + cal + 1;
		}
	}

	else if (overlap == 2){

		REP(i, n){

			LL tmp1 = row[x][i] | col[y][i], tmp2 = row[x][i] | grid[gr][i], tmp3 = col[y][i] | grid[gr][i];
			if (tmp1 == max1 && tmp2 == max1 && tmp3 == max1)continue;
			LL tmp = min(tmp1, min(tmp2, tmp3));
			int cal = firstZero(tmp);
			if (60 * i + cal >= N)return 0;
			return 60 * i + cal + 1;
		}
	}
	else if (overlap == 1){
		REP(i, n){
			LL tmp1 = row[x][i], tmp2 = col[y][i], tmp3 = grid[gr][i];
			if (tmp1 == max1 && tmp2 == max1 && tmp3 == max1)continue;
			LL tmp;
			if (tmp1 != max1)tmp = tmp1;
			else if (tmp2 != max1)tmp = tmp2;
			else if (tmp3 != max1)tmp = tmp3;
			int cal = firstZero(tmp);
			if (60 * i + cal >= N)return 0;
			return 60 * i + cal + 1;
		}
	}
	return 0;
}
int main(){
	max1 = (1LL << 60) - 1;
	cin >> n >> k;
	N = n*n;
	n1 = n;
	n = (int)ceil(N / 60.0);
	REP(i, k){
	    	int x, y, val;
		cin >> x >> y >> val;
		x--; y--;
		arr[x][y] = val;
		update(x, y, val);
	}
	int lim = N*N, sz = lim;
	/*int *p = new int(lim+1);*/
	REP(i, lim)p[i] = i;
	REP(level, 3){
		sz = lim;
		REP(times, lim){
			int index = rand() % sz;
			int x = p[index] / N, y = p[index] % N;
			swap(p[index], p[sz - 1]);
			sz--;
			if (!arr[x][y]){
				int tmp = getOption(x, y, 3 - level);
				arr[x][y] = tmp;
				if (tmp)update(x, y, tmp);
			}
		}
	}
	REP(x, N){
		REP(y, N){
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
	return 0;
}
