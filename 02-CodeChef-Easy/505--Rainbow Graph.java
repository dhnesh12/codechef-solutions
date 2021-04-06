import java.util.Scanner;
import java.util.HashSet;

class Rainbow {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner console = new Scanner(System.in);
		int tests = console.nextInt();
		for(int t = 0; t < tests; t++) {
			int nodes = console.nextInt();
			int[][] matrix = new int[nodes][nodes];
			for(int i = 0; i < nodes; i++) {
				for(int j = 0; j < nodes; j++) {
					matrix[i][j] = console.nextInt();
				}
			}
			
			int problemsFound = -1;
			do {
				
				problemsFound = -1;
				for(int i = 0; i < nodes; i++) {
					int colorOne = -1;
					for(int j = 0; j < nodes; j++) {
						if(matrix[i][j] != 0) {
							colorOne = matrix[i][j];
						}
					}
					if(colorOne == -1) {
						continue;
					}
					boolean bad = true;
					for(int j = 0; j < nodes; j++) {
						if(matrix[i][j] != 0 && matrix[i][j] != colorOne) {
							bad = false;
							break;
						}
					}
					if(bad) {
						problemsFound = i;
						break;
					}
				}
				
				for(int i = 0; i < nodes; i++) {
					for(int j = 0; j < nodes; j++) {
						if(i == problemsFound || j == problemsFound) {
							matrix[i][j] = 0;
						}
					}
				}
				
			} while(problemsFound >= 0);
			
			int count = 0;
			for(int i = 0; i < nodes; i++) {
				for(int j = 0; j < nodes; j++) {
					if(matrix[i][j] != 0) {
						count++;
						break;
					}
				}
			}
			
			System.out.println(count);
		}
	}

}
