/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
	    String binary_string;
	    int no_operations=0;
	    Scanner obj=new Scanner(System.in);
	    try{
	        binary_string=obj.nextLine();
	        int len= binary_string.length();
	        char[] char_array= new char[len];
	        String compare="";
	        
	        for(int i=0;i<len;i++){
	            char_array[i]=binary_string.charAt(i);
	            compare+='0';
	        }
	        
	        int index=len-1;
	        while(!binary_string.equals(compare)){
	            
	            String new_string="";
	            for(int i=index;i<len-1;i++){
	                new_string+='0';
	            }
	            if(binary_string.charAt(index)=='1'){
	                no_operations+=1;
	                for(int i=index;i>=0;i--){
	                    if(binary_string.charAt(i)=='1'){
	                        new_string='0'+new_string;
	                    }
	                    else{
	                        new_string='1'+new_string;
	                    }
	                }
	                binary_string=new_string;
	            }
	            else{
	                while(binary_string.charAt(index)!='1'){
	                    index--;
	                }
	            }
	            
	        }
	        System.out.print(no_operations);
	        
	    }
	    catch(Exception e){
	        return;
	    }
		// your code goes here
	}
}
