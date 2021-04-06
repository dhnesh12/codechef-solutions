
#include<stdio.h>
#include<math.h>
unsigned long long int max(unsigned long long int x,unsigned long long int y){
	if(x>y)
		  return x;
	return y;
}
unsigned long long int getnoofdigits(unsigned long long int x){
    int i=0;
    while(x!=0){
    	x=x/10;
    	i++;
    }
   return i;
}
void setarray(unsigned long long int x,unsigned long long int finallength,int a[finallength]){
    int i;
    unsigned long long int tempo=x;
      
	for(i=0;i<finallength;i++){
       a[i]=tempo%10;
       tempo=tempo/10;
	}
}
void sort(unsigned long long int finallength,int a[finallength]){
	int count[10],x,j=0;
	int output[finallength];
	int i=0;
	for(i=0;i<10;i++)
		  count[i]=0;
    for(i=0;i<finallength;i++)
		  count[a[i]]++;
    for (i = 1;i<=9;i++) 
        count[i] += count[i - 1]; 
    for (i = 0; i<finallength; ++i) {
       if(count[a[i]]>0){ 
        output[count[a[i]] - 1] = a[i]; 
        --count[a[i]]; 
        }
    } 
  
    for (i = 0;i<finallength; ++i) 
        a[i] = output[i];
}
void print(int finallength,unsigned long long int a[finallength]){
	 int i=0;
	 for(i=0;i<finallength;i++){
	 	printf("%d\n",a[i]);
	 }
	 printf("\n");
}
unsigned long long int minsum(unsigned long long int x,unsigned long long int y,unsigned long long int finallength){
	unsigned long long int dx,dy,i,co=0;
          int temp;
	//dx=getnoofdigits(x);  
	//dy=getnoofdigits(y);
    //finallength=max(dx,dy);
// printf("final len %lld\n",finallength);
    int ax[finallength],ay[finallength];
    setarray(x,finallength,ax);
    setarray(y,finallength,ay);
   //print(finallength,ax);
   // print(finallength,ay);
    sort(finallength,ax);
    sort(finallength,ay);
 //  print(finallength,ax);
   //print(finallength,ay);
    for(i=0;i<finallength;i++){
        temp=ax[i]-ay[i];
       
        if(temp<0){
        //  printf("tempo1 : %d\n",temp); 
           temp=(-1)*temp;
           // printf("tempo2 : %d\n",temp); 
         }
      
       co+=temp;
    }
   return co;
}
int main(int argc, char const *argv[])
{   // printf("wel\n ");
    int t;
     unsigned long long int x,y,m,n,sum=0,f;
     scanf("%d",&t);
//  unsigned long long int a[t];
      int i=0;  
    for(i=0;i<t;i++){  
        scanf("%llu %llu",&x,&y);
        f=getnoofdigits(y);
     for(m=x;m<=y;m++){
     for(n=m;n<=y;n++){
     sum+=minsum(m,n,f);
   }
 }
   // a[i]=sum;
   sum = (sum*2)%1000000007;
    printf("%llu\n",sum);
      sum=0;  
	//printf("%d\n",minsum(3178,10920));
   }
    // print(t,a);
	return 0;
}