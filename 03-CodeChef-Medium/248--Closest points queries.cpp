#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

#define FASTIO  ios::sync_with_stdio(false); cin.tie(0);

typedef long long ll;
typedef int idist;
typedef pair<int, int> point;
typedef pair<point, point> ppoint;
typedef pair<idist, ppoint> distpoint;
#define LIM 2500

class ClosestPointsDistanceQueryPriorityQueue{
	private:
		priority_queue<distpoint> maxPQDistPointPair;
		set<point> pointsSet;
		vector<point> pointsVector;
		bool flag[502][502];
		int sqr(int x){
			return x*x;
		}
		int dist(point a, point b){
			return sqr(a.first-b.first) + sqr(a.second-b.second);
		}
	public:
		ClosestPointsDistanceQueryPriorityQueue(){
		}
		void add(int x, int y){
			if (pointsSet.size() < LIM){
				for (auto it = pointsSet.begin(); it != pointsSet.end(); it++){
					maxPQDistPointPair.push(make_pair(-dist((*it), make_pair(x, y)), make_pair((*it), make_pair(x, y))));
				}
			}
			else{
				for (int i = x - 20; i <= x + 20; i++){
					for (int j = y - 20; j <= y + 20; j++){
						if (i>=0&&j>=0&&i<502&&j<502&&flag[i][j]){
							maxPQDistPointPair.push(make_pair(-dist(make_pair(i,j), make_pair(x, y)), make_pair(make_pair(i,j), make_pair(x, y))));
						}
					}
				}
				pointsVector.push_back(make_pair(x, y));
			}
			flag[x][y] = true;
			pointsSet.insert(make_pair(x, y));

		}
		void remove(int x, int y){
			pointsSet.erase(make_pair(x, y));
			flag[x][y] = false;
			if (pointsSet.size() < LIM && pointsVector.size()){
				for (int j = 0; j < pointsVector.size(); j++){
					x = pointsVector[j].first;
					y = pointsVector[j].second; 
					if (flag[x][y] == false)continue;
					for (auto it = pointsSet.begin(); it != pointsSet.end(); it++){
						maxPQDistPointPair.push(make_pair(-dist((*it), make_pair(x, y)), make_pair((*it), make_pair(x, y))));
					}
				}
				pointsVector.clear();
			}
		}
		int closestDistance(){
			while(!maxPQDistPointPair.empty()){
				auto topItem = maxPQDistPointPair.top();
				auto firstPoint = topItem.second.first;
				auto secondPoint = topItem.second.second;
				if (pointsSet.count(firstPoint) == 0 || pointsSet.count(secondPoint) == 0){
					maxPQDistPointPair.pop();
					continue;
				}
				return -topItem.first;
			}
			return 0;
		}
};


int main() {
	int t; cin >> t;
	ClosestPointsDistanceQueryPriorityQueue* cpdq = new ClosestPointsDistanceQueryPriorityQueue();
	while(t--) {
		char c; 
		int x, y; 
		cin >> c>>x>>y;
		if (c == '+') {
			cpdq->add(x, y);
		} else {
			cpdq->remove(x, y);
		}
		cout<<cpdq->closestDistance()<<"\n";
	}
	delete cpdq;
	return 0;
}