import java.util.*;
import java.io.*;

public class Main {

    static void addTo(BitSet base, BitSet addend) {
	int accum = 0;
	int baseLen = base.length();
	int addendLen = addend.length();
	for(int i=0;i<baseLen || i<addendLen || accum != 0;i++) {
	    accum += (base.get(i)?1:0) + (addend.get(i)?1:0);
	    base.set(i, (accum & 1) != 0);
	    accum >>= 1;
	}
    }

    static void increment(BitSet base) {
	int i=0;
	while (base.get(i)) {
	    base.clear(i);
	    i++;
	}
	base.set(i);
    }

    static int compareBitSets(BitSet a, BitSet b) {
	int alen = a.length();
	int blen = b.length();
	if (alen > blen) {
	    return 1;
	}
	else if (alen < blen) {
	    return -1;
	}
	else {
	    for(int i=alen-1;i>=0;i--) {
		boolean abit = a.get(i);
		boolean bbit = b.get(i);
		if (abit && ! bbit) {
		    return 1;
		}
		else if (bbit && ! abit) {
		    return -1;
		}
	    }
	    return 0;
	}
    }
    
    static void sortBitSets(List<BitSet> L) {
	// biggest first
	Collections.sort(L, new Comparator<BitSet>() {
		public int compare(BitSet a, BitSet b) {
		    // -1 means a is bigger
		    return - compareBitSets(a, b);
		}
	    });
    }

    static int enforceMinimumCard(BitSet b, int card, int minCard) {
	int i=0;
	while (card < minCard) {
	    if (! b.get(i)) {
		b.set(i);
		card++;
	    }
	    i++;
	}
	return card;
    }

    static boolean canDistributeOnes(BitSet ones, int numOnes, List<BitSet> L, int listIndex) {
	if (listIndex >= L.size()) {
	    return true;
	}
	
	BitSet b = L.get(listIndex);
	if (b.length() == 0) {
	    return canDistributeOnes(ones, numOnes, L, listIndex+1);
	}
	else if (numOnes < L.size() - listIndex) {
	    return false;
	}
	else if (ones.length() < b.length()) {
	    return false;
	}
	for(int i=ones.length()-1; i>=b.length(); i--) {
	    if (ones.get(i)) {
		ones.clear(i);
		numOnes--;
		boolean result = canDistributeOnes(ones, numOnes, L, listIndex+1);
		numOnes++;
		ones.set(i);
		if (result) {
		    return true;
		}
	    }
	}
	if (! ones.get(b.length()-1)) {
	    return false;
	}
	else {
	    int j = b.length()-1;
	    ones.clear(j);
	    numOnes--;
	    b.clear(j);
	    boolean result = canDistributeOnes(ones, numOnes, L, listIndex);
	    b.set(j);
	    numOnes++;
	    ones.set(j);
	    return result;
	}
    }

    static int incrementWithMinCardinality(BitSet b, int card, int minCard) {
	int i=0;
	while (b.get(i)) {
	    b.clear(i);
	    card--;
	    i++;
	}
	b.set(i);
	card++;
	
	card = enforceMinimumCard(b, card, minCard);
	
	return card;
    }

    static BitSet bitSetSum(Collection<BitSet> sets) {
	BitSet sum = new BitSet();
	
	for(BitSet b : sets) {
	    addTo(sum, b);
	}
	return sum;
    }
    
    static BitSet bind(Collection<BitSet> sets) {
	List<BitSet> L = new ArrayList<BitSet>(sets);
	sortBitSets(L);

	BitSet sum = bitSetSum(L);
	int card = sum.cardinality();
	card = enforceMinimumCard(sum, card, L.size());

	BitSet lowerBound = new BitSet();
	for(BitSet b : L) {
	    int i = b.length()-1;
	    while (lowerBound.get(i)) i++;
	    lowerBound.set(i);
	}
	if (compareBitSets(lowerBound, sum) > 0) {
	    sum = lowerBound;
	}
	
	for(;;) {
	    if (canDistributeOnes(sum, card, L, 0)) {
		return sum;
	    }

	    card = incrementWithMinCardinality(sum, card, L.size());
	}
    }
    
    public static BitSet getBitSetForAdjacency(List<List<Integer>> adjacency, int startNode) {
	List<Integer> adj = adjacency.get(startNode);
	if (adj.size() == 0) {
	    return new BitSet();
	}
	else {
	    List<BitSet> sets = new ArrayList<BitSet>();
	    Iterator<Integer> iter = adj.iterator();
	    while (iter.hasNext()) {
		int n2 = iter.next();
		iter.remove();
		adjacency.get(n2).remove((Object)startNode);
		BitSet b = getBitSetForAdjacency(adjacency, n2);
		increment(b);
		sets.add(b);
	    }
	    BitSet bnd = bind(sets);
	    return bnd;
	}
    }

    public static void main(String[] args) throws IOException {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	int numTests = Integer.parseInt(in.readLine());
	for(int t=0;t<numTests;t++) {
	    int numVertices = Integer.parseInt(in.readLine());
	    String[] edgeStrings = in.readLine().split("\\s+");
	    List<List<Integer>> adjacency = new ArrayList<List<Integer>>();
	    for(int x=0;x<numVertices;x++) {
		adjacency.add(new LinkedList<Integer>());
	    }
	    for(int x=0;x<numVertices-1;x++) {
		int a = Integer.parseInt(edgeStrings[x]);
		int b = x+1;
		adjacency.get(a).add(b);
		adjacency.get(b).add(a);
	    }
	    System.out.println(getBitSetForAdjacency(adjacency, 0).length());
	}
    }

}
