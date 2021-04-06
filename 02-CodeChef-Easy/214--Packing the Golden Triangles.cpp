#include <algorithm>
#include <stdio.h>
 
using std::sort;
 
int L[1000];
struct _R {
  int R2, R1;
} R[1000];
 
bool R_cmp(const struct _R &a, const struct _R &b) {
  if(a.R2 == b.R2)
    return a.R1 < b.R1;
  return a.R2 < b.R2;
}
 
void do_it()
{
  int i, j, n, n_box, n_band;
 
  scanf("%i", &n_box);
  for(j = 0; j < n_box; j++){
    scanf("%i", &L[j]);
    L[j] *= 7;
  }
 
  scanf("%i", &n_band);
  for(j = 0; j < n_band; j++){
    scanf("%i", &R[j].R1);
    scanf("%i", &R[j].R2);
    R[j].R1 *= 11;
    R[j].R2 *= 11;
  }
 
  sort(L, L+n_box);
  sort(R, R+n_band, &R_cmp);

 
  n = 0;
  for(i = 0; i < n_box; i++){
    for(j = 0; j < n_band; j++){
      if(R[j].R1 <= L[i] &&
	 L[i] <= R[j].R2){
	n++;
	R[j].R1 = (1<<30);
	break;
      }
    }
  }
 
  printf("%i\n", n);
 
}
 
int main(int argc, char **argv)
{
  int n_test, i;
  scanf("%i", &n_test);
  for(i = 0; i < n_test; i++){
    do_it();
  }
  return 0;
}