using System;

public class Test
{
	public static void Main()
	{
		// your code goes here
		int t = Convert.ToInt32(Console.ReadLine());

            while (t-- > 0)
            {
                int[] x =new int[6];
                string[] a = Console.ReadLine().Split(' ');
                string[] b = Console.ReadLine().Split(' ');
                string[] c = Console.ReadLine().Split(' ');

                x[0] = Convert.ToInt32(a[0]) + Convert.ToInt32(a[1]) + Convert.ToInt32(a[2]);
                x[1] = Convert.ToInt32(b[0]) + Convert.ToInt32(b[1]) + Convert.ToInt32(b[2]);
                x[2] = Convert.ToInt32(c[0]) + Convert.ToInt32(c[1]) + Convert.ToInt32(c[2]);
                x[3] = Convert.ToInt32(a[0]) + Convert.ToInt32(b[0]) + Convert.ToInt32(c[0]);
                x[4] = Convert.ToInt32(a[1]) + Convert.ToInt32(b[1]) + Convert.ToInt32(c[1]);
                x[5] = Convert.ToInt32(a[2]) + Convert.ToInt32(b[2]) + Convert.ToInt32(c[2]);

                int m = 0;

                if (m < x[0])
                {
                    m = x[0];
                }
                if (m < x[1])
                {
                    m = x[1];
                }
                if (m < x[2])
                {
                    m = x[2];
                }
                if (m < x[3])
                {
                    m = x[3];
                }
                if (m < x[4])
                {
                    m = x[4];
                }
                if (m < x[5])
                {
                    m = x[5];
                }


                if (m == 0)
                {
                    Console.WriteLine(m);
                }
                else if (m % 2 == 0)
                {
                    Console.WriteLine(m - 1);
                }
                else
                {
                    Console.WriteLine(m);
                }
            }
	}
}
