#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
using namespace chrono_literals;
using ll = long long;

static bool REAL_SUBMISSION = true;

string SOLVER = REAL_SUBMISSION ? "B" : "S";

struct RNG_ {
    void reset(ll seed=0) {
        if (!seed) seed = (ll)(intptr_t)new int;
        gen.seed(seed);
    }
    int operator()(int n) { return (*this)(0, n-1); }
    int operator()(int lo, int hi) {
        uniform_int_distribution<int> dist(lo, hi);
        return dist(gen);
    }
    int operator()(const vector<int>& vec) {
        assert(!vec.empty());
        return vec[(*this)(0, vec.size() - 1)];
    }
    mt19937 gen;
} RNG;

struct Timer {
    chrono::time_point<chrono::system_clock> start;
    Timer() : start(chrono::system_clock::now()) {}
    chrono::milliseconds elapsed() const {
        auto now = chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - start);
    }
    ll millis() const {
        return elapsed().count();
    }
};

auto find(vector<int>& vec, int x) {
    return find(vec.begin(), vec.end(), x);
}

auto find(const vector<int>& vec, int x) {
    return find(vec.begin(), vec.end(), x);
}

bool contains(const vector<int>& vec, int x) {
    return find(vec, x) != vec.end();
}

void sortuniq(vector<int>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

struct Point {
    ll x, y;
};

struct Edge {
    Edge(int a, int b) {
        p[0] = min(a, b);
        p[1] = max(a, b);
    }

    bool operator<(Edge x) const {
        if (p[0] != x.p[0]) return p[0] < x.p[0];
        return p[1] < x.p[1];
    }

    bool operator==(Edge x) const {
        return p[0]==x.p[0] && p[1]==x.p[1];
    }

    int p[2];
};

struct Triangle {
    int p[3];
};

struct Shape {
    int id = -1;
    ll area = 0;
    vector<int> points;
};

struct Flip {
    Edge oldEdge;
    Edge newEdge;
};

struct Solution;

struct TestCase {
    vector<Point> points;
    vector<Triangle> triangles;
    vector<ll> areas;
    unique_ptr<Solution> perfect = nullptr;

    ll area(const Triangle& t) const;
};

struct Solution {
    explicit Solution(const TestCase* tc);

    bool flip(Edge &edge);
    bool flip(Flip flip);
    void undoFlip();
    bool remove(Edge edge);

    Edge randomEdge();

    bool complete();
    ll score();

    Shape& lookupShape(int id);
    bool mergeShapes(int id1, int id2);

    vector<Edge>& getEdges(vector<Edge>& result, const Shape& shape);
    void swapPoint(Shape& shape, int oldPoint, int newPoint);

public:
    const TestCase* tc = nullptr;
    vector<Flip> flips;
    vector<Edge> deletions;
    vector<vector<int>> pointadj;
    vector<Shape> shapes;
    map<Edge, pair<int, int>> edgeadj;
};

istream& operator>>(istream& s, TestCase& tc);

ostream& operator<<(ostream& s, const vector<int>& vec);
ostream& operator<<(ostream& s, const Edge&);
ostream& operator<<(ostream& s, const Flip&);
ostream& operator<<(ostream& s, const Triangle&);
ostream& operator<<(ostream& s, const Shape&);
ostream& operator<<(ostream& s, Solution& sol);

struct Solver {
    virtual ~Solver() = default;
    virtual Solution solve(const TestCase* tc) = 0;
};

struct RandomMergeSolver final : Solver {
    static RandomMergeSolver* instance();
    Solution solve(const TestCase* tc) override;
};

struct PerfectSolver final : Solver {
    static PerfectSolver* instance();
    Solution solve(const TestCase* tc) override;
};

struct BestSolver final : Solver {
    static BestSolver* instance();
    Solution solve(const TestCase* tc) override;
};

struct SubmarineSolver final : Solver {
    static SubmarineSolver* instance();
    Solution solve(const TestCase* tc) override;
};

// Source: http://codechef.com/download/Images/FEB21/CUTCAKE/generator.cp
namespace CodeChefGenerator {
//Delaunay Triangulation functions
typedef long long ll;
bool ge(const ll& a, const ll& b) { return a >= b; }
bool le(const ll& a, const ll& b) { return a <= b; }
bool eq(const ll& a, const ll& b) { return a == b; }
bool gt(const ll& a, const ll& b) { return a > b; }
bool lt(const ll& a, const ll& b) { return a < b; }

struct pt {
    ll x, y;
    pt() { }
    pt(ll _x, ll _y) : x(_x), y(_y) { }
    pt operator - (const pt& p) const {
        return pt(x - p.x, y - p.y);
    }
    ll cross(const pt& p) const {
        return x * p.y - y * p.x;
    }
    ll cross(const pt& a, const pt& b) const {
        return (a - *this).cross(b - *this);
    }
    ll dot(const pt& p) const {
        return x * p.x + y * p.y;
    }
    ll dot(const pt& a, const pt& b) const {
        return (a - *this).dot(b - *this);
    }
    ll sqrLength() const {
        return this->dot(*this);
    }
    bool operator == (const pt& p) const {
        return eq(x, p.x) && eq(y, p.y);
    }
    bool operator < (const pt& p) const{
        if(x != p.x) return x < p.x;
        return y<p.y;
    }
};
bool ccw(pt a,pt b,pt c){
    return ((b-a).cross(c-b))>0;
}
bool convex(pt a,pt b,pt c,pt d){
    return (
            (ccw(a,b,c) && ccw(b,c,d) && ccw(c,d,a) && ccw(d,a,b)) ||
            (ccw(a,d,c) && ccw(d,c,b) && ccw(c,b,a) && ccw(b,a,d))
            );
}

ll triangleArea(Point p1, Point p2, Point p3) {
    pt x(p1.x, p1.y);
    pt y(p2.x, p2.y);
    pt z(p3.x, p3.y);
    ll area = (y - x).cross(z - x);
    return llabs(area);
}

ll triangleArea(const vector<Point>& points, const int* ids) {
    return triangleArea(points[ids[0]], points[ids[1]], points[ids[2]]);
}

bool convex(const vector<Point>& points, int p1, int p2, int p3, int p4) {
    pt a(points[p1].x, points[p1].y);
    pt b(points[p2].x, points[p2].y);
    pt c(points[p3].x, points[p3].y);
    pt d(points[p4].x, points[p4].y);
    return convex(a, b, c, d);
}

} // end of http://codechef.com/download/Images/FEB21/CUTCAKE/generator.cp

Solver *createSolver(string name) {
    if (name == "B") {
        return BestSolver::instance();
    }
    if (name == "S") {
        return SubmarineSolver::instance();
    }
    assert(0);
}

Solution solve(const TestCase* tc) {
    Timer timer;
    Solver* solver = createSolver(SOLVER);
    auto solution = solver->solve(tc);
    return solution;
}

int main(int argc, char **argv) {
    cin.sync_with_stdio(0);
    if (TestCase tc; cin >> tc) {
        Solver *solver = createSolver(SOLVER);
        Solution sol = solver->solve(&tc);
        cout << sol;
        cerr << "Score: " << sol.score() << '\n';
    }
}

ll TestCase::area(const Triangle& t) const {
    return CodeChefGenerator::triangleArea(points, t.p);
}

Solution::Solution(const TestCase* tc) : tc(tc) {
    int n = tc->points.size();
    pointadj.resize(n);
    for (const Triangle& t : tc->triangles) {
        pointadj[t.p[0]].push_back(t.p[1]);
        pointadj[t.p[0]].push_back(t.p[2]);
        pointadj[t.p[1]].push_back(t.p[0]);
        pointadj[t.p[1]].push_back(t.p[2]);
        pointadj[t.p[2]].push_back(t.p[0]);
        pointadj[t.p[2]].push_back(t.p[1]);
    }
    for (vector<int>& adj : pointadj) {
        sortuniq(adj);
    }
    int tn = tc->triangles.size();
    shapes.resize(tn);

    auto joinEdgeShape = [&](Edge e, int shapeId) {
        auto it = edgeadj.find(e);
        if (it == edgeadj.end()) {
            edgeadj[e] = make_pair(-1, -1);
        }
        pair<int, int>& p = edgeadj[e];
        if (p.first == shapeId || p.second == shapeId) return;
        if (p.first != -1 && p.second != -1) {
            assert(0);
        }
        if (p.first == -1) {
            p.first = shapeId;
        }
        else {
            p.second = shapeId;
        }
    };

    for (int i=0; i<tn; i++) {
        shapes[i].id = i;
        const int (&p)[3] = tc->triangles[i].p;
        shapes[i].points.assign(begin(p), end(p));
        shapes[i].area = tc->area(tc->triangles[i]);
        joinEdgeShape(Edge(p[0], p[1]), i);
        joinEdgeShape(Edge(p[1], p[2]), i);
        joinEdgeShape(Edge(p[2], p[0]), i);
    }
}

bool Solution::flip(Edge &edge) {
    auto [id1, id2] = edgeadj[edge];
    if (id2 == -1) return false;
    Shape& s1 = lookupShape(id1);
    Shape& s2 = lookupShape(id2);
    if (s1.id == s2.id) return false;
    if (s1.points.size() != 3) return false;
    if (s2.points.size() != 3) return false;
    int a = edge.p[0];
    int b = edge.p[1];
    assert(contains(s1.points, a));
    assert(contains(s1.points, b));
    assert(contains(s2.points, a));
    assert(contains(s2.points, b));
    int c = -1;
    int d = -1;
    for (int p : s1.points) if (p != a && p != b) c = p;
    for (int p : s2.points) if (p != a && p != b) d = p;
    assert(c != -1);
    assert(d != -1);
    Edge e2(c, d);
    if (flip(Flip{edge, e2})) {
        edge = e2;
        return true;
    }
    return false;
}

bool Solution::flip(Flip flip) {
    auto [a, b] = flip.oldEdge.p;
    auto [c, d] = flip.newEdge.p;

    if (!CodeChefGenerator::convex(tc->points, a, c, b, d)) {
        return false;
    }
    auto [id1, id2] = edgeadj[flip.oldEdge];
    Shape& s1 = lookupShape(id1);
    Shape& s2 = lookupShape(id2);
    if (s1.points.size() != 3) return false;
    if (s2.points.size() != 3) return false;
    assert(contains(pointadj[a], b));
    assert(contains(pointadj[b], a));
    pointadj[a].erase(find(pointadj[a], b));
    pointadj[b].erase(find(pointadj[b], a));

    assert(!contains(pointadj[c], d));
    assert(!contains(pointadj[d], c));
    pointadj[c].push_back(d);
    pointadj[d].push_back(c);
    sortuniq(pointadj[c]);
    sortuniq(pointadj[d]);

    assert(id1 != id2);
    assert(s1.points.size() == 3);
    assert(s2.points.size() == 3);
    assert(contains(s1.points, a));
    assert(contains(s1.points, b));
    assert(contains(s1.points, c) || contains(s1.points, d));
    assert(contains(s2.points, a));
    assert(contains(s2.points, b));
    assert(contains(s2.points, c) || contains(s2.points, d));

    ll oldArea = s1.area + s2.area;

    auto updateEdgeShape = [&](Edge e, int oldId, int newId) {
        pair<int, int>& p = edgeadj[e];
        assert(p.first == oldId || p.second == oldId);
        assert(p.first != newId && p.second != newId);
        if (p.first == oldId) p.first = newId;
        else p.second = newId;
    };

    // replace a-b with c-d
    assert(edgeadj.find(Edge(a, b)) != edgeadj.end());
    assert(edgeadj[Edge(c, d)] == make_pair(0, 0));
    edgeadj.erase(Edge(a, b));
    edgeadj[Edge(c, d)] = make_pair(s1.id, s2.id);

    if (contains(s1.points, c)) {
        swapPoint(s1, b, d); // abc -> acd
        swapPoint(s2, a, c); // abd -> bcd
        updateEdgeShape(Edge(b, c), s1.id, s2.id);
        updateEdgeShape(Edge(a, d), s2.id, s1.id);
    }
    else {
        swapPoint(s2, b, d);
        swapPoint(s1, a, c);
        updateEdgeShape(Edge(b, c), s2.id, s1.id);
        updateEdgeShape(Edge(a, d), s1.id, s2.id);
    }

    ll newArea = s1.area + s2.area;
    assert(oldArea == newArea);

    if (!flips.empty() && flips.back().newEdge == flip.oldEdge) {
        flips.pop_back();
    }
    else {
        flips.push_back(flip);
    }
    return true;
}

void Solution::undoFlip() {
    assert(!flips.empty());
    Edge e = flips.back().newEdge;
    bool ok = flip(e);
    assert(ok);
}

bool Solution::remove(Edge edge) {
    if (complete()) return false;
    auto [a, b] = edge.p;
    assert(contains(pointadj[a], b));
    assert(contains(pointadj[b], a));

    auto [id1, id2] = edgeadj[edge];
    if (id1 == -1 || id2 == -1) {
        return false;
    }
    if (!mergeShapes(id1, id2)) {
        return false;
    }
    deletions.push_back(edge);
    return true;
}

Edge Solution::randomEdge() {
    int a = RNG(0, tc->points.size() - 1);
    int b = RNG(pointadj[a]);
    Edge edge(a, b);
    assert(edgeadj.count(edge) == 1);
    return edge;
}

bool Solution::complete() {
    return tc->triangles.size() - deletions.size() == tc->areas.size();
}

ll Solution::score() {
    if (!complete()) {
        return 1e10;
    }
    vector<ll> areas;
    ll A = tc->areas.size();
    areas.reserve(A);
    for (int i=0; i<shapes.size(); i++) {
        Shape& s = lookupShape(i);
        if (s.id == i) {
            areas.push_back(s.area);
        }
    }
    sort(areas.begin(), areas.end());
    ll result = 0;
    for (int i=0; i<A; i++) {
        result += llabs(tc->areas[i] - areas[i]);
    }
    return result;
}

Shape& Solution::lookupShape(int id) {
    assert(id != -1);
    int id2 = shapes[id].id;
    if (id2 == id) {
        return shapes[id];
    }
    Shape& shape = lookupShape(id2);
    shapes[id].id = shape.id;
    return shape;
}

bool Solution::mergeShapes(int id1, int id2) {
    Shape& s1 = lookupShape(id1);
    Shape& s2 = lookupShape(id2);
    if (s1.id == s2.id) {
        return false;
    }
    ll newId = min(s1.id, s2.id);
    ll oldId = max(s1.id, s2.id);
    vector<int>& oldPoints = shapes[oldId].points;
    vector<int>& newPoints = shapes[newId].points;
    newPoints.reserve(newPoints.size() + oldPoints.size());
    copy(oldPoints.begin(), oldPoints.end(), back_inserter(newPoints));
    sortuniq(newPoints);
    shapes[newId].area += shapes[oldId].area;
    shapes[oldId].points.clear();
    shapes[oldId].id = newId;
    shapes[oldId].area = 0;
    return true;
}

vector<Edge>& Solution::getEdges(vector<Edge>& result, const Shape& shape) {
    result.clear();
    int k = shape.points.size();
    for (int i=0; i<k; i++) {
        for (int j=i+1; j<k; j++) {
            Edge e(shape.points[i], shape.points[j]);
            if (edgeadj.count(e)) {
                result.push_back(e);
            }
        }
    }
    return result;
}

void Solution::swapPoint(Shape& shape, int oldPoint, int newPoint) {
    if (!contains(shape.points, oldPoint)) {
        swap(oldPoint, newPoint);
    }
    assert(contains(shape.points, oldPoint));
    assert(!contains(shape.points, newPoint));
    assert(shape.points.size() == 3);
    auto it = find(shape.points.begin(), shape.points.end(), oldPoint);
    *it = newPoint;
    sortuniq(shape.points);
    shape.area = CodeChefGenerator::triangleArea(tc->points, shape.points.data());
}

istream& operator>>(istream& s, TestCase& tc) {
    int points, triangles, areas;
    if (!(s >> points >> triangles >> areas)) return s;
    tc.points.resize(points);
    for (Point& p : tc.points) {
        if (!(s >> p.x >> p.y)) return s;
    }
    tc.triangles.resize(triangles);
    for (Triangle& t : tc.triangles) {
        for (int& p : t.p) {
            if (!(s >> p)) return s;
            p--;
        }
    }
    tc.areas.resize(areas);
    for (ll& area : tc.areas) {
        if (!(s >> area)) return s;
    }
    return s;
}

ostream& operator<<(ostream& s, Solution& sol) {
    assert(sol.complete());
    s << sol.flips.size() << '\n';
    for (const Flip& f : sol.flips) {
        int a = f.oldEdge.p[0];
        int b = f.oldEdge.p[1];
        s << (a+1) << ' ' << (b+1) << '\n';
    }
    for (const Edge& e : sol.deletions) {
        int a = e.p[0];
        int b = e.p[1];
        s << (a+1) << ' ' << (b+1) << '\n';
    }
    return s;
}

RandomMergeSolver* RandomMergeSolver::instance() { static RandomMergeSolver solver; return &solver; }
PerfectSolver* PerfectSolver::instance() { static PerfectSolver solver; return &solver; }
BestSolver* BestSolver::instance() { static BestSolver solver; return &solver; }
SubmarineSolver* SubmarineSolver::instance() { static SubmarineSolver solver; return &solver; }

Solution RandomMergeSolver::solve(const TestCase* tc) {
    Solution sol(tc);
    while (!sol.complete()) {
        Edge e = sol.randomEdge();
        sol.remove(e);
    }
    return sol;
}

Solution PerfectSolver::solve(const TestCase* tc) {
    Solution sol(tc);
    multiset<ll> targetAreas(tc->areas.begin(), tc->areas.end());
    set<ll> GOOD_AREA(tc->areas.begin(), tc->areas.end());
    set<pair<ll, int>> availShapes;

    static const TestCase* TC = nullptr;
    static vector<Edge> TRY_FLIP;
    static int ATTEMPT = 0;
    if (TC != tc) {
        TC = tc;
        ATTEMPT = 0;
    }
    ATTEMPT++;

    bool DISABLE_FIX = false;
    auto isFixed = [&](Edge e) -> bool {
        auto it = sol.edgeadj.find(e);
        if (it == sol.edgeadj.end()) return true;
        auto [id1, id2] = it->second;
        if (id1==-2 || id2==-1 || id1==id2) return true;
        Shape& s1 = sol.lookupShape(id1);
        Shape& s2 = sol.lookupShape(id2);
        if (s1.id == s2.id) return true;
        if (DISABLE_FIX) return false;
        if (GOOD_AREA.count(s1.area)) return true;
        if (GOOD_AREA.count(s2.area)) return true;
        return false;
    };

    auto shapeIsAvail = [&](int id) -> bool {
        if (id == -1) return false;
        Shape& s = sol.lookupShape(id);
        return availShapes.count(make_pair(s.area, s.id));
    };

    for (const Shape& s : sol.shapes) {
        availShapes.emplace(s.area, s.id);
    }

    vector<Edge> edgebuf;
    auto fixShape = [&](const Shape& s) {
        //cerr << "    FIX SHAPE: " << s << '\n';
        availShapes.erase(make_pair(s.area, s.id));
    };

    auto fixShapeIfTarget = [&](const Shape& s) -> bool {
        auto it = targetAreas.find(s.area);
        if (it == targetAreas.end()) {
            return false;
        }
        targetAreas.erase(it);
        fixShape(s);
        return true;
    };

    vector<Edge> availedgebuf;
    auto availEdges = [&](const Shape& s) -> vector<Edge>& {
        availedgebuf.clear();
        for (const Edge& e : sol.getEdges(edgebuf, s)) {
            if (!isFixed(e)) {
                availedgebuf.push_back(e);
            }
        }
        return availedgebuf;
    };

    auto tryFlip = [&](Edge& e, bool strict=true) -> bool {
        //cerr << "\ntryFlip(" << e << ")\n";
        if (isFixed(e)) {
            //cerr << "tryFlip: " << e << " is fixed\n";
            return false;
        }
        if (!sol.flips.empty() && sol.flips.back().newEdge == e) return false;
        auto [id1, id2] = sol.edgeadj[e];
        Shape old1 = sol.lookupShape(id1);
        Shape old2 = sol.lookupShape(id2);
        if (old1.points.size() != 3) return false;
        if (old2.points.size() != 3) return false;
        Edge e2 = e;
        if (!sol.flip(e2)) {
            //cerr << "tryFlip: " << e << " can't be fipped\n";
            return false;
        }
        const Shape& s1 = sol.lookupShape(id1);
        const Shape& s2 = sol.lookupShape(id2);
        //cerr << "tryFlip: new s1 = " << s1 << '\n';
        //cerr << "tryFlip: new s2 = " << s2 << '\n';
        //cerr << "tryFlip: LAST FLIP = " << sol.flips.back() << '\n';
        int fix = 0;
        int fix1 = fixShapeIfTarget(s1);
        int fix2 = fixShapeIfTarget(s2);
        fix += fix1;
        fix += fix2;
        if (strict && !fix) {
            sol.undoFlip();
            //cerr << "tryFlip: " << e << " did not fix any areas\n";
            auto [a1, a2] = sol.edgeadj[e];
            //cerr << "tryFlip: [a1,a2] = [" << a1 << ',' << a2 << "]\n";
            return false;
        }
        availShapes.erase(make_pair(old1.area, old1.id));
        availShapes.erase(make_pair(old2.area, old2.id));
        if (!fix1) availShapes.insert(make_pair(s1.area, s1.id));
        if (!fix2) availShapes.insert(make_pair(s2.area, s2.id));
        //cerr << "tryFlip: OK " << e << " -> " << e2 << '\n';
        e = e2;
        return true;
    };

    for (const Shape& s : sol.shapes) {
        fixShapeIfTarget(s);
    }

    // Try flipping or removing each edge
    set<Edge> edgequeue;
    auto enqueueEdge = [&](Edge e) {
        auto it = sol.edgeadj.find(e);
        if (it == sol.edgeadj.end()) return;
        auto [id1, id2] = it->second;
        if (id1==id2 || id2==-1) return;
        if (isFixed(e)) return;
        edgequeue.insert(e);
    };
    auto enqueueEdgesOfShape = [&](int id) {
        if (id == -1) return;
        Shape& s = sol.lookupShape(id);
        for (Edge e : availEdges(s)) {
            enqueueEdge(e);
        }
    };

    auto tryEachEdge = [&]() -> bool {
        bool yay = false;
        for (const auto& p : sol.edgeadj) {
            enqueueEdge(p.first);
        }
        while (!edgequeue.empty()) {
            Edge e = *edgequeue.begin();
            edgequeue.erase(edgequeue.begin());
            if (isFixed(e)) continue;
            auto [id1, id2] = sol.edgeadj[e];
            if (id1 == id2) {
                continue;
            }
            assert(id1 != id2);
            assert(id1 != -1);
            assert(id2 != -1);
            if (tryFlip(e)) {
                enqueueEdgesOfShape(id1);
                enqueueEdgesOfShape(id2);
                yay = true;
                continue;
            }

            if (sol.complete()) continue;
            const Shape& t1 = sol.lookupShape(id1);
            const Shape& t2 = sol.lookupShape(id2);
            ll area = t1.area + t2.area;
            auto it = targetAreas.find(area);
            if (it != targetAreas.end()) {
                if (sol.remove(e)) {
                    int fix = 0;
                    fix += fixShapeIfTarget(sol.lookupShape(id1));
                    fix += fixShapeIfTarget(sol.lookupShape(id2));
                    assert(fix);
                    yay = true;
                }
            }
        }
        return yay;
    };

    if (ATTEMPT > 1 && !TRY_FLIP.empty() && RNG(0, 1)) {
        DISABLE_FIX = true;
        shuffle(TRY_FLIP.begin(), TRY_FLIP.end(), RNG.gen);
        int cnt = RNG(0, TRY_FLIP.size());
        cnt = TRY_FLIP.size();
        //cerr << "TRYING FLIPS " << cnt << '\n';
        for (int i=0; i<cnt; i++) {
            Edge e = TRY_FLIP[i];
            if (!sol.edgeadj.count(e)) continue;
            auto [id1, id2] = sol.edgeadj[e];
            if (id1==id2 || id2==-1) continue;
            Shape& s1 = sol.lookupShape(id1);
            Shape& s2 = sol.lookupShape(id2);
            bool ok1 = targetAreas.count(s1.area);
            bool ok2 = targetAreas.count(s2.area);
            if (ok1 || ok2) continue;
            if (tryFlip(e)) {
                //cerr << "FLIPPED " << e << '\n';
                //break;
            }
            else if (!RNG(0, 10) && sol.remove(e)) {
                fixShapeIfTarget(sol.lookupShape(id1));
                fixShapeIfTarget(sol.lookupShape(id2));
            }
        }
        DISABLE_FIX = false;
        //cerr << "TRYING FLIPS DONE\n";
    }

    if (ATTEMPT > 2 && ATTEMPT%3==0) {
        DISABLE_FIX = true;
        tryEachEdge();
        DISABLE_FIX = false;
    }
    tryEachEdge();

    vector<pair<Edge, int>> dfsStack;
    set<int> dfsVisited;
    bool ALL_EDGES = false;
    auto dfs = [&](auto dfs, int d, ll area, Shape& s) -> bool {
        bool good = targetAreas.count(area);
        if (d==0) return good;
        dfsVisited.insert(s.id);
        vector<Edge> edges;
        if (ALL_EDGES) sol.getEdges(edges, s);
        else edges = availEdges(s);
        for (Edge e : edges) {
            auto [id1, id2] = sol.edgeadj[e];
            int id = id1==s.id ? id2 : id1;
            if (id==-1 || dfsVisited.count(id)) continue;
            Shape& s2 = sol.lookupShape(id);
            dfsStack.push_back(make_pair(e, s2.id));
            if (dfs(dfs, d-1, area+s2.area, s2)) {
                return true;
            }
            dfsStack.pop_back();
        }
        if (good) return true;
        dfsVisited.erase(s.id);
        return false;
    };

    auto tryMergesFrom = [&](Shape& s, int maxMerge) -> bool {
        dfsStack.clear();
        if (dfs(dfs, maxMerge-1, s.area, s)) {
            //cerr << "MERGE: " << s;
            //for (int i=0; i<dfsStack.size(); i++) {
            //    cerr << ' ' << sol.lookupShape(dfsStack[i].second);
            //}
            //cerr << '\n';
            for (const auto& p : dfsStack) {
                Edge e = p.first;
                sol.remove(e);
                auto [id1, id2] = sol.edgeadj[e];
                fixShapeIfTarget(sol.lookupShape(id1));
                fixShapeIfTarget(sol.lookupShape(id2));
            }
            return true;
        }
        return false;
    };

    auto tryWeirdMerges = [&]() -> bool {
        bool yay = false;
        ALL_EDGES = true;
        vector<int> perm(sol.shapes.size());
        iota(perm.begin(), perm.end(), 0);
        for (int maxMerge=2; maxMerge<=3; maxMerge++) {
            shuffle(perm.begin(), perm.end(), RNG.gen);
            for (int i : perm) {
                Shape& s = sol.lookupShape(i);
                if (s.id != i) continue;
                yay |= tryMergesFrom(s, maxMerge);
            }
        }
        ALL_EDGES = false;
        return yay;
    };

    if (RNG(0, 1)) tryWeirdMerges();
    auto tryMerges = [&]() -> bool {
        bool yay = false;
        for (int maxMerge=2; maxMerge<=10; maxMerge++) {
            set<pair<ll, int>> shapeQueue(availShapes.begin(), availShapes.end());
            while (!shapeQueue.empty()) {
                auto [area, id] = *shapeQueue.begin();
                shapeQueue.erase(shapeQueue.begin());
                Shape& s = sol.lookupShape(id);
                yay |= tryMergesFrom(s, maxMerge);
            }
        }
        return yay;
    };

    if (RNG(0,1)) tryMerges();
    {
    vector<Edge> edges;
    for (const auto& p : sol.edgeadj) {
        if (!isFixed(p.first)) edges.push_back(p.first);
    }
    for (int i=0, tl=50; i<tl && !sol.complete(); i++) {
        if (sol.flips.size() >= 1000) break;
        if (edges.empty()) {
            //cerr << "OUT OF EDGES\n";
            break;
        }
        shuffle(edges.begin(), edges.end(), RNG.gen);
        int flippos = -1;
        for (int i=0; i<edges.size(); i++) {
            if (tryFlip(edges[i], false)) {
                flippos = i;
                break;
            }
        }
        if (flippos==-1) break;
        auto [id1, id2] = sol.edgeadj[edges[flippos]];
        //cerr << "RANDOM FLIP: " << edges[flippos] << '\n';
        bool yay = false;
        if (!yay) {
            Shape& s1 = sol.lookupShape(id1);
            for (Edge e : availEdges(s1)) {
                if (tryFlip(e)) {
                    yay = true;
                }
            }
            Shape& s2 = sol.lookupShape(id2);
            for (Edge e : availEdges(s2)) {
                if (tryFlip(e)) {
                    yay = true;
                }
            }
        }
        if (i>20) {
            yay |= tryMergesFrom(sol.lookupShape(id1), 10);
            yay |= tryMergesFrom(sol.lookupShape(id2), 10);
        }
        //yay |= tryEachEdge();
        if (yay) {
            tl=i+50;
            edges.clear();
            for (const auto& p : sol.edgeadj) {
                if (!isFixed(p.first)) edges.push_back(p.first);
            }
        }
    }
    }

    tryEachEdge();
    tryWeirdMerges();
    vector<Edge> edges;
    for (const auto& p : sol.edgeadj) {
        Edge e = p.first;
        if (!isFixed(e)) {
            edges.push_back(e);
        }
    }
    shuffle(edges.begin(), edges.end(), RNG.gen);
    for (int i=0; !sol.complete() && i<edges.size(); i++) {
        sol.remove(edges[i]);
    }
    while (!sol.complete()) {
        Edge e = sol.randomEdge();
        sol.remove(e);
    }

    if (sol.score() > 0) {
        TRY_FLIP.clear();
        set<ll> targets(tc->areas.begin(), tc->areas.end());
        for (const auto& p : sol.edgeadj) {
            Edge e = p.first;
            auto [id1, id2] = p.second;
            if (id1!=id2 && id2!=-1) {
                const Shape& s1 = sol.lookupShape(id1);
                const Shape& s2 = sol.lookupShape(id2);
                if (!targets.count(s1.area) && !targets.count(s2.area)) {
                    TRY_FLIP.push_back(e);
                }
            }
        }
    }
    return sol;
}

Solution BestSolver::solve(const TestCase* tc) {
    Timer timer;
    Solution best(tc);
    ll bestScore = best.score();

    auto callSolver = [&](Solver *solver) {
        if (bestScore == 0) return;
        auto sol = solver->solve(tc);
        ll score = sol.score();
        if (score < bestScore) {
            best = move(sol);
            bestScore = score;
            cerr << "[BEST] " << bestScore << '\n';
        }
    };

    while (bestScore>0 && timer.millis()<4000) {
        callSolver(PerfectSolver::instance());
    }
    assert(best.complete());
    ll millis = timer.millis();
    assert(millis <= 4500);

    return best;
}

Solution SubmarineSolver::solve(const TestCase* tc) {
    auto goodSolution = BestSolver::instance()->solve(tc);
    ll goodScore = goodSolution.score();
    int M = goodSolution.deletions.size();
    cerr << "Real score = " << goodScore << '\n';
    assert(goodScore == 0);

    for (int i=0; i<191; i++) {
        Edge e = goodSolution.randomEdge();
        goodSolution.flip(e);
    }
    if (goodSolution.score() > 0) {
        return goodSolution;
    }
    auto dummySolution = RandomMergeSolver::instance()->solve(tc);
    cerr << "Returning dummy solution with score " << dummySolution.score() << '\n';
    return dummySolution;
}
