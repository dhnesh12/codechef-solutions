#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
static const double eps = 1e-8;
struct Point {
    int x, y;
    Point() { }
    Point(int _x, int _y)
        : x(_x)
        , y(_y)
    {
    }
};
long long cross(const Point& a, const Point& b)
{
    return (long long)a.x * b.y - (long long)a.y * b.x;
}
struct Segment {
    Point l, r;
    int down, bel;
    Segment() { }
    Segment(Point _l, Point _r, int _down, int _bel)
        : l(_l)
        , r(_r)
        , down(_down)
        , bel(_bel)
    {
    }
    double gety(double x)
    {
        return l.y + (double)(r.y - l.y) / (r.x - l.x) * (x - l.x);
    }
    bool on(Point p)
    {
        if (p.x < l.x || p.x > r.x)
            return 0;
        return (long long)(p.y - l.y) * (r.x - l.x) == (long long)(r.y - l.y) * (p.x - l.x);
    }
} S[N];
int num;
#define ls ch[0]
#define rs ch[1]
struct Node {
    Node* ch[2];
    int size, id, p;
    Node()
        : size(0)
    {
    }
    void up()
    {
        size = ls->size + rs->size + 1;
    }
} mem[15000010], *P = mem, Tnull, *null = &Tnull;
Node* newnode()
{
    P->ls = P->rs = null;
    P->size = 1;
    P->p = rand();
    return P++;
}
void copy(Node*& x, Node* y)
{
    if (y == null)
        x = null;
    else
        *(x = newnode()) = *y;
}
void Merge(Node*& re, Node* x, Node* y)
{
    if (x == null)
        copy(re, y);
    else if (y == null)
        copy(re, x);
    else if (x->p < y->p) {
        copy(re, x);
        Merge(re->rs, x->rs, y);
        re->up();
    } else {
        copy(re, y);
        Merge(re->ls, x, y->ls);
        re->up();
    }
}
void Split(Node* p, Node*& x, Node*& y, int k)
{
    if (k == 0) {
        copy(x, null);
        copy(y, p);
    } else if (k == p->size) {
        copy(x, p);
        copy(y, null);
    } else if (k <= p->ls->size) {
        copy(y, p);
        Split(p->ls, x, y->ls, k);
        y->up();
    } else {
        copy(x, p);
        Split(p->rs, x->rs, y, k - p->ls->size - 1);
        x->up();
    }
}
Node* find_succ(Node* p, double _x, double _y)
{
    if (p == null)
        return null;
    double y = S[p->id].gety(_x);
    if (y + eps >= _y) {
        Node* temp = find_succ(p->ls, _x, _y);
        return temp == null ? p : temp;
    } else
        return find_succ(p->rs, _x, _y);
}
int calc_down(Node* p, double _x, int id)
{
    if (p == null)
        return 0;
    if (S[id].gety(_x) <= S[p->id].gety(_x))
        return calc_down(p->ls, _x, id);
    else
        return p->ls->size + 1 + calc_down(p->rs, _x, id);
}
Node* insert(Node* p, double _x, int id)
{
    int down = calc_down(p, _x, id);
    Node *x, *y, *re;
    Split(p, x, y, down);
    Node* now = newnode();
    now->id = id;
    Merge(re, x, now);
    Merge(re, re, y);
    return re;
}
Node* cutoff(Node* p, double _x, int id)
{
    int down = calc_down(p, _x, id);
    Node *x, *y, *z, *re;
    Split(p, x, y, down);
    Split(y, y, z, 1);
    Merge(re, x, z);
    return re;
}
Point p[N];
int ux[N];
vector<int> in[N], out[N];
Node* root[N];
int get_ins(Node* p, int x, int y)
{
    static Node* temp;
    temp = find_succ(p, x, y);
    if (temp == null)
        return -1;
    else if (S[temp->id].on(Point(x, y)))
        return S[temp->id].bel;
    else
        return S[temp->id].down;
}
int main()
{
    int n, i, j, t, m = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &t);
        for (j = 1; j <= t; ++j) {
            scanf("%d%d", &p[j].x, &p[j].y);
            ux[++m] = p[j].x;
        }
        p[t + 1] = p[1];
        long long area = 0;
        for (j = 1; j <= t; ++j)
            area += cross(p[j], p[j + 1]);
        if (area < 0) {
            for (j = 1; j <= t; ++j) {
                if (p[j].x < p[j + 1].x)
                    S[++num] = Segment(p[j], p[j + 1], i, i);
                else if (p[j + 1].x < p[j].x)
                    S[++num] = Segment(p[j + 1], p[j], -1, i);
            }
        } else {
            for (j = 1; j <= t; ++j) {
                if (p[j].x < p[j + 1].x)
                    S[++num] = Segment(p[j], p[j + 1], -1, i);
                else if (p[j + 1].x < p[j].x)
                    S[++num] = Segment(p[j + 1], p[j], i, i);
            }
        }
    }
    sort(ux + 1, ux + m + 1);
    int _m = unique(ux + 1, ux + m + 1) - ux - 1;
    for (i = 1; i <= num; ++i) {
        in[lower_bound(ux + 1, ux + _m + 1, S[i].l.x) - ux].push_back(i);
        out[lower_bound(ux + 1, ux + _m + 1, S[i].r.x) - ux].push_back(i);
    }
    for (root[0] = null, i = 1; i <= _m; ++i) {
        root[i] = root[i - 1];
        for (j = 0; j < out[i].size(); ++j)
            root[i] = cutoff(root[i], .5 * (ux[i] + ux[i - 1]), out[i][j]);
        for (j = 0; j < in[i].size(); ++j)
            root[i] = insert(root[i], .5 * (ux[i] + ux[i + 1]), in[i][j]);
    }
    int q, x, y, ans, ins;
    scanf("%d", &q);
    for (i = 1; i <= q; ++i) {
        scanf("%d%d", &x, &y);
        if (x < ux[1] || x > ux[_m])
            ans = -1;
        else {
            ins = lower_bound(ux + 1, ux + _m + 1, x) - ux;
            if (ux[ins] == x)
                ans = max(get_ins(root[ins - 1], x, y), get_ins(root[ins], x, y));
            else
                ans = get_ins(root[ins - 1], x, y);
        }
        printf("%d\n", ans);
        fflush(stdout);
    }
    return 0;
}