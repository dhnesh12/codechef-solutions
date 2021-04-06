using System;
using System.Linq;
using System.Collections.Generic;

public class Test
{
	public static void Main(string[] args)
	{
	    CubicalVirus.solution();
	}
}

class CubicalVirus
    {
        public static void solution()
        {
            int n = Int32.Parse(Console.ReadLine());
            bool[][][] checkVirus = new bool[n][][];
            List<int> xp = new List<int>();
            List<int> yp = new List<int>();
            List<int> zp = new List<int>();
            List<int> costx = new List<int>();
            List<int> costy = new List<int>();
            List<int> costz = new List<int>();

            for(int i=0;i<n;i++)
            {
                checkVirus[i] = new bool[n][];
                for (int j=0;j<n;j++)
                {
                    checkVirus[i][j] = new bool[n];
                }
            }
            for(int k=0;k<n; k++)
            {
                for(int j=0;j<n;j++)
                {
                    string ip = Console.ReadLine();
                    for(int i=0;i<n;i++)
                    {
                        checkVirus[i][j][k] = ip[i] == '1';
                    }
                }
            }
            for(int i=0;i<n;i++)
            {
                xp.Add(i);
                yp.Add(i);
                zp.Add(i);
            }
            for(int i=0;i<n;i++)
            {
                costx.Add(findcost(i, n, null, null, null, checkVirus, true, false));
            }
            var sortx = costx.Select((x, i) => new KeyValuePair<int, int>(x, i)).OrderBy(x => x.Key).ToList();
            var newXindex = sortx.Select(x => x.Value).ToList();
            for(int i=0;i<n;i++)
            {
                costy.Add(findcost(i, n, newXindex, null, null, checkVirus, false, true));
            }
            var sorty = costy.Select((y, i) => new KeyValuePair<int, int>(y, i)).OrderBy(y => y.Key).ToList();
            var newYindex = sorty.Select(x => x.Value).ToList();
            for(int i=0;i<n;i++)
            {
                costz.Add(findcost(i, n, newXindex, newYindex, null, checkVirus, false, false));
            }
            var sortz = costz.Select((z, i) => new KeyValuePair<int, int>(z, i)).OrderBy(z => z.Key).ToList();
            var newZindex = sortz.Select(x => x.Value).ToList();
            costx = new List<int>();
            for(int i=0;i<n;i++)
            {
                costx.Add(findcost(i, n, null, null, newZindex, checkVirus, true, false));
            }
            sortx = costx.Select((x, i) => new KeyValuePair<int, int>(x, i)).OrderBy(x => x.Key).ToList();
            Console.WriteLine(string.Join(" ", sortx.Select(x => x.Value + 1)));
            Console.WriteLine(string.Join(" ", sorty.Select(x => x.Value + 1)));
            Console.WriteLine(string.Join(" ", sortz.Select(x => x.Value + 1)));
        }

        static int findcost(
            int id,
            int n,
            List<int> newXindex,
            List<int> newYindex,
            List<int> newZindex,
            bool[][][] cubicalbox,
            bool checkx,
            bool checky)
            {
                int ans = 0;
                for(int i=0;i<n;i++)
                {
                    for(int j=0;j<n;j++)
                    {
                        if(checky)
                        {
                            if(newXindex != null)
                            {
                                if((ans<(n-i)*(n-j)) && cubicalbox[newXindex[i]][id][j])
                                {
                                    ans = (n-i)*(n-j);
                                }
                            }
                            else
                            {
                                if((ans<(n-i)*(n-j)) && cubicalbox[i][id][j])
                                {
                                    ans = (n-i)*(n-j);
                                }
                            }
                        }
                        else if(checkx && !checky)
                        {
                            if(newZindex != null && newYindex != null)
                            {
                                if((ans<(n-i)*(n-j)) && cubicalbox[id][newYindex[i]][newZindex[j]])
                                {
                                    ans = (n-i)*(n-j);
                                }
                            }
                            else
                            {
                                if((ans<(n-i)*(n-j)) && cubicalbox[id][i][j])
                                {
                                    ans = (n-i)*(n-j);
                                }
                            }
                        }
                        else
                        {
                            if(newXindex != null && newYindex != null)
                            {
                                if((ans<(n-i)*(n-j)) && cubicalbox[newXindex[i]][newYindex[j]][id])
                                {
                                    ans = (n-i)*(n-j);
                                }
                            }
                            else if((ans<(n-i)*(n-j)) && cubicalbox[i][j][id])
                            {
                                ans = (n-i)*(n-j);
                            }
                        }
                    }
                }
                return ans;
            }
        }