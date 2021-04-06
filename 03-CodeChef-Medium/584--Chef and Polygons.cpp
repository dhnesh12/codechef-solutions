#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
const int MIN_Y_COORD = static_cast<const int>(-1e5);

struct Point {
    int x, y;

    Point(long x = 0, long y = 0) { this->x = x, this->y = y; }

    inline long ccw(Point other) const {
        long ret =  this->x * other.y - this->y * other.x;
        //assert(ret != 0);
        return ret;
    }
    //Determinant of two non-collinear vectors starting from (0,0)

    bool operator<(const Point &other) const { return ccw(other) > 0; }

    bool operator>=(const Point &other) const { return ccw(other) <= 0; }
    bool operator>(const Point &other) const { return ccw(other) < 0; }
    
    Point operator-(const Point &other) { return Point(this->x - other.x, this->y - other.y); }
};

// True if moving CW
bool dir(Point a, Point b, Point c)  { return (b - a) >= (c - a); }
bool dir2(Point a, Point b, Point c) { return (b - a) > (c - a); }

void prep(vector<vector<int>> &trap, const vector<Point> &rs, const vector<Point> &bs) {
    for (int i = 0; i < rs.size(); ++i)
        for (int j = i + 1; j < rs.size(); ++j) {
            for (int k = 0; k < bs.size(); ++k) {
                if ( rs[i].x == rs[j].x ) {
                    assert( bs[k].x != rs[i].x );
                    trap[i][j] += bs[k].x == rs[i].x
                               && bs[k].y >= min(rs[i].y, rs[j].y)
                               && bs[k].y <= max(rs[i].y, rs[j].y);
                } else if ( rs[i].x < rs[j].x ) {
                    bool d1 = dir(rs[i], rs[j], bs[k]),
                         d2 = dir({rs[i].x, MIN_Y_COORD}, rs[i], bs[k]),
                         d3 = dir2(rs[j], {rs[j].x, MIN_Y_COORD}, bs[k]);
                    trap[i][j] += d1 && d2 && d3;
                    
                } else {
                    bool d1 = dir(rs[i], rs[j], bs[k]),
                         d2 = dir2({rs[i].x, MIN_Y_COORD}, rs[i], bs[k]),
                         d3 = dir(rs[j], {rs[j].x, MIN_Y_COORD}, bs[k]);
                    trap[i][j] -= !d1 && !d2 && !d3;
                }
                /*
                // {0, 1} -> {-1, +1}
                long d1 = -1 + 2*dir(rs[i], rs[j], bs[k]),
                     d2 = -1 + 2*dir2({rs[i].x, MIN_Y_COORD}, rs[i], bs[k]),
                     d3 = -1 + 2*dir(rs[j], {rs[j].x, MIN_Y_COORD}, bs[k]);

                trap[i][j] += (d1 + d2 + d3) / 3;
                */
            }
            trap[j][i] = -trap[i][j];
        }
}

void readPoints(int n, vector<Point> &p) {
    long x, y;
    for (int i = 0; i < n; ++i) {
        scanf("%li%li", &x, &y);
        p.push_back({x, y});
    }
}

int query(vector<int> &poly, vector<Point> &rs, vector<vector<int>> &trap) {
    int total = 0;

    for (int i = 0; i < poly.size(); ++i)
        total += trap[poly[i]][poly[ (i + 1) % poly.size() ]];

    return total;
}

int main() {
    int R, B, Q;
    scanf("%d%d", &R, &B);

    vector<Point> rs, bs;
    readPoints(R, rs);
    readPoints(B, bs);

    vector<vector<int>> trap(R, vector<int>(R, 0));
    prep(trap, rs, bs);

    /*
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++)
            printf("%i ", trap[i][j]);
        printf("\n");
    }
    */

    scanf("%d", &Q);
    while (Q--) {
        int V;
        scanf("%d", &V);

        vector<int> poly(V);
        for (int i = 0; i < V; ++i) {
            scanf("%d", &poly[i]);
            poly[i]--;
        }
        
        printf("%d\n", query(poly, rs, trap));
    }

    return 0;
}
