#include<cstdio>
#include<algorithm>
#include<vector>
#define S 1000007
using namespace std;

///na którym miejscu jest x
int T[S];

///co jest na miejscu x
int T2[S];

///jaki zbior jest w miejscu x
int sp[S];

///przedzialy zbiorow
int l[S];
int r[S];

///Kiedy ostatnio powstał nowy zbiór ze zbioru x
int lastCreate[S];

vector < int > L[S];
bool odw[S];

int kl[S];

int main(void){
    int z;
    scanf("%d",&z);
    while(z--){
        int n,m;
        scanf("%d %d",&n,&m);
        int a,b;
        for(int i =1; i <= m;i++){
            scanf("%d %d",&a,&b);
            L[a].push_back(b);
            L[b].push_back(a);
        }
        int licznik = 1;
        for(int i = 1; i <= n;i++){
            T[i] = i;
            T2[i] = i;
            sp[i] = 1;
        }
        l[1] = 1;
        r[1] = n;
        for(int i = 1; i <= n;i++){
            int x = T2[i];
            odw[x] = 1;
            //printf("%d ",x);
            l[sp[i]] ++;
            for(int j = 0; j < L[x].size();j++){
                int v = L[x][j];
                if(v == x)
                    continue;
                if(odw[v]){
                    kl[x]++;
                    continue;
                }
                int pos = T[v];
                int id = sp[pos],id2;
                if(lastCreate[id] < i){
                    ///tu tworzymy nowy zbior
                    licznik++;
                    id2 = licznik;
                    l[id2] = r[id2] = l[id]-1;
                    l[id2]++;
                    lastCreate[id] = i;
                }else{
                    ///tu juz tworzylismy, to tylko przerzucamy i takie tam
                    id2 = sp[l[id]-1];
                }
                ///mamy teraz id i id2
                r[id2]++;
                l[id]++;
                sp[r[id2]] = id2;
                int v2 = T2[r[id2]];
                int pos2 = T[v2];
                ///mamy elementy v i v2 na pozycjach pos i pos2
                //printf("swapuje sobie %d %d na pozycjach %d %d  %d %d    %d %d %d %d*\n",v,v2,pos,pos2,id,id2,l[id2],r[id2],l[id],r[id]);
                swap(T[v],T[v2]);
                swap(T2[pos],T2[pos2]);

            }
            sp[i] = 0;
            /*for(int j = 1; j <= n;j++){
                printf("%d ",T[j]);
            }
            printf("\n");
            for(int j = 1; j <= n;j++){
                printf("%d ",T2[j]);
            }
            printf("\n");
            for(int j = 1; j <= n;j++){
                printf("%d ",sp[j]);
            }
            printf("\n");
            for(int j = 1; j <= n;j++){
                printf("%d ",l[j]);
            }
            printf("\n");
            for(int j = 1; j <= n;j++){
                printf("%d ",r[j]);
            }
            printf("\n\n");*/
        }



        int odp = 0;
        for(int i = 1; i <= n;i++){
            odp = max(odp,kl[i]);
        }
        for(int i = 1; i <= max(n,licznik);i++){
            L[i].clear();
            kl[i] = 0;
            odw[i] = 0;
            lastCreate[i] = 0;
            T[i] = T2[i] = sp[i] = l[i] = r[i] = 0;
        }
        printf("%d\n",odp+1);

    }
    return 0;
}
/*
1
8 11
1 6
2 8
3 6
3 8
4 7
4 8
5 7
5 8
6 7
6 8
7 8
*/
