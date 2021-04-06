 #include <stdio.h>
         
        int main(){
        	int t;
        	scanf("%d", &t);
        	while(t--){
        		int n, a,i;
        		scanf("%d%d",&n,&a);
        		if(a==1){
        			printf("%d ",n);
        			for(i=1;i<=n;i++){
        				printf("a");
        			}
        			
        		}
        		else if(a==2){
        			if(n==1)
        				printf("1 a");
        		else if(n==2)
        				printf("1 ab");
        			else if(n==3)
        				printf("2 aab");
        			else if(n==4)
        				printf("2 aabb");
        			else if(n==5)
        				printf("3 aaabb");
        			else if(n==6)
        				printf("3 aaabab");
        			else	if(n==7)
        				printf("3 aaababb");
        			else	if(n==8)
        				printf("3 aaababbb");			
        			else if(n==9)
        				printf("4 aabbabaab");
        				else if(n==10)
        				printf("4 aabbabaabb");
        			
        			else{
        			char str[]="aabbab";
        			printf("4 ");
        			for(i=1;i<=n/6;i++)
        				printf("aabbab");
        			for(i=0;i<n%6;i++)
        				printf("%c",str[i]);
        		}
        		}
        		
        		else {
        			char str[27]="0";
        			for(i=0;i<a;i++){
        				str[i]=97+i;
        			}
        			printf("1 ");
        			for(i=1;i<=n/a;i++)
        			printf("%s",str);
        			for(i=0;i<n%a;i++)
        			printf("%c",str[i]);
        		}
        		printf("\n");
        	}
        	return 0;
}
        