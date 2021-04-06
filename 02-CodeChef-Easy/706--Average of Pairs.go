package main
import ("fmt"
//"sort"
)

func main(){
	// your code goes here

	var t int
	fmt.Scanln(&t)
	for i:=0;i<t;i++ {
	    var n int
	    fmt.Scanln(&n)
	    a:=make([]int,n)
	   for i,_ := range a {
	       // var s int
	        fmt.Scanf("%d",&a[i])
	        //a.Append(s)
	    }
	    c:=0
	    for i:=0;i<n-1; i++ {
	        for j:=i+1;j<n;j++ {
	            b:=a[i]+a[j]
	            //d:=b/2
	           // fmt.Println(sort.SearchInts(a,d))
	          /*  if sort.SearchInts(a,d) < n && b%2==0 {
	                c++
	          //  fmt.Print(i,j)
	                
	            }*/
	            for k:=0;k<n;k++ {
	                if b==2*a[k] {
	                    c+=1
	                    break
	                }
	            }
	            
	        }
	    }
	    fmt.Println(c)
	}
}
