#include <cstdio>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
using namespace std;
int values[26]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
int brojrecizaproveruvelikog=1;
int brojrecizaproverumalog=1;
struct slogcvora
{
    int fs,ls,mul;
    char slovo;
} cvor[100005];
clock_t pocetno, krajnje;
int n,m,t,L,pos,idx[100005],global,putanja[25],DOMET,sss,timeinterval;
char cs[300];
bool moze,fajront;
string s,slong;
int izlaznarec;
map <string, int> maps;
map <char, int> mplocice;
char nplocice[100];
struct slogveze
{
    int cvor, sused;
    bool operator < (const slogveze &a) const {
      return (cvor<a.cvor) or (cvor==a.cvor and sused<a.sused);}
} veza[200005];
struct slogrecnika
{
  string rec, sortirana;
  int vrednost;
  bool used;
} recnik[270000];
typedef struct Node
{
   bool End;
   int ID;
   Node * children[26];
   Node(void)
   {
    End=false;
    for (int i=0; i<26; i++)
    children[i] = NULL;
   }
};
Node root;
void Add(char s[], int x)
{
  int len = strlen(s);
  Node *cur = &root;
  for (int i=0; i<len; i++)
  {
    if (cur -> children[s[i]-'A'] == NULL)
    cur -> children[s[i]-'A'] = new Node();
    cur = cur -> children[s[i]-'A'];
  }
  cur -> End = true;
  cur -> ID = x;
}
bool Check(string s)
{
  Node *cur = &root;
  int len=s.size();
  for (int i=0; i<len; i++)
  {
    if (cur -> children[s[i]-'A'] == NULL)
    return false;
    cur = cur -> children[s[i]-'A'];
  }
  if (cur -> End == true)
  return true;
  else
  return false;
}
int CheckPrefix(string s)
{
  Node *cur = &root;
  int len=s.size();
  for (int i=0; i<len; i++)
  {
    if (cur -> children[s[i]-'A'] == NULL)
    return false;
    cur = cur -> children[s[i]-'A'];
  }
  if (cur -> End == true)
  return cur -> ID;
  else
  return t+1;
}
void ispiscvorova()
{
#ifndef ONLINE_JUDGE
  for (int i=1; i<=n; i++)
    cout << cvor[i].fs << " " << cvor[i].ls << " " << cvor[i].mul << " " << cvor[i].slovo << endl;
#endif
}
int bt(string pref)
{
  int pocetak=1;
  int kraj=t;
  int sol=kraj;
  int l=pref.size();
  while (pocetak<=kraj)
  {
    int srednji=(pocetak+kraj)/2;
    if (recnik[srednji].rec.substr(0,l)>=pref)
    {
        sol=srednji;
        kraj=srednji-1;
    }
    else
    {
        pocetak=srednji+1;
    }
  }
  return sol;
}
void unosplocica()
{
  cin >> s;
  sort(s.begin(),s.end()/*,odzdoa*/);
  L=s.size();
  mplocice.clear();
  for (int i=0; i<L; i++)
  mplocice[s[i]]++;
}
void unosplocicaoffline(int koliko)
{
  s.clear();
  for (map<char,int>::iterator it=mplocice.begin(); it!=mplocice.end(); ++it)
  {
    if (it->second < 0)
    while (true);
    for (int i=1; i<=it->second; i++)
    s=s+ it->first;
  }
  while (koliko--)
  s=s+slong[sss++];
  sort(s.begin(),s.end());
  L=s.size();
  mplocice.clear();
  for (int i=0; i<L; i++) mplocice[s[i]]++;       //MCNNPPAAESRORXOTTLRS IALANSRAOOGTT_OOORAMITTO
}                                                 //LRMTCAIITSNLNPPVAAEI SRORXOTTLRSIALANSRAOOGTT_OOORAMITTO
bool podniz(int x, string pref){
  string a=recnik[x].sortirana;
  int l=a.size();
  int p=0;
  for (int i=0; i<l; i++,p++){
    while (a[i]!=s[p]) {
      p++;
      if (p>=L) return false;
    }
  }
  return true;
}
bool podnizpref(int x, string pref){
  string a=recnik[x].rec.substr(pref.size());
  if (!a.size()) return false;
  sort(a.begin(),a.end());
  int l=a.size();
  int p=0;
  for (int i=0; i<l; i++,p++){
    while (a[i]!=s[p]) {
      p++;
      if (p>=L) return false;
    }
  }
  return true;
}
int nadjislobodnureczaveliki(string pref){
  int start;//=100000;
  for (int i=s.size()-1; i>=0; i--) if (s[i]!='_') {pref=s[i]; break;}
  if (pref=="") start=t;
  else start=bt(pref);
  for (int i=start; i>=1; i--)                              //od kraja recnika se trazi rec t je broj reci u recniku
    if (podniz(i,pref) and !recnik[i].used) return i;
  return 0;
}
int nadjislobodnureczamali(string pref){
  int reti=0;
  int maxv=0;
  int cnt=0;
  int start;
  for (int i=s.size()-1; i>=0; i--) if (s[i]!='_') {pref=s[i]; break;}
  if (pref=="") start=t;
  else start=bt(pref);
  for (int i=start; i>=1; i--)                              //od kraja recnika se trazi rec t je broj reci u recniku
    if (podniz(i,pref) and !recnik[i].used)
      if (recnik[i].vrednost>maxv) {
        maxv=recnik[i].vrednost;
        reti=i;
        if (++cnt>brojrecizaproveruvelikog) return reti;
      }
  return reti;
}
void tryputDSF(int x, int dubina, int dokle){
  putanja[dubina]=x;
  if (dubina==dokle) {moze=true; return;}
  idx[x]=global;
  for (int i=cvor[x].fs; i<=cvor[x].ls; i++) {
    if (idx[veza[i].sused]!=global and cvor[veza[i].sused].slovo=='.')
      tryputDSF(veza[i].sused,dubina+1,dokle);
    if (moze) return;
  }
}
bool smestirecbilogde(int x){
  recnik[x].used=true;
  int l=recnik[x].rec.size();
  int i=1;
  while (cvor[i].slovo!='.') i++;
  for (; i<=n; i++) {
    if (cvor[i].slovo!='.') continue;
    moze=false;
    global++;
    tryputDSF(i,1,l);
    if (moze) break;
  }

  if (!moze) return false;

  printf("%d\n",l);
  int a=0;
  for (int j=1; j<=l; j++) a+=cvor[putanja[j]].mul*values[recnik[x].rec[j-1]-65];
  int b=0;
  for (int j=1; j<=l; j++) b+=cvor[putanja[l-j+1]].mul*values[recnik[x].rec[j-1]-65];
//  cout << a << " " << b << endl;
  if (a>b) { // originalna rec ide u resenje
    for (int j=1; j<=l; j++) {
      if (s[L-1]=='_') {
        if (j==1) printf("%d %c\n",putanja[j],'_');
        else printf("%d %c\n",putanja[j],recnik[x].rec[j-1]);
        if (j==1) cvor[putanja[j]].slovo='_';
        else cvor[putanja[j]].slovo=recnik[x].rec[j-1];
      }
      else {
        printf("%d %c\n",putanja[j],recnik[x].rec[j-1]);
        cvor[putanja[j]].slovo=recnik[x].rec[j-1];
      }
      //if (cvor[putanja[j]].slovo!='.') while (true);
    }
    printf("%d\n",l);
    for (int j=1; j<=l; j++) printf("%d ",putanja[j]);
  }
  else {
    for (int j=1; j<=l; j++) {
      printf("%d %c\n",putanja[l-j+1],recnik[x].rec[j-1]);
      //if (cvor[putanja[j]].slovo!='.') while (true);
      cvor[putanja[l-j+1]].slovo=recnik[x].rec[j-1];
    }
    printf("%d\n",l);
    for (int j=1; j<=l; j++) printf("%d ",putanja[l-j+1]);
  }
  cout << endl << recnik[x].rec << endl;
  fflush(stdout);

  for (int i=0; i<recnik[x].rec.size(); i++) mplocice[recnik[x].rec[i]]--;
  unosplocica();
  DOMET+=l;
  return true;
}
bool josjednaprovera(int x, int levo){
  int l=recnik[x].rec.size()-levo;
  if (DOMET+l>n) return false;
  for (int j=1; j<=l; j++) {
    if (cvor[DOMET+j].slovo=='.') ;
    else return false;
  }
  return true;
}
bool smestirec(int x, int levo){
//  if (recnik[x].used) cout << 1/(n-n);
//    else
  recnik[x].used=true;
  int l=recnik[x].rec.size()-levo;
  if (DOMET+l>n) return false;
  printf("%d\n",l);
//  if (l<1) cout << 1/(n-n);
  for (int j=1; j<=l; j++) {
    if (cvor[DOMET+j].slovo=='.')
      printf("%d %c\n",DOMET+j,recnik[x].rec[levo+j-1]);
    else cout << 1/(n-n);
    //if (cvor[putanja[j]].slovo!='.') while (true);
    cvor[DOMET+j].slovo=recnik[x].rec[levo+j-1];
    if (!mplocice[cvor[DOMET+j].slovo]) cout << 1/(n-n);
    else mplocice[cvor[DOMET+j].slovo]--;
  }
  printf("%d\n",recnik[x].rec.size());
  for (int j=DOMET-levo+1; j<=DOMET+l; j++) printf("%d ",j);
  cout << endl << recnik[x].rec << endl;
  int rr=0;
  for (int j=DOMET-levo+1; j<=DOMET+l; j++) {
    if (cvor[j].slovo!=recnik[x].rec[rr++])
       cout << 1/(n-n);
    if (j<1 or j>n) cout << 1/(n-n);
  }
  DOMET=DOMET+l;
  fflush(stdout);
#ifdef ONLINE_JUDGE
  unosplocica();
#endif
#ifndef ONLINE_JUDGE
  unosplocicaoffline(l);
#endif
  return true;
}
void maliprazan(){
#ifndef ONLINE_JUDGE
   cin >> slong;
   unosplocicaoffline(20);
#endif
#ifdef ONLINE_JUDGE
  unosplocica();
#endif
  izlaznarec=nadjislobodnureczamali("");
  smestirecbilogde(izlaznarec);
  DOMET=recnik[izlaznarec].rec.size();

  while (DOMET<n){
     int odakle;
     int pp;
     global++;
     bool uspesno=false;
     string prefix;
     if (DOMET<10) odakle=1; else odakle=DOMET-9;
     for (int i=odakle; i<=DOMET; i++) prefix.push_back(cvor[i].slovo);
//            printf("Prodjoh tuda BT Adresa==%d DOMET==%d prefix==",pp,DOMET); cout << prefix << " plocice== " << s <<endl;
     bool nemaplocicauprefixu=true;
     for (int i=0; i<prefix.size(); i++) if (prefix[i]=='_') nemaplocicauprefixu=false;
     while (prefix.size() and !uspesno and nemaplocicauprefixu) {
       int ps=prefix.size();
       if (CheckPrefix(prefix)) {
          pp=bt(prefix); // pronalazim prvu rec sa ovim prefiksom
          while (recnik[pp].rec.substr(0,ps)==prefix and !uspesno) {//proveravam sve reci s ovim prefiksom
            if (!recnik[pp].used)
              if (podnizpref(pp,prefix) and DOMET-ps+recnik[pp].rec.size()<=n) {uspesno=true; break;}
            pp++;
//            printf("Prodjoh tuda BT Adresa==%d DOMET==%d prefix==",pp,DOMET); cout << prefix << " plocice== " << s <<endl;
          }
       }
       if (uspesno) break;
       prefix=prefix.substr(1);
//       printf("Skracen prefix sada je== "); cout << prefix << endl;
     }
     if (uspesno and (global%18!=0) ) {
         if (!smestirec(pp,prefix.size())) return;
         else ;
     }
     else {
       izlaznarec=nadjislobodnureczamali("");
       if (izlaznarec) {
         if (!smestirecbilogde(izlaznarec)) return;
         else ;
       }
       else return;
     }
     krajnje=clock();
     if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>timeinterval) return;

  }
}
void mali(){
  unosplocica();
  while (true){
    izlaznarec=nadjislobodnureczamali("");
    if (izlaznarec) {
      if (!smestirecbilogde(izlaznarec)) return;
//      else return;// iskljuceno zbog testa malog praznog
    }
    else return;
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>timeinterval) return;
  }
}
void veliki(){
  unosplocica();
  while (true) {
    izlaznarec=nadjislobodnureczamali("");
    if (izlaznarec) {
      if (!smestirecbilogde(izlaznarec)) return;
//      else return;// iskljuceno zbog testa malih
    }
    else return;
    krajnje=clock();
    if ((float)(krajnje-pocetno)/CLOCKS_PER_SEC>timeinterval) return;
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("dictionary.in", "r", stdin);
  freopen("dule.out", "w", stdout);
#endif
  pocetno=clock();
  scanf("%d",&t);
  for (int i=1; i<=t; i++) { // unos recnika
     scanf("%s",&cs);
     Add(cs,i);
     recnik[i].rec=cs;
     recnik[i].sortirana=cs;
     sort(recnik[i].sortirana.begin(),recnik[i].sortirana.end());
     int l=recnik[i].rec.size();
     recnik[i].vrednost=0;
     for (int j=0; j<l; j++) recnik[i].vrednost+=values[cs[j]-65];
//     cout << recnik[i].sortirana << " " << recnik[i].vrednost<<endl;
  }
//  return 0;
#ifndef ONLINE_JUDGE
  freopen("test.in", "r", stdin);
#endif
  pocetno=clock();
  timeinterval = 9;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) scanf("%d", &cvor[i].mul);
  cin >> s;
  int l=s.size();
  int type=0;
  for (int i=0; i<l; i++) {cvor[i+1].slovo=s[i]; type+=(s[i]=='.');}
  for (int i=1; i<=m; i++) {
      scanf("%d %d", &veza[i].cvor, &veza[i].sused);
      veza[i+m].cvor=veza[i].sused;
      veza[i+m].sused=veza[i].cvor;
  }
  m*=2;
  sort(veza+1, veza+m+1);
  for (int i=1; i<=m; i++) cvor[veza[i].cvor].ls=i;
  for (int i=m; i>=1; i--) cvor[veza[i].cvor].fs=i;

  if (n<=10000)
    if (type==n) maliprazan();
//    else maliimaplocica();
    else mali();
  else veliki();
  cout << -1 << endl;
 // int sol=0;
  //if (n>=8000) for (int i=n; cvor[i].slovo=='.'; i--) sol++;
//  if (sol>=4000) cout << 1/(n-n);
  //  ispiscvorova();
  return 0;
}