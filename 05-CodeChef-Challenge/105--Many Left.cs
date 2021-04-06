using System;

public class Test
{
	static void Main()
        {
            var size = 0;
            var map = "";

            if (false)
            {
                size = 6;
                map = "..*..**..*.****.**.***..****..**.*.*";
            }
            else
            {
                size = int.Parse(Console.ReadLine());

                for (var i = 0; i < size; i++)
                {
                    var line = Console.ReadLine();
                    map = map + line;
                }
            }
           
            var currentPegs = 0;
            for (int i=0;i<map.Length;i++)
            {
                if (map[i] == '*') currentPegs++;
            }

            var ans = solver(map, null, size, currentPegs);
            ans = ans.Replace("\r\n\r\n", "\r\n").Replace("\r\n\r\n", "\r\n").Replace("\r\n\r\n", "\r\n").Replace("\r\n\r\n", "\r\n").Replace("\r\n\r\n", "\r\n");
            ans = ans.TrimEnd("\r\n".ToCharArray());

            var moves = ans.Split("\r".ToCharArray()).Length;

            Console.WriteLine(moves);
            Console.WriteLine(ans);
          //  Console.ReadKey();
        }

        static string solver(string map, string moves, int size, int currentPegs)
        {

            if (currentPegs == 1)
            {
                return "";
            }

            var bestAns = "";
            //find out how many moves
            /*  for (int x = 0; x < size; x++)
              {
                  for (int y = 0; y < size; y++)
                  {*/


            var rand =new Random();

            var index = rand.Next(0, map.Length - 1);

            for (int i = index; i < index + map.Length; i++)
            {
                var cor = i % map.Length;
                var x = cor % size;
                var y = (cor - x) / size;
                //right
                if (value(map, x, y, size) == '*' && value(map, x + 2, y, size) == '.' && value(map, x + 1, y, size) == '*')
                {
                    var newMap = genNewMap(map, size, x, y, x + 2, y, x + 1, y);
                    bestAns = x + " " + y + " " + (x + 2) + " " + y + "\r\n";
                    bestAns += solver(newMap, moves, size, currentPegs - 1);
                    break;
                    //Math.Max(bestAns, solver(newMap, moves, size, currentPegs - 1));
                }

                //left
                if (value(map, x, y, size) == '*' && value(map, x - 2, y, size) == '.' && value(map, x - 1, y, size) == '*')
                {
                    var newMap = genNewMap(map, size, x, y, x - 2, y, x - 1, y);
                    bestAns = x + " " + y + " " + (x - 2) + " " + y + "\r\n";
                    bestAns += solver(newMap, moves, size, currentPegs - 1);                    
                    break;
                }

                //top
                if (value(map, x, y, size) == '*' && value(map, x, y + 2, size) == '.' && value(map, x, y + 1, size) == '*')
                {
                    var newMap = genNewMap(map, size, x, y, x, y + 2, x, y + 1);
                    bestAns += x + " " + y + " " + x + " " + (y + 2) + "\r\n";
                    bestAns += solver(newMap, moves, size, currentPegs - 1);
                    break;
                }

                //bottom
                if (value(map, x, y, size) == '*' && value(map, x, y - 2, size) == '.' && value(map, x, y - 1, size) == '*')
                {
                    var newMap = genNewMap(map, size, x, y, x, y - 2, x, y - 1);
                    bestAns = x + " " + y + " " + (x) + " " + (y - 2) + "\r\n";
                    bestAns += solver(newMap, moves, size, currentPegs - 1);
                    break;
                }

                /*     }
                 }*/
            }
            return bestAns;
        }


        static char value(string map, int x, int y, int size)
        {
            if ((x<0) || (y<0)) return '-';
            if ((x >= size) || (y >= size)) return '-';
            var index = x + y * size;
           // if (index > map.Length-1) return '-';
           // if (index < 0) return '-';
            return map[index];
        }

        static string genNewMap(string map, int size, int x, int y, int toX, int toY, int killX, int killY)
        {
            var newmap = map;
            var index = toX + toY * size;
            newmap = newmap.Remove(index,1).Insert(index,"*");
            index = killX + killY * size;
            newmap = newmap.Remove(index, 1).Insert(index, ".");       
            index = x + y * size;
            newmap = newmap.Remove(index, 1).Insert(index, ".");
            return newmap;
        }

}
