#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
clock_t pocetno, krajnje;
float vreme;
map <long long, int> ord;
int n,m,k,S,D,W,disam,benzin,nosim,brres,bestbrres,zarada,bestzarada,pocetni,preostalo;
int dirord[100005],temp[100005];
int resenje[10000000][2],bestresenje[10000000][2];// kasnije odradi s vektorima ako bude trebalo
struct slognarudzbe {
    long long cv1;
    int cv2, tez, zarada, ind;
    bool done;
//    bool operator < (const slognarudzbe &a) const{
//      return zarada>a.zarada;}
} narudzba[100005];
bool myfunc1(const struct slognarudzbe a, const struct slognarudzbe b){
    return (a.zarada>b.zarada or (a.zarada==b.zarada and a.tez<b.tez));
 }
bool myfunc2(const struct slognarudzbe a, const struct slognarudzbe b){
    return  dirord[a.cv1] >dirord[b.cv1] or
           (dirord[a.cv1]==dirord[b.cv1] and a.cv1 <b.cv1) or
           (dirord[a.cv1]==dirord[b.cv1] and a.cv1==b.cv1 and a.zarada>b.zarada);
 }
bool myfunc3(const struct slognarudzbe a, const struct slognarudzbe b){//izbaci ako vreme trazi
    return  dirord[a.cv1] >dirord[b.cv1] or
           (dirord[a.cv1]==dirord[b.cv1] and a.cv1 >b.cv1) or
           (dirord[a.cv1]==dirord[b.cv1] and a.cv1==b.cv1 and a.zarada>b.zarada);
 }
struct slogcvora {
    int fs,ls;
} cvor[100005];
struct slogveze {
    int cvor, sused; int tezina;
    bool operator < (const slogveze &a) const{
      return cvor<a.cvor;}/* or
              (cvor==a.cvor and sused<a.sused) or
              (cvor==a.cvor and sused==a.sused and tezina<a.tezina));}
    bool operator == (const slogveze &a) const {
      return ((cvor==a.cvor) and (sused==a.sused));}*/
} veza[200002];
void check(){
  if (zarada>bestzarada) {
    bestzarada=zarada;
    bestbrres=brres;
    for (int i=1; i<=bestbrres; i++) {
       bestresenje[i][0]=resenje[i][0];
       bestresenje[i][1]=resenje[i][1];
    }
  }
}
void reset(){
  zarada=0;
  brres=0;
  for (int i=1; i<=k; i++) narudzba[i].done=false;
  benzin=D;
  disam=S;
  nosim=0;
  preostalo=k;
  memset(dirord, 0, sizeof(dirord));
  for (int i=1; i<=k; i++) dirord[narudzba[i].cv1]++;
}
void ispisrezultata(int x){
//  if (x) printf("Ispisujem reyultat na mestu X%d\n",x);
  printf("%d\n",bestbrres);
  for (int i=1; i<=bestbrres; i++) printf("%d %d\n", bestresenje[i][0],bestresenje[i][1]);
}
void ubacisusedaakomoze(long long x) {
  for (int i=cvor[x].fs; i<=cvor[x].ls; i++) {
    int order=ord[x*1000000+veza[i].sused];
    if (!order) return;
    if (!dirord[order]) return;
    if (nosim+narudzba[order].tez>W) return;
    if (nosim+narudzba[order].tez>W) return;
 
  }
}
int Dist[10005][10005],P[10005][10005],idx[10005];
void putanja(int i, int j){
  while (P[i][j]) {
    j=P[i][j];
    resenje[++brres][0]=0;
    resenje[  brres][1]=j;
//    ubacisusedaakomoze(j);
  }
}
void odradinarudzbu(int order){
  if (order==0) return;
  if (!(Dist[disam][narudzba[order].cv1]+Dist[narudzba[order].cv1][narudzba[order].cv2]<=benzin)) return;
  if (narudzba[order].tez>W) return;
  if (narudzba[order].done) return;
  if (disam!=narudzba[order].cv1)
    putanja(narudzba[order].cv1,disam);
 
  resenje[++brres][0]=1;
  resenje[  brres][1]=narudzba[order].ind;
  nosim+=narudzba[order].tez;
  putanja(narudzba[order].cv2,narudzba[order].cv1);
  resenje[++brres][0]=2;
  resenje[  brres][1]=narudzba[order].ind;
  benzin-=Dist[disam][narudzba[order].cv1]+Dist[narudzba[order].cv1][narudzba[order].cv2];
  disam=narudzba[order].cv2;
  zarada+=narudzba[order].zarada;
  nosim-=narudzba[order].tez;
  narudzba[order].done=true;
  dirord[narudzba[order].cv1]--;
  preostalo--;
}
int nadjinarudzbu(int x){
  for (int i=1; i<=k; i++) if (narudzba[i].cv1==x and !narudzba[i].done) return i;
  return 0;
}
int prvaneodradjenanarudzba(){
  for (int i=1; i<=k; i++) if (!narudzba[i].done) return i;
}
int najblizaneodradjenanarudzba(){
  int nbl=1000000000;
  int pos;
  for (int i=1; i<=k; i++)
    if (!narudzba[i].done)
      if (nbl >Dist[disam][narudzba[i].cv1] and Dist[disam][narudzba[i].cv1]<=benzin) {
        nbl=Dist[disam][narudzba[i].cv1];
        pos=i;
      }
  return pos;
}
int najblizaneodradjenadestinacija(){
  int nbl=1000000000;
  int pos=0;
  for (int i=1; i<=k; i++)
    if (!narudzba[i].done)
      if (nbl >Dist[disam][narudzba[i].cv1]+Dist[narudzba[i].cv1][narudzba[i].cv2] and
          Dist[disam][narudzba[i].cv1]+Dist[narudzba[i].cv1][narudzba[i].cv2]<=benzin) {
        nbl=Dist[disam][narudzba[i].cv1]+Dist[narudzba[i].cv1][narudzba[i].cv2];
        pos=i;
      }
  return pos;
}
int PV[1000005],MinD[100005], X[20000005], Source, Dest;
int najblizaneodradjenanarudzbaV(){
  int nbl=1000000000;
  int pos;
  for (int i=1; i<=k; i++)
    if (!narudzba[i].done)
      if (nbl >MinD[narudzba[i].cv1] and MinD[narudzba[i].cv1]<=benzin) {
        nbl=MinD[narudzba[i].cv1];
        pos=i;
      }
  return pos;
}
void Dijkstra(int Source) {
int Pocetak, Kraj, i;
  for (int i=1; i<=n; i++) MinD[i]=1000000009;
  for (int i=1; i<=n; i++) P[Source][i]=Source;
  P[Source][Source]=0;
  MinD[Source]=0;
  Pocetak=1;
  Kraj=1;
  X[1]=Source;
  while (Pocetak<=Kraj) {
    for (int i=cvor[X[Pocetak]].fs; i<=cvor[X[Pocetak]].ls; i++)
      if (MinD[veza[i].sused] > MinD[X[Pocetak]] + veza[i].tezina) {
          MinD[veza[i].sused]=MinD[X[Pocetak]] + veza[i].tezina;
          P[Source][veza[i].sused] = X[Pocetak];
          Kraj++;
          X[Kraj]=veza[i].sused;
      }
    Pocetak++;
  }
}
void DijkstraV(int Source) {
int Pocetak, Kraj, i;
  for (int i=1; i<=n; i++) MinD[i]=1000000009;
  for (int i=1; i<=n; i++) PV[i]=Source;
  PV[Source]=0;
  MinD[Source]=0;
  Pocetak=1;
  Kraj=1;
  X[1]=Source;
  while (Pocetak<=Kraj) {
    for (int i=cvor[X[Pocetak]].fs; i<=cvor[X[Pocetak]].ls; i++)
      if (MinD[veza[i].sused] > MinD[X[Pocetak]] + veza[i].tezina) {
          MinD[veza[i].sused]=MinD[X[Pocetak]] + veza[i].tezina;
          PV[veza[i].sused] = X[Pocetak];
          Kraj++;
          X[Kraj]=veza[i].sused;
      }
    Pocetak++;
  }
}
void mali(){
  reset();
  for (int i=1; i<=n; i++) {
    Dijkstra(i);
    for (int j=1; j<=n; j++) Dist[i][j]=MinD[j];
  }
  while (preostalo) {
    if (dirord[disam]) odradinarudzbu(nadjinarudzbu(disam));
    else odradinarudzbu(prvaneodradjenanarudzba());
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
void mali1(){
  reset();
  for (int i=1; i<=n; i++) {
    Dijkstra(i);
    for (int j=1; j<=n; j++) Dist[i][j]=MinD[j];
  }
  while (preostalo) {
    if (dirord[disam]) odradinarudzbu(nadjinarudzbu(disam));
    else odradinarudzbu(najblizaneodradjenanarudzba());
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
void mali2(){
  reset();
  for (int i=1; i<=n; i++) {
    Dijkstra(i);
    for (int j=1; j<=n; j++) Dist[i][j]=MinD[j];
  }
  while (preostalo) {
    if (dirord[disam]) odradinarudzbu(nadjinarudzbu(disam));
    else odradinarudzbu(najblizaneodradjenadestinacija());
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
void DFS(int x, int duzina){
  idx[x]=1;
  for (int j=cvor[x].fs; j<=cvor[x].ls; j++)
  if (!idx[veza[j].sused]){
    Dist[pocetni][veza[j].sused]=duzina+veza[j].tezina;
    P[pocetni][veza[j].sused]=x;
    DFS(veza[j].sused, duzina+veza[j].tezina);
  }
}
void stablo(){
  reset();
  for (int j=1; j<=n; j++) Dist[j][j]=0;
  for (int i=1; i<=n; i++) {
    memset(idx, 0, sizeof(idx));
    pocetni=i;
    DFS(i,0);
  }
  while (preostalo) {
    if (dirord[disam]) odradinarudzbu(nadjinarudzbu(disam));
    else odradinarudzbu(prvaneodradjenanarudzba());
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
void odnesiivratise(int order, int a, int b, bool samotamo){
  resenje[++brres][0]=1;
  resenje[  brres][1]=narudzba[order].ind;
  int br=0;
  int j=b;
  while (PV[j]) {
    temp[++br]=j;
    j=PV[j];
  }
//  printf("narudzba=%d, od %d do %d, samotamo==%d\n", order,a,b,samotamo);
 
  temp[++br]=j;
  for (int i=br-1; i>=1; i--) {
    resenje[++brres][0]=0;
    resenje[  brres][1]=temp[i];
  }
  resenje[++brres][0]=2;
  resenje[  brres][1]=narudzba[order].ind;
  if (samotamo) {
      benzin-=MinD[narudzba[order].cv2];
      disam=narudzba[order].cv2;
      zarada+=narudzba[order].zarada;
      narudzba[order].done=true;
      dirord[narudzba[order].cv1]--;
      preostalo--;
      return;
  }
  for (int i=2; i<=br; i++) {
    resenje[++brres][0]=0;
    resenje[  brres][1]=temp[i];
  }
  benzin-=2*MinD[narudzba[order].cv2];
  zarada+=narudzba[order].zarada;
  narudzba[order].done=true;
  dirord[narudzba[order].cv1]--;
  preostalo--;
}
void odnesi(int order){
  resenje[++brres][0]=1;
  resenje[  brres][1]=narudzba[order].ind;
  int br=0;
  int j=narudzba[order].cv2;
  while (PV[j]) {
    temp[++br]=j;
    j=PV[j];
  }
  temp[++br]=j;
  for (int i=br-1; i>=1; i--) {
    resenje[++brres][0]=0;
    resenje[  brres][1]=temp[i];
  }
  resenje[++brres][0]=2;
  resenje[  brres][1]=narudzba[order].ind;
  benzin-=MinD[narudzba[order].cv2];
  disam=narudzba[order].cv2;
  zarada+=narudzba[order].zarada;
  narudzba[order].done=true;
  dirord[narudzba[order].cv1]--;
  preostalo--;
}
bool isporuci(int source){
   int x=nadjinarudzbu(source);
//   printf("narudzba x=%d\n",x);
   while (narudzba[x].cv1==source) {
     if (!narudzba[x].done)
       if (2*MinD[narudzba[x].cv2]<=benzin)
         odnesiivratise(x,narudzba[x].cv1,narudzba[x].cv2,false);
       else if (MinD[narudzba[x].cv2]<=benzin) {
              odnesiivratise(x,narudzba[x].cv1,narudzba[x].cv2,true);
              return false;
            }
            else return false;
     x++;
//     printf("odradjena je narudzba x=%d benzina ima=%d zaradjeno=%d\n",x-1, benzin, zarada);
     krajnje=clock();
     if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>4.8) return false;
   }
   return true;
}
bool isporuciV(int source, int x){
   while (narudzba[x].cv1==source) {
     if (!narudzba[x].done)
       if (2*MinD[narudzba[x].cv2]<=benzin)
         odnesiivratise(x,narudzba[x].cv1,narudzba[x].cv2, false);
       else if (MinD[narudzba[x].cv2]<=benzin) {
              odnesiivratise(x,narudzba[x].cv1,narudzba[x].cv2,true);
              return false;
            }
            else return false;
     x++;
//     printf("odradjena je narudzba x=%d benzina ima=%d zaradjeno=%d\n",x-1, benzin, zarada);
     krajnje=clock();
     if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return false;
   }
   return true;
}
bool isporuciV1(int x){
   if (MinD[narudzba[x].cv2]<=benzin) odnesi(x);
   else return false;
   krajnje=clock();
   if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return false;
   return true;
}
void veliki(){
  DijkstraV(S);
//  printf("prodjoh tuda\n");
  if (dirord[disam])
    if (!isporuci(disam)) return;
  while (preostalo) {
    int x=prvaneodradjenanarudzba();
    if (x==0) return;
    int j=narudzba[x].cv1;
    if (MinD[j]>benzin) return;
    int br=0;
    while (PV[j]) {
      temp[++br]=j;
      j=PV[j];
    }
    temp[++br]=j;
    for (int i=br-1; i>=1; i--) {
      resenje[++brres][0]=0;
      resenje[  brres][1]=temp[i];
    }
    benzin-=MinD[narudzba[x].cv1];
    disam=narudzba[x].cv1;
 
    DijkstraV(narudzba[x].cv1);
//    for (int i=1; i<=6; i++) printf("%d ",MinD[i]);printf("\n");
//    for (int i=1; i<=6; i++) printf("%d ",PV[i]);printf("\n");
 
//   printf("prodjoh tuda disam==%d x=%d\n", disam, x);
    if (!isporuciV(disam, x)) return;
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
void veliki1(){
  disam=S;
  while (preostalo) {
//    printf("Disam==%d\n",disam);
    DijkstraV(disam);
    int x=najblizaneodradjenanarudzbaV();
    if (x==0) return;
    int j=narudzba[x].cv1;
    if (MinD[j]>benzin) return;
    int br=0;
    while (PV[j]) {
      temp[++br]=j;
      j=PV[j];
    }
    temp[++br]=j;
    for (int i=br-1; i>=1; i--) {
      resenje[++brres][0]=0;
      resenje[  brres][1]=temp[i];
    }
    benzin-=MinD[narudzba[x].cv1];
    disam=narudzba[x].cv1;
 
    DijkstraV(narudzba[x].cv1);
 
    if (!isporuciV1(x)) return;
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>vreme) return;
  }
}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("delivery.in", "r", stdin);
    freopen("delivery.out","w", stdout);
#endif
    pocetno=clock();
    scanf("%d %d",&n, &m);
    for (int i=1; i<=m; i++) {
      scanf("%d %d %d",&veza[i].cvor, &veza[i].sused, &veza[i].tezina);
      veza[i+m].cvor=veza[i].sused;
      veza[i+m].sused=veza[i].cvor;
      veza[i+m].tezina=veza[i].tezina;
    }
 
    m*=2;
    sort(veza+1, veza+m+1);
 
    for (int i=1; i<=m; i++) cvor[veza[i].cvor].ls=i;
    for (int i=m; i>=1; i--) cvor[veza[i].cvor].fs=i;
 
    scanf("%d",&k);
    for (int i=1; i<=k; i++) {
      scanf("%d %d %d %d",&narudzba[i].cv1, &narudzba[i].cv2, &narudzba[i].tez, &narudzba[i].zarada);
      narudzba[i].ind=i;
      narudzba[i].done=false;
      ord[narudzba[i].cv1*1000000+narudzba[i].cv2]=i;
    }
    scanf("%d %d %d",&S, &D, &W);
    int y=0;
    if (n<=1000) {
      sort(narudzba+1, narudzba+k+1, myfunc1);
      vreme=1.0;
      mali();  //trazi prvi neodradjeni
      check();
      vreme=2.0;
      mali1(); //trazi najblizeg odakle pocinje
      check();
      vreme=3.0;
      mali2(); //trazi najblizeg u koji se isporucuje
      check();
      reset();
      sort(narudzba+1, narudzba+k+1, myfunc1);
      vreme=4.8;
      veliki1();
      check();
    }
    else if (n-1==m/2 and n<=10000) {
           sort(narudzba+1, narudzba+k+1, myfunc1);
           vreme=2.4;
           stablo();
           check();
           reset();
           sort(narudzba+1, narudzba+k+1, myfunc1);
           vreme=4.8;
           veliki1();
           check();
         }
         else {
           reset();
           sort(narudzba+1, narudzba+k+1, myfunc3);
           vreme=2.5;
           veliki();
           check();
 
           reset();
           sort(narudzba+1, narudzba+k+1, myfunc1);
           vreme=4.9;
           veliki1();
           check();
         }
    ispisrezultata(0);
 
    return 0;
}