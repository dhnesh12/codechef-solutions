#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
 
namespace // private.
{
class Cache {
    std::vector<char>  adj[64];
    std::vector<char>  mag;
    std::vector<char>  idx_to_pos;
    std::vector<char>  pos_to_idx;
    std::vector<long>  res;
    
    void m_add_adjacent(const char* g, int n, int m, int i);
    
public:
    int configure(const char* g, int n, int m);
    size_t hash(const char* g, int pos);
 
    const std::vector<char>& adjacent(int pos) const
        { return adj[pos];
        }
        
    long& result(size_t i)
        { return res[i];
        }
};
 
void Cache::m_add_adjacent(const char* g, int n, int m, int i)
{
    static const char move[] = { 0, -1, 0, 1, 0, -2, 0, 2, 0 };
    
    int x = i / m;
    int y = i % m;
    
    for ( int j = 0; j < 8; j++ ) {
    
        int u = x + move[j];
        int v = y + move[j+1];
        
        if (u >= 0 && u < n && v >= 0 && v < m) {
        
            int k = u * m + v;
            
            if (g[k] != 0) {
                adj[i].push_back(k);
            }
        }
    }
}
 
int Cache::configure(const char* g, int n, int m)
{
    *this = Cache();
    
    unsigned long nstate = 1;
    int ntiles = 0;
    int nvalid = 0;
    
    pos_to_idx.resize(n * m);
    
    for ( int i = 0; i < n * m; i++ ) {
    
        int temp = g[i];
        
        if (temp != 0) {
            m_add_adjacent(g, n, m, i);
            
            mag.push_back(temp);
            pos_to_idx[i] = nvalid;
            idx_to_pos.push_back(i);
            
            nstate *= temp + 1;
            ntiles += temp;
            nvalid += 1;
        }
    }
    
    res.resize(nstate * nvalid, -1L);
    
    return ntiles;
}
 
size_t Cache::hash(const char* g, int pos)
{
    size_t hval = pos_to_idx[pos];
   
    for ( size_t i = mag.size(); i > 0; i-- ) {
        hval = hval * (mag[i-1] + 1) + g[idx_to_pos[i-1]];
    }
   
    return hval;
}
 
long solve_lower(char* g, int pos, int final_pos, int tilesum, Cache& cache)
{
    char& current = g[pos];
    
    if (current == 0) {
        return 0;
    }
    if (tilesum == 1) {
        return (pos == final_pos) ? 1 : 0;
    }
    
    long& result = cache.result(cache.hash(g, pos));
    
    if (result >= 0) {
        return result;
    }
    
    long temp = 0;
    
    current--;
    
    for ( auto next_pos : cache.adjacent(pos) ) {
        temp += solve_lower(g, next_pos, final_pos, tilesum - 1, cache);
    }
 
    current++;
    
    result = temp;
    return result;
}
} // end private.
 
long solve(const char* g, int n, int m, int sx, int sy, int fx, int fy)
{
    char state[64];
    memcpy(state, g, n * m);
 
    Cache cache;
    int tiles = cache.configure(state, n, m);
    int start = sx * m + sy;
    int final = fx * m + fy;
    
    return solve_lower(state, start, final, tiles, cache);
}
 
int main(int argc, char* argv[])
{
    int cases;
    
    std::cin >> cases;
    
    assert(cases >= 1);
    assert(cases <= 5);
    
    for ( int i = 0; i < cases; i++ ) {
    
        int n, m;
        
        std::cin >> n >> m;
        
        assert(n >= 3);
        assert(n <= 8);
        assert(m >= 3);
        assert(m <= 8);
        
        int sx, sy;
        int fx, fy;
        
        std::cin >> sx >> sy;
        std::cin >> fx >> fy;
        
        assert(sx >= 1);
        assert(sx <= n);
        assert(fx >= 1);
        assert(fx <= n);
        assert(sy >= 1);
        assert(sy <= m);
        assert(fy >= 1);
        assert(fy <= m);
        
        char g[64];
        memset(g, 0, 64);
        
        for ( int j = 0; j < m * n; j++ ) {
        
            int temp;
            
            std::cin >> temp;
            g[j] = temp;
        }
        
        long result = solve(g, n, m, sx-1, sy-1, fx-1, fy-1);
        
        std::cout << result << std::endl;
    }
    return 0;
} 
