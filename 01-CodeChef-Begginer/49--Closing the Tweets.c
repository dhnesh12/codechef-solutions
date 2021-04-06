#include <stdio.h>
#include <string.h>

int main(){
	int twt, nc, i, i2;
	scanf("%d%d",&twt,&nc);
	int click[twt], nr, cnt = 0;
	char line[8];

	for(i = 0; i < twt; i++){
		click[i] = 0;
	}

	for(i = 0; i < nc; i++){
		scanf("%s",line);
		if(!(strcmp("CLOSEALL",line))){
			for(i2 = 0; i2 < twt; i2++){
				click[i2] = 0;
			}
			cnt = 0;
		}
		else if(!(strcmp("CLICK",line))){
			scanf("%d",&nr);
			if(click[nr - 1] == 1){
				cnt--;
				click[nr - 1] = 0;
			}
			else{
				cnt++;
				click[nr - 1] = 1;
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}