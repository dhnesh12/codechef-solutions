import java.nio.file.Paths;
import java.nio.file.Files;
import java.nio.charset.StandardCharsets;

import java.util.*;
import java.lang.*;
import java.io.*;

import java.util.stream.IntStream;

public class Main
{
	public static void main (String[] args) throws java.lang.Exception { new Main(); }
	BufferedReader r = new BufferedReader (new InputStreamReader (System.in));
	String pathToFile = "main_input.txt";
    String pathToFile_output = "main_output.txt";
    ArrayList<String> lines_data_input;
    Iterator ln;
    PrintWriter pwout, pwout2;
    long startProgramNanoTime, endProgramNanoTime;
	int pti(String s){ return Integer.parseInt(s); }
	String gs(Iterator ln){ return ln.next() + ""; }
	int t_pti(Iterator ln){ return pti(gs(ln)); }
	void pln(String s){ System.out.println(s); }
    
    void getDataInput() throws java.lang.Exception {
        lines_data_input = new ArrayList<String>();
        String s = r.readLine(); while (s != null) { lines_data_input.add(s); s = r.readLine();  } 
        r.close();
    }
    
    void printToTextFileMainInput(String text) throws java.lang.Exception { if(pwout==null)pwout = new PrintWriter( 
        pathToFile, "UTF-8" ); pwout.println( text ); }
    void printToTextFileMainOutput(String text) throws java.lang.Exception { if(pwout2==null)pwout2 = new PrintWriter( 
        pathToFile_output, "UTF-8" ); pwout2.println( text ); }
    void printAllInput(){ ln = lines_data_input.iterator(); while(ln.hasNext())pln(ln.next() + ""); };
    void doThingBeforeCloseProgram(){ if(pwout != null)pwout.close();if(pwout2 != null)pwout2.close(); endProgramNanoTime = System.nanoTime();
                                        //pln("Time Elapsed = " + ((double)(endProgramNanoTime-startProgramNanoTime) / 1000000000) + " second#");
                                    }
	Main() throws java.lang.Exception {
        startProgramNanoTime = System.nanoTime();
		getDataInput();
        //lines_data_input = (ArrayList<String>) Files.readAllLines(Paths.get(pathToFile), StandardCharsets.UTF_8);
        //printAllInput();
		ln = lines_data_input.iterator();

        solve();
        doThingBeforeCloseProgram();
	}
    
    void solve () throws java.lang.Exception {
        int T = t_pti(ln);
        
        for (int t=0; t<T; t++) {
            String temp[] = gs(ln).split(" ");
            int n = pti(temp[0]);
            int m = pti(temp[1]);
            rowInputan = n;
            colInputan = m;

            byte [][] cellsInputan = new byte[n][m];
            for (int i=0; i<n; i++) {
                String line = gs(ln);

                for (int j=0; j<m; j++) {
                    char cell = line.charAt(j);
                    if(cell == MyGrid.BALL)
                        cellsInputan[i][j] = MyGrid.BYTE_BALL;
                    else
                        cellsInputan[i][j] = MyGrid.BYTE_EMPTY;
                }
            }
            
            ArrayList<MyMove> listOfMoveToFinish = findPath(cellsInputan);
            if(listOfMoveToFinish == null) pln("-1");
            else{
                pln(listOfMoveToFinish.size() + "");
                for(MyMove move : listOfMoveToFinish){
                    pln( move.getCoordinates() );
                }
            }
        }
    }
    
    // start function baru
        ArrayList<MyMove> findPath(byte[][] cellsInputan){
            
            Set<MyGrid> HashSetForGridThatHasBeenVisited = new HashSet<MyGrid>();
            Comparator<GridAndListOfMoves> comparatorGridAndListOfMoves = new ComparatorGridAndListOfMoves();
            Queue<GridAndListOfMoves> PrioQue = new PriorityQueue<GridAndListOfMoves>(1, comparatorGridAndListOfMoves);
            
            MyGrid gridStart = new MyGrid(cellsInputan);
            if(gridStart.getJumlahBolaDiGridIni() == ( Main.rowInputan*Main.colInputan) ){return null;}
            PrioQue.add( new GridAndListOfMoves( gridStart, new ArrayList<MyMove>() ) );
            
            while(!PrioQue.isEmpty()){
                GridAndListOfMoves currentGridAndListOfMoves = PrioQue.poll();
                
                MyGrid currentGrid = currentGridAndListOfMoves.getGrid();
                
                ArrayList<MyMove> oldListOfMove = currentGridAndListOfMoves.getListOfMoves();
                
                if(currentGrid.isGoal())return oldListOfMove;
                
                for(MyMove currentSuccessorMove : currentGridAndListOfMoves.getGrid().getAllSuccessorMove()){
                    
                    byte[][] cellsAfterThisSucessorMove = getCloneOfCellsAfterThisSucessorMove( currentGrid, currentSuccessorMove );
                    MyGrid gridAfterThisSuccessorMove = new MyGrid( cellsAfterThisSucessorMove );
                    
                    if(!HashSetForGridThatHasBeenVisited.contains(gridAfterThisSuccessorMove)){
                        HashSetForGridThatHasBeenVisited.add(gridAfterThisSuccessorMove);
                        
                        ArrayList<MyMove> newListOfMove = new ArrayList<MyMove> ( oldListOfMove );
                        newListOfMove.add(currentSuccessorMove);
                        GridAndListOfMoves objBaru = new GridAndListOfMoves( gridAfterThisSuccessorMove, newListOfMove );
                        
                        PrioQue.add(objBaru);
                    }
                }
            }
            return null;
            
        }
    
        boolean isGridEqualsToFinishGrid(MyGrid g){
            return (g.getJumlahBolaDiGridIni() == 1);
        }
    
        byte[][] getCloneOfCellsAfterThisSucessorMove(MyGrid currentGrid, MyMove currentSuccessorMove){
            byte[][] cellBaru = currentGrid.cloneCell();
            int[] attributeMyMove = currentSuccessorMove.getAllAttributes();
            
            int rEC = attributeMyMove[0];
            int cEC = attributeMyMove[1];
            int rB = attributeMyMove[2];
            int cB = attributeMyMove[3];
            
            if(attributeMyMove[4] == 1){ //isFirstType == 1?
                cellBaru[rEC][cEC] = 1;
                cellBaru[rB][cB] = 0;
            }else{
                int rMid = attributeMyMove[5];
                int cMid = attributeMyMove[6];
                
                cellBaru[rEC][cEC] = 1;
                cellBaru[rB][cB] = 0;
                cellBaru[rMid][cMid] = 0;
            }
            return cellBaru;
        }
    // end function baru
    
    // start class baru
        class MyGrid{
            public static final char BALL='*';
            public static final char EMPTY='.';
            public static final byte BYTE_BALL=1;
            public static final byte BYTE_EMPTY=0;
            private final byte[][] cells;
            private int jumlahBolaDiGridIni;
            
            public MyGrid(byte[][] cellsParam){
                this.cells = cellsParam.clone();
                hitungJumlahBolaDiGridIni();
            }
            
            private void hitungJumlahBolaDiGridIni(){
                jumlahBolaDiGridIni = 0; 
                for(int i = 0 ; i < Main.rowInputan; i++){
                    for(int j = 0 ; j < Main.colInputan; j++){
                        jumlahBolaDiGridIni += cells[i][j];
                    }
                }
            }
            
            public boolean isGoal(){return jumlahBolaDiGridIni == 1;}
            
            public int getJumlahBolaDiGridIni(){return this.jumlahBolaDiGridIni;}
            
            public ArrayList<MyMove> getAllSuccessorMove(){
                /*
                    All Empty Cell = Possible To Move
                    
                        Possibilities Of Empty Cell Movement : 
                        a. Empty Cell, Empty Cell -1 Hori
                        b. Empty Cell, Empty Cell +1 Hori
                        c. Empty Cell, Empty Cell -1 Verti
                        d. Empty Cell, Empty Cell +1 Verti
                    
                        e. Empty Cell, Empty Cell -1, Empty Cell -2 Hori
                        f. Empty Cell, Empty Cell +1, Empty Cell +2 Hori
                        g. Empty Cell, Empty Cell -1, Empty Cell -2 Verti
                        h. Empty Cell, Empty Cell +1, Empty Cell +2 Verti
                    
                        check ( a - d ) if the non Empty Cell WithinTheGrid & within the Law FirstTypeOfMove
                        if true , add to successor
                    
                */
                
                ArrayList<MyMove> allSuccessorMove = new ArrayList<MyMove> ();
                MyMove temp;
                for(int i = 0 ; i < Main.rowInputan ; i++){
                    for(int j = 0 ; j < Main.colInputan ; j++){

                        if( cells[i][j] == BYTE_EMPTY ){
                            
                            //first type of moves
                            temp = new MyMove(i,j, i,j-1); if(temp.passedFirstTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i,j+1); if(temp.passedFirstTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i-1,j); if(temp.passedFirstTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i+1,j); if(temp.passedFirstTypeOfMove(cells)) allSuccessorMove.add(temp);
                            
                            //second type of moves (  )
                            temp = new MyMove(i,j, i,j-2); if(temp.passed2ndTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i,j+2); if(temp.passed2ndTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i-2,j); if(temp.passed2ndTypeOfMove(cells)) allSuccessorMove.add(temp);
                            temp = new MyMove(i,j, i+2,j); if(temp.passed2ndTypeOfMove(cells)) allSuccessorMove.add(temp);
                        }
                    }
                }
                
                return allSuccessorMove;
            }
            
            public byte[][] cloneCell(){
                byte[][] temp = new byte[Main.rowInputan][Main.colInputan];
                for(int i = 0 ; i < Main.rowInputan ; i++){
                    System.arraycopy( cells[i], 0, temp[i], 0, Main.colInputan );
                }
                return temp;
            }
            
            
            @Override
            public boolean equals(Object o){
                if(this == o)return true;
                if(o == null || getClass() != o.getClass()) return false;
                MyGrid tempGrid = (MyGrid) o;
                return Arrays.deepEquals(this.cells, tempGrid.cells);
            }
            
            @Override
            public int hashCode(){
                return Arrays.deepHashCode(cells);
            }
            
        }
    
        class MyMove{
            private int rowEmptyCell;
            private int colEmptyCell;
            private int rowBallWhoWillMove;
            private int colBallWhoWillMove;
            
            private int isFirstType;
            
            private int rowMiddle = -1;
            private int colMiddle = -1;
            
            public MyMove(int rowEmptyCell, int colEmptyCell, int rowBallWhoWillMove, int colBallWhoWillMove){
                this.rowEmptyCell = rowEmptyCell;
                this.colEmptyCell = colEmptyCell;
                this.rowBallWhoWillMove = rowBallWhoWillMove;
                this.colBallWhoWillMove = colBallWhoWillMove;
            }
            public String getCoordinates(){ return (rowBallWhoWillMove + 1) + " " + (colBallWhoWillMove + 1) + " " + (rowEmptyCell + 1) + " " + (colEmptyCell + 1); }
            public int[] getAllAttributes(){ return new int[]{ rowEmptyCell, colEmptyCell, rowBallWhoWillMove, colBallWhoWillMove, isFirstType, rowMiddle, colMiddle }; }
            
            public boolean passedFirstTypeOfMove(byte[][] cells){
                isFirstType = 1;
                //cek within the grid
                if(colBallWhoWillMove < 0)return false;
                if(colBallWhoWillMove >= Main.colInputan)return false;
                if(rowBallWhoWillMove < 0)return false;
                if(rowBallWhoWillMove >= Main.rowInputan)return false;
                
                //cek first type condition
                return(cells[rowBallWhoWillMove][colBallWhoWillMove] == MyGrid.BYTE_BALL);
            }
            
            public boolean passed2ndTypeOfMove(byte[][] cells){
                isFirstType = 0;
                //cek within the grid
                //no need to check the emptyCell + 1 / -1 hori / verti , because if +2/-2 hori verti outside grid then it solves the equation of within the grid
                if(colBallWhoWillMove < 0)return false;
                if(colBallWhoWillMove >= Main.colInputan)return false;
                if(rowBallWhoWillMove < 0)return false;
                if(rowBallWhoWillMove >= Main.rowInputan)return false;
                
                //cek second type condition part 1
                if( cells[rowBallWhoWillMove][colBallWhoWillMove] != MyGrid.BYTE_BALL )return false;
                
                if( colBallWhoWillMove < colEmptyCell ){
                    colMiddle = colBallWhoWillMove + 1;
                    rowMiddle = rowEmptyCell;
                }else if( colBallWhoWillMove > colEmptyCell ){
                    colMiddle = colBallWhoWillMove - 1;
                    rowMiddle = rowEmptyCell;
                }else{
                    if( rowBallWhoWillMove < rowEmptyCell ){
                        rowMiddle = rowBallWhoWillMove + 1;
                    }else{
                        rowMiddle = rowBallWhoWillMove - 1;
                    }
                    colMiddle = colEmptyCell;
                }
                //cek second type condition part 2
                return cells[rowMiddle][colMiddle] == MyGrid.BYTE_BALL;
            }
        }
    
        class GridAndListOfMoves{
            private MyGrid currentGrid;
            private ArrayList<MyMove> listOfMovesToAchieveThisGrid;
            
            public GridAndListOfMoves(MyGrid currentGrid, ArrayList<MyMove> listMove){
                this.currentGrid = currentGrid;
                this.listOfMovesToAchieveThisGrid = listMove;
            }
            
            public MyGrid getGrid(){
                return currentGrid;
            }
            
            public ArrayList<MyMove> getListOfMoves(){
                return listOfMovesToAchieveThisGrid;
            }
        }
    
        class ComparatorGridAndListOfMoves implements Comparator<GridAndListOfMoves>{
            @Override
            public int compare(GridAndListOfMoves o1, GridAndListOfMoves o2){
                return o1.getGrid().getJumlahBolaDiGridIni() - o2.getGrid().getJumlahBolaDiGridIni();
            }
        }
    // end class baru
    
    // start attribute baru
        public static int rowInputan;
        public static int colInputan;
    // end attribute baru
}