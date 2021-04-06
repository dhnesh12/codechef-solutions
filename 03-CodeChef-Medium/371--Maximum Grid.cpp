#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define fin std::cin
#define fout std::cout

#define maxn 100005

struct Point{
    int x, y;
    long long val;
};

bool sortPoints(Point a, Point b){
    return a.x < b.x;
}

std::vector <Point> v;

long long max[4*maxn];
long long lazy[4*maxn];

void update(int node, int left, int right, int l, int r, long long val){
    if(lazy[node] != 0){
        max[node] += lazy[node];
        if(left < right){
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(l <= left and right <= r){
        max[node] += val;
        if(left < right){
            lazy[2*node+1] += val;
            lazy[2*node+2] += val;
        }
        return;
    }
      if(left > r or right < l)
        return;

    int mid = (left + right) / 2;
    update(2*node+1, left, mid, l, r, val);
    update(2*node+2, mid+1, right, l, r, val);
    max[node] = std::max(max[2*node+1], max[2*node+2]);
}

int32_t main(){
    int n, lenght;
    fin >> n >> lenght;

    v.resize(n);
    for(int i=0; i<n; i++)
        fin >> v[i].x >> v[i].y >> v[i].val;
    std::sort(v.begin(), v.end(), sortPoints);

    int l=0, r=0;
    long long maxVal = 0;
    for(int x = lenght; x <= lenght or x <= v[n-1].x; x ++){
        while(r < v.size() and v[r].x <= x){
            update(0, 0, maxn-5, v[r].y-lenght+1, v[r].y, v[r].val);
            r ++;
        }
        while(l < v.size() and v[l].x <= x - lenght){
            update(0, 0, maxn-5, v[l].y-lenght+1, v[l].y, -v[l].val);
            l ++;
        }
        maxVal = std::max(maxVal, max[0]);
    }
    for(int i=0; i<4*maxn; i++){
        max[i] = 0;
        lazy[i] = 0;
    }

    int left = 1, right = lenght, mid;
    long long ans = 0, currMax;
    while(left <= right){
        mid = (left + right) / 2;
        lenght = mid;
        l = r = 0;
        currMax = 0;
        for(int x = lenght; x <= lenght or x <= v[n-1].x; x ++){
            while(r < v.size() and v[r].x <= x){
                update(0, 0, maxn-5, v[r].y-lenght+1, v[r].y, v[r].val);
                r ++;
            }
            while(l < v.size() and v[l].x <= x - lenght){
                update(0, 0, maxn-5, v[l].y-lenght+1, v[l].y, -v[l].val);
                l ++;
            }
            currMax = std::max(currMax, max[0]);
        }
        for(int i=0; i<4*maxn; i++){
            max[i] = 0;
            lazy[i] = 0;
        }

        if(currMax == maxVal){
            ans = mid;
            right = mid - 1;
        }
        else 
            left = mid + 1;

    }


    fout << maxVal << ' ' << ans << '\n';

    return 0;
}