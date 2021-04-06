import java.io.*;
class Cont{
	int l,w,h,z;
	Cont(int a, int b, int c)
	{
		h = (int)Math.max(a, Math.max(b, c));
		if (h == a)
		{ l = b; w = c; }
		else if (h == b)
		{ l = a; w = c; }
		else if (h == c)
		{ l = a; w = b; }
		z = l * w;
	}
	public boolean comp(int a, int b)
	{
		if (l <= a && w <= b)
			return true;
		else if (l <= b && w <= a)
		{
			l = l + w;
			w = l - w;
			l = l - w;
			return true;
		}
		return false;
	}
	}
	public class Main
	{
		public static void main(String args[])throws Exception
		{
			int n = 0, i = 0, j = 0, k = 0,n1=0;
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			n = Integer.parseInt(br.readLine());
			String s="";
			String sw[]=null;
			while (n > 0)
			{   
				s = br.readLine();
				n1 = Integer.parseInt(br.readLine());
 
				Cont box[] = new Cont[n1];
				for (i = 0; i < n1; i++)
				{
					s = br.readLine();
					sw = s.split(" ");
					box[i] = new Cont(Integer.parseInt(sw[0]), Integer.parseInt(sw[1]), Integer.parseInt(sw[2]));
				}
				Cont temp = null;
				for (i = 1; i < n1; i++)
				{
					temp = box[i];
					j = i - 1;
					while (j > -1 && box[j].z > temp.z)
					{
						box[j + 1] = box[j];
						j--;
					}
					box[j + 1] = temp;
				}
					s = "";
					temp=box[n1-1];
					for (i = n1 - 2; i > -1; i--)
					{if(box[i].comp(temp.l,temp.w))
					{
						s = s + box[i].h + " " + box[i].l + " " + box[i].w + "LC";
						temp = box[i];
					}
 
				     }
					 sw = s.split("LC");
					 System.out.println(sw.length);
					 for (i = sw.length-1; i >-1; i--)
						 System.out.println(sw[i]);
				n--;
 
			}
			
 
 
			}
 
		}