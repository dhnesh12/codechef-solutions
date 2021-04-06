import java.io.*;
import java.util.*; 
 
import static java.util.Arrays.*;
import static java.lang.StrictMath.*;
import static java.util.Collections.*;
 
public class Main {
 
    public static final int INF = (int) 1e9;
    public static final boolean DEBUG = 1==0;
 
    public static void main(String[] args) {
 
        long startTime = System.currentTimeMillis();
        try {
 
            InputReader reader = DEBUG 
                ? new InputReader(System.getProperty("ONLINE_JUDGE") != null ? System.in : new FileInputStream(args[0]))
                : new InputReader(System.in);
 
            //InputReader reader = new InputReader(new FileInputStream(args[0]));
 
            PrintWriter writer = new PrintWriter(System.out); 
 
            int shopsCount = reader.readUInt();
            int roadsCount = reader.readUInt();
            int productsCount = reader.readUInt();
            int budget = reader.readUInt();
 
            Catalog catalog = new Catalog(productsCount, shopsCount, reader);
            Graph city = new Graph(shopsCount, roadsCount, reader);
            Shopper chef = new Shopper(startTime, budget, catalog, city);
            chef.buyAll(writer);
            writer.close();
        } 
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
 
} 
 
class Shop {
 
    Shop(int id, int productsCount) {
 
        this.id = id;
 
        basket = new ListInts(productsCount);
        priceList = new ListInts(productsCount, Main.INF); 
    } 
 
    void addOffer(int product, int price) { priceList.el[product] = price; }
     
    boolean isAvailable(int product) { return priceList.el[product] != Main.INF; }
     
    int getPrice(int product) { return priceList.el[product]; }
 
    void addToBasket(int product) { basket.add(product); }
 
    int id;
    ListInts priceList;
    ListInts basket;
}
 
class Offer {
 
    Offer(int price, Shop shop) {
        this.price = price; 
        this.shop = shop; 
    }
 
    int price;
    Shop shop;
}
 
class Product {
 
    Product() { 
        id = -1; 
        weight = 0; 
    }
     
    Product(int id, int shopsCount, Shop[] shops, InputReader reader) {
 
        this.id = id;
        clear();
        shopsOffer = new ListInts(shopsCount, Main.INF);
     
        try {
            int n = reader.readUInt();
            weight = reader.readUInt();
            for (int j = 0; j < n; ++j) {
                int shop = reader.readUInt()-1;
                int price = reader.readUInt();
                offers.add(new Offer(price, shops[shop]));
                shops[shop].addOffer(id, price);
                shopsOffer.el[shop] = price;
            }
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
     
        sort(offers, new Comparator<Offer>() {
 
            @Override
            public int compare(Offer a, Offer b) {
                int diff = a.price-b.price;
                return diff != 0 ? diff : a.shop.id-b.shop.id;
            }
        });
    }
     
    boolean isBought() { return bought; }
     
    void buy(int inShop) { this.inShop = inShop; bought = true; }
     
    void clear() { bought = false; }
     
    boolean isAvailable(int shop) { return shopsOffer.el[shop] != Main.INF; }
     
    int getPrice(int shop) { return shopsOffer.el[shop]; }
     
    int getBoughtCost() { return shopsOffer.el[inShop]; } 
     
    int getWhereBought() { return inShop; };
     
    int getBestOfferShop() { return offers.get(0).shop.id; }
     
    int getBestOfferPrice() { return offers.get(0).price; } 
 
    int id;
    int weight;
    int inShop;
    boolean bought;
    List<Offer> offers = new ArrayList<Offer>();
    ListInts shopsOffer;
}
 
class Catalog {
 
    Catalog(int productsCount, int shopsCount, InputReader reader) {
 
        this.shopsCount = shopsCount;
        shops = new Shop[shopsCount];
        for (int shop = 0; shop < shopsCount; ++shop)
            shops[shop] = new Shop(shop, productsCount);
     
        this.productsCount = productsCount; 
        products = new Product[productsCount];
        initProducts = new Product[productsCount];
        for (int product = 0; product < productsCount; ++product)
            initProducts[product] = products[product] = new Product(product, shopsCount, shops, reader);
 
        sort(products, new Comparator<Product>() {
            
            @Override
            public int compare(Product a, Product b) {
                int diff = a.weight-b.weight;
                return diff != 0 ? diff : a.id-b.id;
            }
        });
    }
 
    int productsCount, shopsCount;
    Product[] products, initProducts;
    Shop[] shops; 
}
 
class Edge {
 
    Edge(int to, int distance) {
        this.to = to; 
        this.distance = distance;
    }
 
    int to;
    int distance;
}
 
class Graph {
  
    public static final int N = (int) 1e3;
 
    Graph(int shopsCount, int roadsCount, InputReader reader) {
 
        this.shopsCount = shopsCount;
        for (int i = 0; i < shopsCount; ++i) {
            for (int j = 0; j < i; ++j)
                d[i<<10|j] = Main.INF;
            d[i<<10|i] = 0;
        }
         
        try {
            for (int road = 0; road < roadsCount; ++road) {
                int shop1 = reader.readUInt()-1;
                int shop2 = reader.readUInt()-1;
                addEdge(shop1, shop2, reader.readUInt());
            }
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
 
        floydWarshall();
    }
 
    void addEdge(int shop1, int shop2, int distance) {
        adj[shop1].add(new Edge(shop2, distance));
        adj[shop2].add(new Edge(shop1, distance));
        if (shop1 < shop2) {
            int tmp = shop1; shop1 = shop2; shop2 = tmp;
        }
        d[shop1<<10|shop2] = distance;
    }
 
    void floydWarshall() {
        for (int i = 0; i < shopsCount; ++i)
            for (int j = 0; j < shopsCount; ++j)
                if (i != j) {
                    int aji = i < j ? d[j<<10|i] : d[i<<10|j];
     
                    if (aji == Main.INF)
                        continue;
     
                    for (int k = min(i, j)-1; k >= 0; --k) {
                        int njk = aji + d[i<<10|k];
                        if (njk < d[j<<10|k]) 
                            d[j<<10|k] = njk;
                    }
     
                    for (int k = i+1; k < j; ++k) {
                        int njk = aji + d[k<<10|i];
                        if (njk < d[j<<10|k]) 
                            d[j<<10|k] = njk;
                    }
                }
     
        for (int i = 0; i < shopsCount-1; ++i)
            for (int j = i+1; j < shopsCount; ++j)
                d[i<<10|j] = d[j<<10|i];
    }   
 
    int dijkstra(int s, int t) {
     
        fill(distances, 0, shopsCount, Main.INF);
     
        path[s] = -1;
        distances[s] = 0;
        queue.clear();
        queue.add(s);
        do {
            int v = queue.pollFirst(); 
            int d = distances[v];
     
            if (v == t)
                break;
     
            for (Edge e: adj[v]) {
     
                if (distances[e.to] < Main.INF && distances[e.to] > d+e.distance)
                    queue.remove(e.to);
     
                if (distances[e.to] > d+e.distance) {
                    path[e.to] = v;
                    distances[e.to] = d+e.distance;
                    queue.add(e.to);
                }
            }
        }
        while (!queue.isEmpty());
     
        return distances[t];
    } 
 
    void getPath(int s, int t, ListInts p) {
        if (s != t) {
            getPath(s, path[t], p);
            p.add(t+1);
        }
    }
 
    int getDistance(int s, int t) { return d[s<<10|t]; }
 
    int shopsCount;
 
    List<Edge> adj[] = new List[N];
 
    {
        for (int i = 0; i < N; ++i)
            adj[i] = new ArrayList<Edge>();
    }
 
    int distances[] = new int[N];
    int d[] = new int[1<<20]; 
    int path[] = new int[N];
 
    TreeSet<Integer> queue = new TreeSet(new Comparator<Integer>() {
        
        @Override
        public int compare(Integer a, Integer b) {
            int delta = distances[a]-distances[b];
            return delta != 0 ? delta : a-b;
        }
    });
}
 
class Purchase {
 
    Purchase(Product product, Shop shop) {
        set(product, shop);
    }
 
    void set(Product product, Shop shop) {
        this.product = product;
        this.shop = shop;
    }
 
    Product product;
    Shop shop;
}
 
class OrderIndex {
 
    public static final int K = 502;
 
    OrderIndex(int budget, Catalog catalog, Graph city) {
 
        this.budget = budget;
        this.city = city;
 
        order.ensureCapacity(size = catalog.productsCount+2);
     
        order.add(new Purchase(new Product(), catalog.shops[0]));
        spent = 0;
        for (Product product: catalog.products) {
            order.add(new Purchase(product, catalog.shops[product.getBestOfferShop()]));
            spent += product.getBestOfferPrice();
        }
        order.add(new Purchase(new Product(), catalog.shops[catalog.shopsCount-1]));
     
          headWeight[0] =   tailWeight[size-1] = 
        headDistance[0] = tailDistance[size-1] = 0;
            headCost[0] =     tailCost[size-1] = 0;
     
        updateIndex(1);
        updateReverseIndex(size-2);
     
        cost = headCost[size-1];
 
        t = cost < 2*catalog.productsCount ? 1 : cost/(2*catalog.productsCount);
        cooling = 0.99999;
    }
 
    void reset(double cooling, Catalog catalog) {
 
          headWeight[0] =   tailWeight[size-1] = 
        headDistance[0] = tailDistance[size-1] = 0;
            headCost[0] =     tailCost[size-1] = 0;
     
        updateIndex(1);
        updateReverseIndex(size-2);
     
        cost = headCost[size-1];
 
        t = cost < 2*catalog.productsCount ? 1 : cost/(2*catalog.productsCount);
        this.cooling = cooling;
    }
     
    void updateIndex(int from) {
        for (int i = from; i < size; ++i) {
            int dij = city.getDistance(order.get(i-1).shop.id, order.get(i).shop.id);
            headWeight[i] = headWeight[i-1] + order.get(i).product.weight;
            headDistance[i] = headDistance[i-1] + dij;
            headCost[i] = headCost[i-1] + (long) dij*headWeight[i-1];
        }
    }
     
    void updateReverseIndex(int from) {
        for (int i = from; i >= 0; --i) {
            int dij = city.getDistance(order.get(i+1).shop.id, order.get(i).shop.id);
            tailWeight[i] = tailWeight[i+1] + order.get(i).product.weight;
            tailDistance[i] = tailDistance[i+1] + dij;
            tailCost[i] = tailCost[i+1] + (long) dij*tailWeight[i+1];
        }
    }
 
    long getReverseCost(int i, int j)
    {
        int shopI = order.get(i).shop.id, shopJ = order.get(j).shop.id;
        int shopIm1 = order.get(i-1).shop.id, shopJm1 = order.get(j-1).shop.id;
     
        int dij = city.getDistance(shopI, shopJ);
     
        long unchangedPrefixCost = headCost[i-1];
        long unchangedSuffixCost = headCost[size-1] - headCost[j] - (long) headWeight[j-1]*tailDistance[j];
     
        long reversedSegmentWeight = tailWeight[i] - tailWeight[j];
        long reversedSegmentDistance = tailDistance[i] - tailDistance[j-1];
        long reversedSegmentCost = tailCost[i] - tailCost[j-1] - (long) tailWeight[j]*reversedSegmentDistance;
     
        return unchangedPrefixCost 
             + headWeight[i-1]*(city.getDistance(shopIm1, shopJm1) + reversedSegmentDistance + dij + tailDistance[j])
             + reversedSegmentCost + reversedSegmentWeight*(dij + tailDistance[j])
             + unchangedSuffixCost;
    }
     
    long getChangeCost(int i, int newShop)
    {
        long totalCost = cost;
     
        int oldShop = order.get(i).shop.id;
        int d1 = city.getDistance(order.get(i-1).shop.id, oldShop);
        int d2 = city.getDistance(oldShop, order.get(i+1).shop.id);
        int d12 = d1+d2;
        int d1New = city.getDistance(order.get(i-1).shop.id, newShop);
        int d2New = city.getDistance(newShop, order.get(i+1).shop.id);
        int d12New = d1New+d2New;
     
        return totalCost
             + (d12New-d12) * (long) headWeight[i-1] 
             + (d2New-d2) * (long) order.get(i).product.weight;
    }
     
    long getChangeCost(int i, int j, int newShop)
    {
     
        int shopI = order.get(i).shop.id;
        int shopIm1 = order.get(i-1).shop.id;
        int shopIp1 = order.get(i+1).shop.id;
     
        int shopJ = order.get(j).shop.id;
        int shopJm1 = order.get(j-1).shop.id;
        int shopJp1 = order.get(j+1).shop.id;
     
        int d1 = city.getDistance(shopIm1, shopI);
        int d2 = city.getDistance(shopI, shopIp1);
     
        int dOld = d1+d2;
        int dNew = city.getDistance(shopIm1, shopIp1);
     
        long w = order.get(i).product.weight;
     
        long removedCost = cost
            + (dNew - dOld) * (long) headWeight[i-1]
            - w*tailDistance[i];
     
        if (j < i)
        {
     
            int dij = city.getDistance(newShop, shopJ);
            int djm1i = city.getDistance(shopJm1, newShop);
            int djm1j = city.getDistance(shopJm1, shopJ);
            
            return removedCost 
                + w*(tailDistance[j] - dOld + dNew + dij)
                + (djm1i + dij - djm1j) * (long) headWeight[j-1];
        }
        else
        {
            int dijp1 = city.getDistance(newShop, shopJp1);
            int dji = city.getDistance(shopJ, newShop);
            int djjp1 = city.getDistance(shopJ, shopJp1);
     
            return removedCost
                + w*(tailDistance[j+1] + dijp1)
                + (dji + dijp1 - djjp1) * (long) (headWeight[j] - w);
        }
    }
     
    long getShiftCost(int i, int j)
    {
        int shopI = order.get(i).shop.id;
        int shopIm1 = order.get(i-1).shop.id;
        int shopIp1 = order.get(i+1).shop.id;
        int shopJ = order.get(j).shop.id;
        int shopJm1 = order.get(j-1).shop.id;
        int shopJp1 = order.get(j+1).shop.id;
        int d1 = city.getDistance(shopIm1, shopI);
        int d2 = city.getDistance(shopI, shopIp1);
        int d12 = d1+d2;
        int dNew = city.getDistance(shopIm1, shopIp1);
     
        long w = order.get(i).product.weight;
     
        long removedCost = cost
            - (d12 - dNew) * (long) headWeight[i-1]
            - w*tailDistance[i];
     
        if (j < i)
        {
     
            int dij = city.getDistance(shopI, shopJ);
            int djm1i = city.getDistance(shopJm1, shopI);
            int djm1j = city.getDistance(shopJm1, shopJ);
            
            return removedCost 
                + w*(tailDistance[j] - d12 + dNew + dij)
                + (djm1i + dij - djm1j) * (long) headWeight[j-1];
        }
        else
        {
            int dijp1 = city.getDistance(shopI, shopJp1);
            int dji = city.getDistance(shopJ, shopI);
            int djjp1 = city.getDistance(shopJ, shopJp1);
     
            return removedCost
                + w*(tailDistance[j+1] + dijp1)
                + (dji + dijp1 - djjp1) * (long) (headWeight[j] - w);
        }
    }
     
    long getSwapCost(int i, int j)
    {
        int shopI = order.get(i).shop.id;
        int shopIp1 = order.get(i+1).shop.id;
        int shopIm1 = order.get(i-1).shop.id;
        int shopJ = order.get(j).shop.id;
        int shopJp1 = order.get(j+1).shop.id;
        int shopJm1 = order.get(j-1).shop.id;
     
        long wi = order.get(i).product.weight;
        long wj = order.get(j).product.weight;
     
        int dim1ip1 = city.getDistance(shopIm1, shopIp1);
        int dim1i = city.getDistance(shopIm1, shopI);
        int diip1 = city.getDistance(shopI, shopIp1);
     
        int djm1jp1 = city.getDistance(shopJm1, shopJp1);
        int djm1j = city.getDistance(shopJm1, shopJ);
        int djjp1 = city.getDistance(shopJ, shopJp1);
     
        int dim1j = city.getDistance(shopIm1, shopJ);
        int djip1 = city.getDistance(shopJ, shopIp1);
     
        int djm1i = city.getDistance(shopJm1, shopI);
        int dijp1 = city.getDistance(shopI, shopJp1);
     
        int deltaI = dim1j + djip1 - dim1i - diip1;
        int deltaJ = djm1i + dijp1 - djm1j - djjp1;
     
        return cost 
             - wi*tailDistance[i]
             - wj*tailDistance[j]
             + wj*(tailDistance[i+1] + deltaJ + djip1)
             + wi*(tailDistance[j+1] + dijp1)
             + deltaI * (long) headWeight[i-1]
             + deltaJ * (headWeight[j-1] - wi);
    }
 
    void tryReverse(int i, int j) {
        long newCost = getReverseCost(i, j);
        double tmp = rng.nextDouble();
        if (tmp < exp((cost-newCost)/t)) {
            cost = newCost;
            int x = i, y = j-1;
            while (x < y) {
                swap(order, x++, y--);
            }
            updateIndex(i);
            updateReverseIndex(j-1);
        }
    }
 
    void tryChange(int i) {
        int spentI = order.get(i).product.getPrice(order.get(i).shop.id);
        int vars = 0;
        for (Offer offer: order.get(i).product.offers)
            if (spent+offer.price-spentI <= budget)
                ++vars;
            else
                break;
        if (vars > 1)
        {
     
            int x = rng.nextInt(vars-1);
            for (Offer offer: order.get(i).product.offers)
                if (offer.shop.id != order.get(i).shop.id)
                    if (x == 0)
                    {
                        long newCost = getChangeCost(i, offer.shop.id);
                        if (rng.nextDouble() < exp((cost-newCost)/t))
                        {
                            cost = newCost;
                            order.get(i).shop = offer.shop;
                            updateIndex(i);
                            updateReverseIndex(i);
                            spent += offer.price-spentI;
                        }
                        break;
                    }
                    else
                        --x;
        }
    }
 
    void tryChange2(int i, int k)
    {
        int spentI = order.get(i).product.getPrice(order.get(i).shop.id);
        int vars = 0;
        for (Offer offer: order.get(i).product.offers)
            if (spent+offer.price-spentI <= budget)
                ++vars;
            else
                break;
        if (vars > 1)
        {
            int x = rng.nextInt(vars-1);
            for (Offer offer: order.get(i).product.offers)
                if (offer.shop.id != order.get(i).shop.id)
                    if (x == 0)
                    {
                        for (int it = 0; it < 23; ++it)
                        {
                            int j = rng.nextInt(k) + 1;
                            while (j == i)
                                j = rng.nextInt(k)+1;
                            long newCost = getChangeCost(i, j, offer.shop.id);
                            if (rng.nextDouble() < exp((cost-newCost)/t))
                            {
                                cost = newCost;
                                order.get(i).shop = offer.shop;
                                Purchase p = order.get(i);
                                order.remove(i);
                                order.add(j, p);
                                updateIndex(min(i, j));
                                updateReverseIndex(max(i, j));
                                spent += offer.price-spentI;
                            }
                            break;
                        }
                        break;
                    }
                    else
                        --x;
        }
    }
 
    void tryShift(int i, int j) {
     
        long newCost = getShiftCost(i, j);       
        if (rng.nextDouble() < exp((cost-newCost)/t)) {
            cost = newCost;
            Purchase p = order.get(i);
            order.remove(i);
            order.add(j, p);
            updateIndex(min(i, j));
            updateReverseIndex(max(i, j));
        }
    }
 
    void trySwap(int i, int j) {
        if (i > j) {
            int tmp = i; i = j; j = tmp;
        }
        if (i+1 == j)
            return;
        long newCost = getSwapCost(i, j);
        if (rng.nextDouble() < exp((cost-newCost)/t)) {
            cost = newCost;
            swap(order, i, j);
            updateIndex(i);
            updateReverseIndex(j);
        }
    }
 
    long calculateCost() {
        long cost = 0, weight = 0;
        int currentShop = 0;
 
        boolean up[] = new boolean[1111];
     
        for (Purchase purchase: order) {
            cost += weight*city.getDistance(currentShop, purchase.shop.id);
            weight += purchase.product.weight;
 
            if (purchase.product.id != -1) {
                if (up[purchase.product.id])
                    throw new RuntimeException("Double use: " + purchase.product.id);
                up[purchase.product.id] = true;
            }
 
            currentShop = purchase.shop.id;
        }
     
        return cost;
    }
 
    void tick() { t *= cooling; }
 
    RandomGenerator rng = new RandomGenerator();
  
    double t, cooling;
    long cost;
 
    Graph city;
 
    int budget, spent, size;
    ArrayList<Purchase> order = new ArrayList<Purchase>();
 
    int headWeight[] = new int[K]; 
    int tailWeight[] = new int[K]; 
    int headDistance[] = new int[K]; 
    int tailDistance[] = new int[K]; 
    long headCost[] = new long[K]; 
    long tailCost[] = new long[K]; 
}
 
class Shopper {
 
    public static final long TL1 = 8400;
    public static final long TL2 = 9800;
    public static final long TIME_LIMIT = 9800; 
     
    Shopper(long startTime, int budget, Catalog catalog, Graph city) {
        this.startTime = startTime;
        this.budget = budget; 
        this.catalog = catalog; 
        this.city = city;
    }
 
    void buyAll(PrintWriter writer)  {
 
        boolean debug = Main.DEBUG;
        OrderIndex order = new OrderIndex(budget, catalog, city);
        ListInts plan = new ListInts();
 
        sa(startTime + TL1, order, plan);
        plan = optimizeShop(plan);
        plan = optimizeRoute(plan, order);
        order.reset(0.99998, catalog);
 
        if (debug)
            System.err.println(order.cost + " " + order.calculateCost() + " " + order.t);
 
        sa(startTime + TL2, order, plan);
        plan = optimizeShop(plan);
        plan = optimizeRoute(plan);
 
        if (debug)
            System.err.println(order.cost + " " + order.calculateCost() + " " + order.t);
 
        if (!debug)
            printPlan(plan, writer);
    }
     
    ListInts optimizeShop(ListInts plan) {
        ListInts route = new ListInts(plan.size);
        for (int i = 0; i < plan.size; ++i) {
            int action = plan.el[i];
            if (action > 0)
                route.add(action-1);
        }
        
        int cost = 0;
        for (Product product: catalog.products) {
            cost += product.getBoughtCost();
            product.clear();
        }
     
        for (int i = route.size-1; i >= 0; --i) {
            int shop = route.el[i];
            for (Product product: catalog.products) 
                if (!product.isBought() && product.inShop == shop) {// && product.isAvailable(shop) && cost+product.getPrice(shop)-product.getBoughtCost() <= budget) {
                    cost += product.getPrice(shop)-product.getBoughtCost();
                    product.buy(shop);
                }
        }
 
        for (Product p: catalog.products)
            p.bought = false;
 
        for (int i = route.size-1; i >= 0; --i) {
            int shop = route.el[i]; 
            for (Product product: catalog.products)
                if (!product.bought) {
                    if (product.inShop == shop) {
                        product.bought = true;
                    }
                    else if (product.isAvailable(shop) && cost+product.getPrice(shop)-product.getBoughtCost() <= budget) {
                        cost += product.getPrice(shop)-product.getBoughtCost();
                        product.buy(shop);
                    }
                }
        }
     
        ListInts optimizedPlan = new ListInts(plan.size);
     
        int visitCount[] = new int[catalog.shopsCount];
        for (int i = 0; i < route.size; ++i)
            ++visitCount[route.el[i]];
     
        if (visitCount[0] == 0)
            shopIn(0, optimizedPlan); 
        for (int i = 0; i < route.size; ++i) {
            int shop = route.el[i];
            optimizedPlan.add(shop+1);
            if (--visitCount[shop] == 0)
                shopIn(shop, optimizedPlan);
        }
     
        return optimizedPlan;
    }
     
    ListInts optimizeRoute(ListInts plan) {
        boolean used[] = new boolean[catalog.shopsCount];
        for (Product product: catalog.products)
            used[product.getWhereBought()] = true;
     
        int visitCount[] = new int[catalog.shopsCount];
        for (int i = 0; i < plan.size; ++i) {
            int x = plan.el[i];
            if (x > 0)
                ++visitCount[x-1];
        }
     
        int currentShop = 0;
        boolean skipped = false;
     
        ListInts optimizedPlan = new ListInts(plan.size);
        for (int i = 0; i < plan.size; ++i) {
            int action = plan.el[i];
            if (action < 0) {
                optimizedPlan.add(action);
                skipped = false;
            }
            else if (used[action-1] && --visitCount[action-1] == 0) {
                if (skipped) {
                    city.dijkstra(currentShop, action-1);
                    city.getPath(currentShop, action-1, optimizedPlan);
                }
                else {
                    optimizedPlan.add(action);
                }
     
                currentShop = action-1;
            }
            else {
                skipped = true;
            }
        }
     
        city.dijkstra(currentShop, catalog.shopsCount-1);
        city.getPath(currentShop, catalog.shopsCount-1, optimizedPlan);
     
        return optimizedPlan;
    }
     
    ListInts optimizeRoute(ListInts plan, OrderIndex order) {
        boolean used[] = new boolean[catalog.shopsCount];
        for (Product product: catalog.products)
            used[product.getWhereBought()] = true;
     
        int visitCount[] = new int[catalog.shopsCount];
        for (int i = 0; i < plan.size; ++i) {
            int x = plan.el[i];
            if (x > 0)
                ++visitCount[x-1];
        }
     
        int currentShop = 0;
        boolean skipped = false;
     
        ListInts optimizedPlan = new ListInts(plan.size);
        int ind = 1;
        for (int i = 0; i < plan.size; ++i) {
            int action = plan.el[i];
            if (action < 0) {
                optimizedPlan.add(action);
                order.order.get(ind++).set(catalog.initProducts[-action-1], catalog.shops[currentShop]);
                skipped = false;
            }
            else if (used[action-1] && --visitCount[action-1] == 0) {
                if (skipped) {
                    city.dijkstra(currentShop, action-1);
                    city.getPath(currentShop, action-1, optimizedPlan);
                }
                else {
                    optimizedPlan.add(action);
                }
     
                currentShop = action-1;
            }
            else {
                skipped = true;
            }
        }
     
        city.dijkstra(currentShop, catalog.shopsCount-1);
        city.getPath(currentShop, catalog.shopsCount-1, optimizedPlan);
 
        return optimizedPlan;
    }
 
    void shopIn(int shop, ListInts plan) {
        for (Product product: catalog.products)
            if (product.getWhereBought() == shop)
                plan.add(-product.id-1);
    }
 
    RandomGenerator rng = new RandomGenerator();
 
    void sa(long tl, OrderIndex order, ListInts plan) {
     
        int k = catalog.productsCount, its = 0;
            
        do {
     
            int from = rng.nextInt(k-1)+1;
            int to = from+rng.nextInt(k-from+1)+1;
            order.tryReverse(from, to);
 
            for (int it = 0; it < (k < 100 ? 7 : rng.nextInt(23)); ++it)
                order.tryChange(rng.nextInt(k) + 1);
 
            int x = rng.nextInt(k), y = rng.nextInt(k);
            while (x == y)
                x = rng.nextInt(k);
            order.tryShift(x+1, y+1);
     
            order.tryChange2(rng.nextInt(k) + 1, k);
 
            order.tick();
            if (++its%1000 == 0 && System.currentTimeMillis() > tl)
                break;
        }
        while (true);
     
        plan.size = 0;
        int currentShop = 0;
        for (Purchase purchase: order.order)
        {
            int productId = purchase.product.id, toShop = purchase.shop.id;
     
            purchase.product.buy(toShop);
            city.dijkstra(currentShop, toShop);
            city.getPath(currentShop, toShop, plan);
            plan.add(-productId-1);
            currentShop = toShop;
        }
    }
     
    void printPlan(ListInts plan, PrintWriter writer) {
        writer.println(plan.size);
        for (int i = 0; i < plan.size; ++i) {
            writer.print(plan.el[i]);
            writer.print(' ');
        }
        writer.println();
    }
 
    long startTime;
    int budget;
    Catalog catalog;
    Graph city;
}
 
class InputReader {
 
    private static final int BUFFER_SIZE = (1 << 16)-1;
    private static final int ALPHABET_SIZE = 1<<8; 
 
    private int cursor = BUFFER_SIZE;
    private byte[] buffer = new byte[BUFFER_SIZE];
    private boolean[] isDigit = new boolean[ALPHABET_SIZE];
 
    private InputStream stream;
 
    public InputReader(InputStream stream) {
        this.stream = stream;
        for (int i = 48; i <= 57; ++i) 
            isDigit[i] = true;
    }
 
    public int readUInt() throws IOException {
        return readU31(begin());
    }
 
    private void readAhead(int amount) throws IOException {
        int remaining = BUFFER_SIZE^cursor;
        if (remaining < amount) {
            System.arraycopy(buffer, cursor, buffer, 0, remaining);
            remaining += stream.read(buffer, remaining, cursor);
            cursor = 0;
            if (remaining < BUFFER_SIZE)
                buffer[remaining] = (byte) 0;
        }
    }
 
    private byte read() {
        return buffer[cursor++];
    }
 
    private byte begin() throws IOException {
        readAhead(23);
        byte c = read();
        while (!isDigit[c]) { 
            c = read();
        }
        return c;
    }
 
    private int readU31(byte c) {
        int r = 0;
        while (isDigit[c]) {
            r = (r<<3) + (r<<1) + (c&15);
            c = read();
        }
        return r;
    }
}
 
class ListInts {
 
    public static final int DEFAULT_CAPACITY = 11;
 
    public ListInts() {
        this(DEFAULT_CAPACITY);
    }
 
    public ListInts(int capacity) {
        el = new int[this.capacity = capacity];
        size = 0;
    }
 
    public ListInts(int size, int value) {
        el = new int[capacity = size];
        fill(el, value);
        this.size = size;
    }
 
    public void add(int v) {
        if (size < capacity) {
            el[size++] = v;
        }
        else {
            el = copyOf(el, capacity <<= 1);
            el[size++] = v;
        }
    } 
 
    int[] el;
 
    int size;
    int capacity;
}
 
class RandomGenerator {
 
    private static final double r = 9007199254740881.0/9007199254740992.0;
    private static final double d = 362436069876.0/9007199254740992.0;
 
    public RandomGenerator() {
        this(22222239);
    }
 
    public RandomGenerator(long seed) {
        try {
            x = seed;
            fillU(nextInt(), nextInt());
        } 
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
 
    public int nextInt() {
        return nextInt((int) 1e9);
    }
 
    public int nextInt(int n) {
        x ^= x << 21;
        x ^= x >>> 35;
        x ^= x << 4;
        int r = (int)x % n;     
        return r < 0 ? -r : r;
    }
 
    public double nextDouble() {
        double x = u[i] - u[j];
        if (x < 0.0)
            x += 1.0;
        u[i] = x;
 
        if (--i == 0) i = 97;
        if (--j == 0) j = 97;
 
        c -= d;
        if (c < 0.0)
            c += r;
 
        x -= c;
        return x < 0. ? x+1. : x;
    }
 
    private void fillU(int seed1, int seed2) {
        int x = seed1;
        int y = seed2;
 
        for (int i = 1; i < 98; ++i) {
            double s = 0.0;
            double t = 0.5;
 
            for (int j = 1; j < 54; ++j) {
                x = (6969*x) % 65543;
                y = (8888*y) % 65579;
                if (((x^y) & 32) > 0)
                    s += t;
                t *= .5;
            }
            if (x == 0)
                throw new IllegalArgumentException("x");
            if (y == 0)
                throw new IllegalArgumentException("y");
            u[i] = s;
        }
    }
 
    private long x = 1;
    private double c = 0.;
    private int i = 97, j = 33;
 
    private double[] u = new double[98];
}