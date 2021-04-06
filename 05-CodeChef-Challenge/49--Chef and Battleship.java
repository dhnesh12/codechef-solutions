import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.Scanner;

class L
{
    static final String arrange =
            "##...##.#.\n" +
            "..........\n" +
            "#.###.....\n" +
            "#.........\n" +
            "#...####..\n" +
            "..........\n" +
            "..#.##....\n" +
            "..........\n" +
            "..#..#....\n" +
            "..........\n";
    static BufferedReader io = new BufferedReader(new InputStreamReader(System.in));
    static Random rn = new Random();

    public static void main(String[] args) throws Exception {
        int i;
        System.out.println(1);
        System.out.print(arrange);

        boolean over = false;
        do {
            System.out.println("5 6");
            switch (Integer.parseInt(io.readLine()))
            {
                case 1:     // missed
                    for(i = Integer.parseInt(io.readLine()); i > 0; --i)
                        io.readLine();
                    break;
                case 2:     // hit but not sunk
                    break;
                case 3:     // hit and sunk
                    break;
                case 4:     // I win
                    over = true;
                    break;
                case 5:     // I lose
                    for(i = Integer.parseInt(io.readLine()); i > 0; --i)
                        io.readLine();
                    over = true;
                    break;
            }
        } while(!over);
        System.out.println(0);
    }
}
