
import java.util.*;
import java.lang.*;

class CodeChef {

    static Scanner scan = new Scanner(System.in);

    static class Segment {
        int beg, end;

        Segment(int beg, int end) {
            this.beg = beg;
            this.end = end;
        }
    }

    public static void main (String[] args) {
        int n = scan.nextInt(), m = scan.nextInt();
        int[] arr = new int[n];
        int segId = 0;
        List<Segment> segments = new ArrayList<>();
        int[] segmentOf = new int[n];
        int beg = 0;
        for(int i=0;i<n;i++) {
            arr[i] = scan.nextInt();
            if(i > 0 && arr[i-1] != arr[i]) {
                segId++;
                segments.add(new Segment(beg, i-1));
                beg = i;
            }
            segmentOf[i] = segId;
        }
        segments.add(new Segment(beg, n-1));

        while(m-- > 0) {
            int l = scan.nextInt() - 1, r = scan.nextInt() - 1, k = scan.nextInt();
            int mid = (r+l) / 2;
            int midSegmentId = segmentOf[mid];
            Segment midSegment = segments.get(midSegmentId);
            int length = Math.min(r, midSegment.end) - Math.max(l, midSegment.beg) + 1;
            if(length >= k) {
                System.out.println(arr[mid]);
            } else {
                System.out.println(-1);
            }

        }
    }

}