import java.io.*;
import java.util.*;
class anteater {
    public static void main(String[] args)throws IOException {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        for(int z=1;z<=t;z++){
            int n=sc.nextInt();
            int m=sc.nextInt();
            char ch[][]=new char[n][m];
            int count[][][]=new int[n][m][51];
            for(int i=0;i<n;i++){
                String s=sc.next();
                for(int j=0;j<m;j++){
                    ch[i][j]=s.charAt(j);
                }
            }

            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(ch[i][j]=='R'){
                        update(count,0,1,n,m,i,j,ch);
                    }
                    else if(ch[i][j]=='L'){
                        update(count,0,-1,n,m,i,j,ch);
                    }
                    else if(ch[i][j]=='U'){
                        update(count,-1,0,n,m,i,j,ch);
                    }
                    else if(ch[i][j]=='D') {
                        update(count,1,0,n,m,i,j,ch);
                    }
                }
            }
            int pairs=0;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(ch[i][j]!='#')
                    {
                    //System.out.println(i+" "+j);
                        for(int k=0;k<=50;k++){
                            //System.out.print(count[i][j][k]+" ");
                            int tt=count[i][j][k];
                            pairs+=((tt*(tt-1))/2);
                        }
                        //System.out.println();
                    
                    }
                }
            }
            System.out.println(pairs);
        }
    }
    static void update(int a[][][],int r,int c,int n,int m,int i,int j,char ch[][]){
        int cc=0;
        while(i<n && j<m && i>=0 && j>=0){
            if(ch[i][j]=='#'){
                break;
            }
            a[i][j][cc]++;
            i+=r;
            j+=c;
            cc++;
        }
    }    
}
