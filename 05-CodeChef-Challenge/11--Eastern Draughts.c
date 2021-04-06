#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#define DEB*/
#define siz 1000001
#define zuruck {rad=0; x=0; y=0; goto beginn;}

typedef struct {
char x1, y1, x2, y2;
} struktur;

main()
{
int N, t, x, y, rad, x1, y1, L=0, anz, R;
double P;
char a[40][40];
struktur bew[siz];

/* Einlesen */
scanf("%d",&N);
for(t=0; t<N; t++)
	scanf("%s",a[t]);

/* P berechnen */
R=0;
for(y=0; y<N; y++)
	for(x=0; x<N; x++)
		if(a[y][x]=='*') R++;
P=-0.5+sqrt(0.25+2.0*(double)R);

/* Ausgabe davor */
#ifdef DEB
for(t=0; t<N; t++)
	puts(a[t]);
#endif
/* 1. Stufe: Verschiebung nach rechts */
for(y=N-1; y>=0; y--)
	for(x=N-2; x>=0; x--)
		if(a[y][x]=='*' && a[y][x+1]=='.')
			{
			while(a[y][x]=='*' && a[y][x+1]=='.' && x<N-1)
				{
				a[y][x]='.';
				a[y][x+1]='*';

				bew[L].x1=x;
				bew[L].y1=y;
				bew[L].x2=x+1;
				bew[L].y2=y;
				L++;

				x++;
				}
			y=N-1;
			x=N-2;
			}

/* 1. Stufe: Verschiebung nach unten */
for(y=N-2; y>=0; y--)
	for(x=N-1; x>=0; x--)
		if(a[y][x]=='*' && a[y+1][x]=='.')
			{
			while(a[y][x]=='*' && a[y+1][x]=='.' && y<N-1)
				{
				a[y][x]='.';
				a[y+1][x]='*';

				bew[L].x1=x;
				bew[L].y1=y;
						bew[L].x2=x;
				bew[L].y2=y+1;
				L++;

				y++;
				}
			y=N-2;
			x=N-1;
			}

/* Ausgabe dazwischen */
#ifdef DEB
puts("");
for(t=0; t<N; t++)
	puts(a[t]);
#endif

/* 2. Stufe: Rueckverschiebung */

for(rad=0; rad<N; rad++)
	{
beginn:	for(y=0; y<=rad; y++)
		for(x=0; x<=rad; x++)
			if(a[y][x]=='.' && (double)x+(double)y<P)
				{

				/* horizontale Suche */
				for(x1=x+1; x1<N; x1++)
					if(a[y][x1]=='*')
						{
						while(x1>x)
							{
							a[y][x1]='.';
							a[y][--x1]='*';

							bew[L].x1=x1+1;
							bew[L].y1=y;
								bew[L].x2=x1;
							bew[L].y2=y;
							L++;

							}
						zuruck;
						}

				/* vertikale Suche */
				for(y1=y+1; y1<N; y1++)
					if(a[y1][x]=='*')
						{
						while(y1>y)
							{
							a[y1][x]='.';
							a[--y1][x]='*';

							bew[L].x1=x;
							bew[L].y1=y1+1;
							bew[L].x2=x;
							bew[L].y2=y1;
							L++;

							}
						zuruck;
						}

				/* schraege Suche */
				for(y1=y+1; y1<N; y1++)
					for(x1=x+1; x1<N; x1++)
						if(a[y1][x1]=='*')
							{
							while(x1>x)
								{
								a[y1][x1]='.';
								a[y1][--x1]='*';
	bew[L].x1=x1+1;
								bew[L].y1=y1;
								bew[L].x2=x1;
								bew[L].y2=y1;
								L++;

								}
							while(y1>y)
								{
								a[y1][x1]='.';
								a[--y1][x1]='*';

								bew[L].x1=x1;
								bew[L].y1=y1+1;
								bew[L].x2=x1;
								bew[L].y2=y1;
								L++;

								}
							zuruck;
							}
				}
	}			

/* Ausgabe danach */
#ifdef DEB
puts("");
for(t=0; t<N; t++)
	puts(a[t]);
puts("");
#endif

/* Endausgabe */
#ifndef DEB
printf("%d\n",L);
for(t=0; t<L; t++)
	printf("%d %d %d %d\n",bew[t].x1,bew[t].y1,bew[t].x2,bew[t].y2);
#endif

return 0;
}