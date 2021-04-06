 #include <cmath>
    #include <cstdio>
    #include <vector>
    #include <map>
    #include <set>
    #include <queue>
    #include <iostream>
    #include <string>
    #include <algorithm>
    #define MAXISLAND 1000
     
    using namespace std;
     
    template<typename T>
    T getNum(){
    	T res=0;
    	char c;
    	while(1){
    		//c=getchar();
    		c = getchar_unlocked();
    		if(c==' ' || c=='\n') continue;
    		else break;
    	}
    	res=c-'0';
    	while(1){
    		//c=getchar();
    		c = getchar_unlocked();
    		if(c>='0' && c<='9') res=10*res+c-'0';
    		else break;
    	}
    	return res;
    }
     
    string getString()
    {
    	char c;
    	while(1){
    		//c=getchar();
    		c = getchar_unlocked();
    		if(c==' ' || c=='\n') continue;
    		else break;
    	}
        string i = "";
        i += c;
        while(1)
        {
        	c = getchar_unlocked();
        	if(c == '\n' || c == ' '){
        		break;
        	}
        	i += c;
        }
        return i;
    }
     
    struct Point_t {
    	int x, y, batas, typePoint;
    	string namePoint;
    };
    struct Point_tComparer
    {
        bool operator()(Point_t const &e1, Point_t const &e2)
    	{
    		return e1.namePoint < e2.namePoint;
    	}
    };
     
    struct Line_t {Point_t A, B;};
    struct RestrictedArea_t {Line_t line1, line2;};
    struct Graph_t {double weight; string nameDestination;};
    struct Graph_tComparer {
    	bool operator()(Graph_t const &e1, Graph_t const &e2)
    	{
    		return e1.weight < e2.weight;
    	}
    };
    map<string, vector<Graph_t> > G;
    set<Point_t,Point_tComparer> listPoint[MAXISLAND+2];
    map<string, int> listName;
    vector<RestrictedArea_t> listRestrictedArea[MAXISLAND+2];
    vector<Point_t> listPointSelected;
    int nIsland;
    double resultDist, weight[MAXISLAND+2];
    bool edgeWasGenerated[MAXISLAND+2];
     
    int getIdxIslandPoint(string name)
    {
    	return listName[name];
    }
     
    Point_t getPoint(string name)
    {
    	int i = getIdxIslandPoint(name);
    	
    	Point_t pointTemp;
    	pointTemp.namePoint = name;
    	return *listPoint[i].find(pointTemp);
    }
     
    double eucledian_dist(Point_t point1, Point_t point2)
    {
    	return sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
    }
     
    bool equalPoint(Point_t point1, Point_t point2)
    {
    	return (point1.x == point2.x && point1.y == point2.y);
    }
     
    bool ifIntersect(Line_t line1, Line_t line2)
    {
    	Point_t a = line1.A, b = line1.B, c = line2.A, d = line2.B;
    	
    	int test1 = ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x));
    	if(test1 == 0) return false;
    	
    	int test2 = ((d.x - c.x) * (b.y - c.y) - (d.y - c.y) * (b.x - c.x));
    	if(test2 == 0) return false;
    	
    	int test3 = ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
    	if(test3 == 0) return false;
    	
    	int test4 = ((b.x - a.x) * (d.y - a.y) - (b.y - a.y) * (d.x - a.x));
    	if(test4 == 0) return false;
    	
        return (test1 > 0) != (test2 > 0) && (test3 > 0) != (test4 > 0);
    }
     
    void generateEdgeInIsland(int idxIsland)
    {
    	//cout << "island " << idxIsland << endl;
    	for (auto it = listPoint[idxIsland].begin(); it != listPoint[idxIsland].end(); ++it)
    	{
    		for (auto it2 = next(it); it2 != listPoint[idxIsland].end(); ++it2)
    		{
    			bool isValid = true;
    			
    			for (auto& it3 : listRestrictedArea[idxIsland])
    			{
    				Line_t lineNew, lineTemp2, lineTemp3;
    				lineNew.A = *it;
    				lineNew.B = *it2;
     
    				if ( (ifIntersect(lineNew,it3.line1)) ||
    					 (ifIntersect(lineNew,it3.line2)) 
    					)
    				{
    					isValid = false;
    					break;
    				}
    			}
    			if(isValid)
    			{
    				double w = eucledian_dist(*it,*it2);
    				G[it->namePoint].push_back({w, it2->namePoint});
    				G[it2->namePoint].push_back({w, it->namePoint});
    				/*	
    				if(it->typePoint == 1) cout << "(" << it->x << "," << it->y << ")";
    				else cout << it->namePoint;
    				cout << " - ";
    				
    				if(it2->typePoint == 1) cout << "(" << it2->x << "," << it2->y << ")";
    				else cout << it2->namePoint;
    				cout << endl;
    				*/
    			}
    		}
    	}
    }
     
    void dijkstra(string s, string t)
    {
    	map<string, double> tentative;
    	map<string, bool> visited;
    	map<string, string> prev;
     	
     	/*
     	for(int i = 0; i < nIsland; i++)
     		for(auto it : listPoint[i])
     			prev[it.namePoint] = s;
     	*/
     	
    	Graph_t current;
    	visited[s] = true;
    	
    	priority_queue<Graph_t,vector<Graph_t>,Graph_tComparer> Q;
    	Q.push({0.0, s});
    	
    	while(!Q.empty())
    	{
    		current = Q.top();
    		Q.pop();
    		
    		string nowV = current.nameDestination;
    		
    		if(nowV == t)
    			break;
    		
    		double nowW = -current.weight;
    		
    		if(tentative[nowV] != nowW)
    			continue;
    		
    		int idxIsland = getIdxIslandPoint(nowV);
    		if(!edgeWasGenerated[idxIsland]){
    			generateEdgeInIsland(idxIsland);
    			edgeWasGenerated[idxIsland] = true;
    		}
    		
    		for(auto& dest : G[nowV])
    		{
    			string d = dest.nameDestination;
    			if(visited[d])
    				continue;
    				
    			double tmp = nowW + dest.weight;
    			if((tentative[d] == 0) || tentative[d] > tmp)
    			{
    				tentative[d] = tmp;
    				Q.push({-tmp,d});
    				prev[d] = nowV;
    			}
    		}	
    		visited[nowV] = true;
    	}
    	
    	string namePoint = t;
    	Point_t pointSelected;
    	int idxBefore, idxAfter;
    	
    	while(1){
    		if(namePoint == s){
    			pointSelected = getPoint(namePoint);
    			listPointSelected.insert(listPointSelected.begin(),pointSelected);
    			break;
    		}
    		pointSelected = getPoint(namePoint);
    		listPointSelected.insert(listPointSelected.begin(),pointSelected);
    		idxAfter = getIdxIslandPoint(namePoint), idxBefore = getIdxIslandPoint(prev[namePoint]);
    		if(idxAfter == idxBefore){
    			weight[idxAfter] += tentative[namePoint] - tentative[prev[namePoint]];
    		} else {
    			resultDist += tentative[namePoint] - tentative[prev[namePoint]];
    		}
    		namePoint = prev[namePoint];
    	}
    }
     
    void addPoint(string str, int x, int y, int batas, int typePoint, int idxIsland)
    {
    	listPoint[idxIsland].insert({x, y, batas, typePoint, str});
    	listName[str] = idxIsland;
    }
     
    int main()
    {
    	int T, t, w, h, nTerminal, nRestrictedArea, nEdgeNew, x1, y1, x2, y2;
    	string nameIsland;
     
    	T = getNum<int>();
    	for (int t = 1; t <= T; t++)
    	{
    		G.clear();
    		listName.clear();
    		listPointSelected.clear();
    		resultDist = 0.0;
    		
    		nIsland = getNum<int>();
    			
    		for(int i = 0; i < nIsland; i++)
    		{
    			weight[i] = 0.0;
    			listRestrictedArea[i].clear();
    			listPoint[i].clear();
    			edgeWasGenerated[i] = false;
    			nameIsland = getString();
    			w = getNum<int>();
    			h = getNum<int>();
    			nTerminal = getNum<int>();
    			
    			for(int j = 0; j < nTerminal; j++)
    			{
    				string nameTerminal;
    				int x, y;
     
    				nameTerminal = getString();
    				x = getNum<int>();
    				y = getNum<int>();
     
    				addPoint(nameIsland + nameTerminal, x, y, nameIsland.length(), 2, i);
    			}
     
    			nRestrictedArea = getNum<int>();
     
    			for(int j = 0; j < nRestrictedArea; j++)
    			{
    				x1 = getNum<int>();
    				y1 = getNum<int>();
    				x2 = getNum<int>();
    				y2 = getNum<int>();
     
    				Line_t lineNew1, lineNew2, lineNew3, lineNew4;
     
    				lineNew1.A.x = x1;
    				lineNew1.A.y = y1;
    				lineNew1.B.x = x2;
    				lineNew1.B.y = y2;
     
    				lineNew2.A.x = x2;
    				lineNew2.A.y = y1;
    				lineNew2.B.x = x1;
    				lineNew2.B.y = y2;
    				
    				listRestrictedArea[i].push_back({lineNew1, lineNew2});
     
    				string strRestrictedArea;
    				strRestrictedArea = nameIsland;
    				strRestrictedArea += '0' + j;
     
    				addPoint(strRestrictedArea + "1", lineNew1.A.x, lineNew1.A.y, 0, 1, i);
    				addPoint(strRestrictedArea + "2", lineNew2.A.x, lineNew2.A.y, 0, 1, i);
    				addPoint(strRestrictedArea + "3", lineNew2.B.x, lineNew2.B.y, 0, 1, i);
    				addPoint(strRestrictedArea + "4", lineNew1.B.x, lineNew1.B.y, 0, 1, i);
    			}
    		}
     
    		nEdgeNew = getNum<int>();
     
    		string terminal1, terminal2, island1, island2;
    		double w;
    		
    		for (int j = 0; j < nEdgeNew; j++)
    		{
    			terminal1 = getString();
    			island1 = getString();
    			terminal2 = getString();
    			island2 = getString();
    			w = getNum<double>();
    			
    			island1 += terminal1;
    			island2 += terminal2;
    			
    			G[island1].push_back({w, island2});
    			G[island2].push_back({w, island1});
    		}
    		terminal1 = getString();
    		island1 = getString();
    		terminal2 = getString();
    		island2 = getString();
     
    		island1 += terminal1;
    		island2 += terminal2;
     
    		printf("case %d Y\n", t);
    		
    		dijkstra(island1,island2);
    		for(int i = 0; i < nIsland; i++) resultDist += ceil(weight[i]);
    		
    		printf("%.0lf\n", resultDist);
    		
    		for (auto& it : listPointSelected)
    		{
    			if(it.typePoint == 1)
    				printf("%d %d\n", it.x, it.y);
    			else
    			{
    				int nTemp = it.namePoint.length();
    				for (int i = it.batas; i < nTemp; ++i) printf("%c",it.namePoint[i]);
    				printf(" ");
    				for (int i = 0; i < it.batas; ++i) printf("%c",it.namePoint[i]);
    				printf("\n");
    			}
    		}
    		printf("\n");
    	}
    	return 0;
    }  

