
import java.util.*;
import java.lang.*;
import java.io.*;
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
Scanner in=new Scanner(System.in);
int t=in.nextInt();
while(t-->0){
int n=in.nextInt();
int q=in.nextInt();
int arr[]=new int[n];
for(int i=0;i<n;i++){
   arr[i] =in.nextInt();
}
while(q-->0){
int a=in.nextInt();
int b=in.nextInt();
int c=in.nextInt();
int d=in.nextInt();
int count=0;
int al[]=new int [b-a+1];
int ar[]=new int [b-a+1];
System.arraycopy(arr, a-1, al, 0, b-a+1);
System.arraycopy(arr,c-1,ar,0,d-c+1);
Arrays.sort(al);
Arrays.sort(ar);
for(int i=0;i<b-a+1;i++){
	if(al[i]!=ar[i]){
		count++;
		if(count>1){
			System.out.println("NO");
			break;
}}}
if(count<=1)
System.out.println("YES");
count=0;

}

}
in.close();
}
}
