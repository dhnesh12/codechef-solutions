#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
typedef pair<int,int> II;
typedef vector<II> VII;
 
struct Node 
{    vector<int> adj, len;
};
 
struct Edge {
    int u, v, L;
    Edge(int U, int V, int LL) : u(U), v(V), L(LL) {}
};
 
int graph_type(const vector<Node>& nodes) {
    const int N = nodes.size();
    int deg1(0), deg2(0);
    for(int i=0; i<N; ++i) {
        int deg = nodes[i].adj.size();
        deg1 += (deg == 1);
        deg2 += (deg == 2);
    }
    if (deg1 > 900) return 2;
    if (deg1 > 420) return 4;
    return (deg2 > 450) ? 3 : 1;
}
 
UL calculate_raw_score(const VII& p) {
    const int N = p.size();
    UL res = 0;
    for(int i=0; i<N-1; ++i) {
        for(int j=i+1; j<N; ++j) {
            LL x = p[i].first - p[j].first;
            LL y = p[i].second - p[j].second;
            res += x*x + y*y;
        }
    }
    return res;
}
 
LL agg_sum(const II p0, const II p1, const LL k, const LL n) {
    const LL X = p1.first - p0.first;
    const LL Y = p1.second - p0.second;
    return k*n*(((n-1)*((n<<1)-1) + (k-1)*((k<<1)-1)) - 3*(k-1)*(n-1) + 6*(X*(n-k) + X*X + Y*Y))/6;
}
 
LL calculate_fast_score(const VII& p) {
    const int N = p.size();
    int minY(p[0].second), maxY(p[0].second);
    for(int i=1; i<N; ++i) {
        minY = min(minY, p[i].second);
        maxY = max(maxY, p[i].second);
    }
    int K = maxY - minY + 1;
    VII d(K, II(1000000, -1000000));
    for(int i=0; i<N; ++i) {
        int x = p[i].first;
        int y = p[i].second - minY;
        d[y].first = min(d[y].first, x);
        d[y].second = max(d[y].second, x);
    }
    vector<pair<int,II>> b;
    b.reserve(K+1);
    for(int i=0; i<K; ++i) {
        if (i == -minY) {
            b.push_back(pair<int,II>(1,II(d[i].first, i)));
            b.push_back(pair<int,II>(1,II(d[i].second, i)));
        } else {
            b.push_back(pair<int,II>(d[i].second - d[i].first + 1, II(d[i].first, i)));
        }
    }
    LL res = 0;
    for(int i=0; i<K+1; ++i) {
        LL k = b[i].first;
        LL k2 = k*k;
        res += k2*(k2-1)/12;
    }
    for(int i=0; i<K; ++i) {
        for(int j=i+1; j<K+1; ++j) {
            res += agg_sum(b[i].second, b[j].second, b[i].first, b[j].first);
        }
    }
    return res;
}
 
VII solve_simple(const int N, const vector<Node>& nodes) {
    VII res(N);
 
    vector<int> process;
    process.push_back(0);
    int ind = 0;
    vector<int> level;
    level.push_back(0);
 
    res[0] = II(0,0);
    vector<bool> visited(N, false);
    visited[0] = true;
 
    vector<vector<Edge>> edges;
 
    while(ind < process.size()) {
        int index = process[ind];
        int cur_level = level[ind];
        if (edges.size() == cur_level) {
            edges.resize(cur_level+1);
        }
        const Node& node = nodes[index];
        int sz = node.adj.size();
        for(int i=0; i<sz; ++i) {
            int next_index = node.adj[i];
            if (!visited[next_index]) {
                visited[next_index] = true;
                edges[cur_level].push_back(Edge(index, next_index, node.len[i]));
                process.push_back(next_index);
                level.push_back(cur_level+1);
            }
        }
        ++ind;
    }
 
    for(int k=0; k<edges.size(); ++k) {
        int maxL = 0;
        for(int i=0; i<edges[k].size(); ++i) {
            maxL = max(maxL, edges[k][i].L);
        }
        if (maxL) {
            int X = res[edges[k][0].u].first + maxL;
            for (int i = 0; i < edges[k].size(); ++i) {
                res[edges[k][i].v] = II(X, i);
            }
        }
    }
 
    return res;
}
 
int optimize_placement(const int from_index, const int to_index, const vector<Node>& nodes,
                       VII& pos, vector<vector<int>>& layers)
{
    const int N = nodes.size();
    vector<int> to_process;
    const int start_index = to_index;
    to_process.push_back(start_index);
    pos.resize(N);
    pos[start_index] = II(0,0);
    layers.resize(0);
    layers.push_back(to_process);
    if (nodes[start_index].adj.size() == 1) {
        return nodes[start_index].len[0];
    }
 
    vector<Node> lodes(N);
    VII ups;
    for(int i=0; i<nodes[start_index].adj.size(); ++i) {
        int next_index = nodes[start_index].adj[i];
        if (next_index != from_index) {
            ups.push_back(II(nodes[start_index].len[i], next_index));
        }
    }
    sort(ups.begin(), ups.end());
    for(int i=0; i<ups.size(); ++i) {
        lodes[start_index].adj.push_back(ups[i].second);
        lodes[start_index].len.push_back(ups[i].first);
    }
 
    int layer = 1;
    while (to_process.size()) {
        vector<int> next_process;
        vector<int> next_layer;
        vector<pair<int, II>> next_line;
        int x_bound = (layer & 1) ? -100000000 : 100000000;
        for(int k = 0; k < to_process.size(); ++k) {
            int index = to_process[k];
            const Node &bnode = lodes[index];
            for (int i = 0; i < bnode.adj.size(); ++i) {
                int next_index = bnode.adj[i];
                if (((index == 41) && (next_index == 791)) || ((index == 791) && (next_index == 41))) {
                    int fff = 444;
                    ++fff;
                }
 
                int next_len = 5000;
                int cur_X = pos[index].first;
                int next_X = (layer & 1) ? max(cur_X + next_len, x_bound + 1)
                                         : min(cur_X - next_len, x_bound - 1);
                x_bound = next_X;
                pos[next_index] = II(next_X, layer);
                ups.resize(0);
                for (int j = 0; j < nodes[next_index].adj.size(); ++j) {
                    int ch_index = nodes[next_index].adj[j];
                    if (ch_index != index) {
                        ups.push_back(II(nodes[next_index].len[j], nodes[next_index].adj[j]));
                    }
                }
                sort(ups.begin(), ups.end());
                Node &node = lodes[next_index];
                for (int j = 0; j < ups.size(); ++j) {
                    node.adj.push_back(ups[j].second);
                    node.len.push_back(ups[j].first);
                }
                if (ups.size()) {
                    next_process.push_back(next_index);
                }
                next_layer.push_back(next_index);
                next_line.push_back(pair<int,II>(next_index, II(bnode.len[i], abs(cur_X - pos[next_index].first))));
            }
        }
        int excess = next_line.back().second.second - next_line.back().second.first;
        int lastX = pos[next_line.back().first].first;
        int inc_dir = (layer&1) ? -1 : 1;
        for(int propX = lastX + inc_dir, j=next_line.size()-2; j>=0; --j, propX += inc_dir) {
            int curX = pos[next_line[j].first].first;
            int diffX = abs(propX - curX);
            pos[next_line[j].first].first = propX;
            next_line[j].second.second += diffX;
            excess = min(excess, next_line[j].second.second - next_line[j].second.first);
        }
        for(int i=0; i<next_line.size(); ++i) {
            pos[next_line[i].first].first += inc_dir*excess;
        }
        reverse(next_process.begin(), next_process.end());
        reverse(next_layer.begin(), next_layer.end());
        swap(to_process, next_process);
        if (next_layer.size())
            layers.push_back(next_layer);
        ++layer;
    }
 
    int widest_index = 1;
    int widest_bound = pos[lodes[start_index].adj.back()].first;
    if (layers.size() == 1) {
        return widest_bound;
    }
 
    for(int k=2; k<layers.size(); ++k) {
        int cur_bound = abs(pos[layers[k-1].front()].first - pos[layers[k].front()].first);
        if (cur_bound > widest_bound) {
            widest_bound = cur_bound;
            widest_index = k;
        }
    }
 
    int max_X = max(pos[layers[widest_index].front()].first, pos[layers[widest_index-1].front()].first);
    int min_X = min(pos[layers[widest_index].front()].first, pos[layers[widest_index-1].front()].first);
    int offsetX = 0;
    for(int k=widest_index-2; k>0; --k) {
        if (pos[layers[k-1].front()].first + offsetX > max_X) {
            offsetX = max_X - pos[layers[k-1].front()].first;
        } else if (pos[layers[k-1].front()].first + offsetX < min_X) {
            offsetX = min_X - pos[layers[k-1].front()].first;
        }
        int sz = layers[k].size();
        for(int i=0; i<sz; ++i) {
            pos[layers[k][i]].first += offsetX;
        }
    }
    pos[start_index].first += offsetX;
    offsetX = 0;
    for(int k=widest_index+2; k<layers.size(); ++k) {
        if (pos[layers[k].front()].first + offsetX > max_X) {
            offsetX = max_X - pos[layers[k].front()].first;
        } else if (pos[layers[k].front()].first + offsetX < min_X) {
            offsetX = min_X - pos[layers[k].front()].first;
        }
        int sz = layers[k-1].size();
        for(int i=0; i<sz; ++i) {
            pos[layers[k-1][i]].first += offsetX;
        }
    }
    for(int k=0; k<layers.back().size(); ++k) {
        pos[layers.back()[k]].first += offsetX;
    }
 
    min_X = pos[start_index].first;
    for(int k=1; k<layers.size(); ++k) {
        for(int i=0; i<layers[k].size(); ++i) {
            min_X = min(min_X, pos[layers[k][i]].first);
        }
    }
    for(int k=0; k<layers.size(); ++k) {
        for(int i=0; i<layers[k].size(); ++i) {
            pos[layers[k][i]].first -= min_X;
        }
    }
 
    return widest_bound;
}
 
void compress(const int N, const vector<Node>& nodes, VII& pos) {
    map<int, VII> d;
    for(int i=0; i<N; ++i) {
        d[pos[i].second].push_back(II(pos[i].first, i));
    }
    for(auto it = d.begin(); it != d.end(); ++it) {
        sort(it->second.begin(), it->second.end());
        if (((it->first > 0) && (it->first&1)) || ((it->first < 0) && ((-it->first)%2 == 0))) {
            const VII& ip = it->second;
            const int sz = ip.size();
            for(int i=0; i<sz; ++i) {
                int v = ip[i].second;
                int slack = 1000000;
                int p0x = pos[v].first;
                for(int j=0; j<nodes[v].adj.size(); ++j) {
                    slack = min(slack, p0x - pos[nodes[v].adj[j]].first - nodes[v].len[j]);
                }
                if (i) {
                    slack = min(slack, p0x - pos[ip[i-1].second].first - 1);
                }
                pos[v].first -= slack;
            }
        }
    }
    for(auto it = d.begin(); it != d.end(); ++it) {
        if (((it->first > 0) && (it->first%2 == 0)) || ((it->first < 0) && ((-it->first)&1))) {
            const VII& ip = it->second;
            const int sz = ip.size();
            for(int i=sz-1; i>=0; --i) {
                int v = ip[i].second;
                int slack = 1000000;
                int p0x = pos[v].first;
                for(int j=0; j<nodes[v].adj.size(); ++j) {
                    slack = min(slack, pos[nodes[v].adj[j]].first - p0x - nodes[v].len[j]);
                }
                if (i < sz-1) {
                    slack = min(slack, pos[ip[i+1].second].first - p0x - 1);
                }
                pos[v].first += slack;
            }
        }
    }
    auto fit = d.begin();
    auto sit = fit;
    ++sit;
    if ((fit->second.size() == 1) && (sit->second.size() == 1)) {
        pos[fit->second[0].second].second += 1;
    }
    auto rfit = d.rbegin();
    auto rsit = rfit;
    ++rsit;
    if ((rfit->second.size() == 1) && (rsit->second.size() == 1)) {
        pos[rfit->second[0].second].second -= 1;
    }
    if ((d[0].size() == 2) && (d.find(1) != d.end()) && (d.find(-1) != d.end())) {
        if ((pos[d[1].back().second].first < pos[d[0].back().second].first)
            && (pos[d[-1].front().second].first > pos[d[0].front().second].first)) {
            pos[d[0].back().second].second += 1;
            for (auto it = d.begin(); (it != d.end()) && (it->first < 0); ++it) {
                const VII &ip = it->second;
                const int sz = ip.size();
                for (int i = 0; i < sz; ++i) {
                    pos[ip[i].second].second += 1;
                }
            }
        }
    }
}
 
void dfs_for_compress(const int from_index, const int to_index, const vector<Node>& nodes, vector<bool>& subtree) {
    subtree[to_index] = true;
    const Node& node = nodes[to_index];
    const int sz = node.adj.size();
    for(int i=0; i<sz; ++i) {
        const int next_index = node.adj[i];
        if (next_index != from_index) {
            dfs_for_compress(to_index, next_index, nodes, subtree);
        }
    }
}
 
int compress(const int from_index, const int N, const vector<Node>& nodes, VII& pos, const vector<vector<int>>& layers) {
    map<int, VII> d;
    for(int i=0; i<layers.size(); ++i) {
        for(int j=0; j<layers[i].size(); ++j) {
            int index = layers[i][j];
            d[pos[index].second].push_back(II(pos[index].first, index));
        }
    }
    for(auto it = d.begin(); it != d.end(); ++it) {
        if (it->first&1) {
            const VII& ip = it->second;
            const int sz = ip.size();
            for(int i=sz-1; i>=0; --i) {
                int v = ip[i].second;
                int slack = 1000000;
                int p0x = pos[v].first;
                for(int j=0; j<nodes[v].adj.size(); ++j) {
                    slack = min(slack, p0x - pos[nodes[v].adj[j]].first - nodes[v].len[j]);
                }
                if (i != sz-1) {
                    slack = min(slack, p0x - pos[ip[i+1].second].first - 1);
                }
                pos[v].first -= slack;
            }
        }
    }
    for(auto it = d.begin(); it != d.end(); ++it) {
        if (it->first%2 == 0) {
            const VII& ip = it->second;
            const int sz = ip.size();
            for(int i=sz-1; i>=0; --i) {
                int v = ip[i].second;
                int slack = 1000000;
                int p0x = pos[v].first;
                for(int j=0; j<nodes[v].adj.size(); ++j) {
                    if (nodes[v].adj[j] != from_index)
                        slack = min(slack, pos[nodes[v].adj[j]].first - p0x - nodes[v].len[j]);
                }
                if (i < sz-1) {
                    slack = min(slack, pos[ip[i+1].second].first - p0x - 1);
                }
                pos[v].first += slack;
            }
        }
    }
    auto rfit = d.rbegin();
    auto rsit = rfit;
    ++rsit;
    if ((rfit->second.size() == 1) && (rsit->second.size() == 1)) {
        pos[rfit->second[0].second].second -= 1;
    }
 
    int minX(1000000), maxX(-1000000);
    for(int i=0; i<layers.size(); ++i) {
        for (int j = 0; j < layers[i].size(); ++j) {
            int index = layers[i][j];
            int p = pos[index].first;
            minX = min(minX, p);
            maxX = max(maxX, p);
        }
    }
    for(int i=0; i<layers.size(); ++i) {
        for (int j = 0; j < layers[i].size(); ++j) {
            int index = layers[i][j];
            pos[index].first -= minX;
        }
    }
    return maxX - minX;
}
 
VII solve_type1(const int N, const vector<Node>& nodes, const double time_limit)
{
    double time_start = double(clock())/CLOCKS_PER_SEC;
    vector<pair<LL, VII>> poses;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<nodes[i].adj.size(); ++j) {
            int v = nodes[i].adj[j];
            if (i<v) {
                int L0 = nodes[i].len[j];
                VII pos1, pos2;
                vector<vector<int>> layers1, layers2;
                optimize_placement(i, v, nodes, pos1, layers1);
                int L2 = optimize_placement(v, i, nodes, pos2, layers2);
 
                VII pos(pos1);
                for(int k=0; k<layers2.size(); ++k) {
                    for(int i=0; i<layers2[k].size(); ++i) {
                        II p = pos2[layers2[k][i]];
                        pos[layers2[k][i]] = II(L2 - p.first, -p.second);
                    }
                }
                if (pos[i].first - pos[v].first < L0) {
                    if (pos[i].first < L0) {
                        pos[v].first = 0;
                        pos[i].first = L0;
                    } else {
                        pos[v].first = pos[i].first - L0;
                    }
                }
                LL cur_score = calculate_fast_score(pos);
                poses.push_back(pair<LL, VII>(cur_score, pos));
            }
        }
    }
 
    sort(poses.begin(), poses.end());
    VII best_pos(poses[0].second);
    compress(N, nodes, best_pos);
    LL best_score = calculate_raw_score(best_pos);
    for(int i=1; (i<poses.size()) && (double(clock())/CLOCKS_PER_SEC - time_start < time_limit); ++i) {
        VII pos = poses[i].second;
        compress(N, nodes, pos);
        LL score = calculate_raw_score(pos);
        if (score < best_score) {
            best_score = score;
            best_pos = pos;
        }
    }
 
    return best_pos;
}
 
void flip(const vector<vector<int>>& layers, const int y_offset, const int sp, VII& pos) {
    for(int i=0; i<layers.size(); ++i) {
        for(int j=0; j<layers[i].size(); ++j) {
            int index = layers[i][j];
            pos[index].second = -pos[index].second - y_offset;
            if (sp) {
                pos[index].first = sp - pos[index].first;
            }
        }
    }
}
 
void optimize_offset(const vector<vector<int>>& layers1, VII& pos1,
                     const vector<vector<int>>& layers2, VII& pos2)
{
    LL sum1 = 0;
    int count1 = 0;
    for(int i=0; i<layers1.size(); ++i) {
        count1 += layers1[i].size();
        for(int j=0; j<layers1[i].size(); ++j) {
            sum1 += pos1[layers1[i][j]].first;
        }
    }
    double ave1 = sum1/double(count1);
 
    LL sum2 = 0;
    int count2 = 0;
    for(int i=0; i<layers2.size(); ++i) {
        count2 += layers2[i].size();
        for(int j=0; j<layers2[i].size(); ++j) {
            sum2 += pos2[layers2[i][j]].first;
        }
    }
    double ave2 = sum2/double(count2);
 
    if (ave1 <= ave2) {
        double diff = ave2 - ave1;
        if (diff > 0.5) {
            int offset = diff + 0.5;
            for(int i=0; i<layers1.size(); ++i) {
                for(int j=0; j<layers1[i].size(); ++j) {
                    pos1[layers1[i][j]].first += offset;
                }
            }
        }
    } else {
        double diff = ave1 - ave2;
        if (diff > 0.5) {
            int offset = diff + 0.5;
            for(int i=0; i<layers2.size(); ++i) {
                for(int j=0; j<layers2[i].size(); ++j) {
                    pos2[layers2[i][j]].first += offset;
                }
            }
        }
    }
}
 
VII solve_type3(const int N, const vector<Node>& nodes) {
    VII res(N);
 
    vector<bool> accounted(N, false);
    vector<vector<int>> chains;
    for(int i=0; i<N; ++i) {
        if ((nodes[i].adj.size() == 2) && (!accounted[i])) {
            accounted[i] = true;
            vector<int> d(1, i);
            d.push_back(nodes[i].adj[0]);
            accounted[d.back()] = true;
            while(nodes[d.back()].adj.size() == 2) {
                int v = nodes[d.back()].adj[0];
                int u = nodes[d.back()].adj[1];
                d.push_back((v == d[d.size()-2]) ? u : v);
                accounted[d.back()] = true;
            }
            reverse(d.begin(), d.end());
            d.push_back(nodes[i].adj[1]);
            accounted[d.back()] = true;
            while(nodes[d.back()].adj.size() == 2) {
                int v = nodes[d.back()].adj[0];
                int u = nodes[d.back()].adj[1];
                d.push_back((v == d[d.size()-2]) ? u : v);
                accounted[d.back()] = true;
            }
            chains.push_back(d);
        }
    }
    int longest_index = 0;
    int longest_len = chains[0].size();
    for(int i=1; i<chains.size(); ++i) {
        if (chains[i].size() > longest_len) {
            longest_len = chains[i].size();
            longest_index = i;
        }
    }
    const vector<int>& the_chain = chains[longest_index];
    if (the_chain.size() < 300) abort();
 
    const int ch0 = the_chain[0];
    const int ch1 = the_chain[1];
    const int ch10 = the_chain.back();
    const int ch11 = the_chain[the_chain.size()-2];
 
    VII pos1, pos2;
    vector<vector<int>> layers1, layers2;
    optimize_placement(ch1, ch0, nodes, pos1, layers1);
    optimize_placement(ch11, ch10, nodes, pos2, layers2);
    int L1 = compress(ch1, N, nodes, pos1, layers1);
    int L2 = compress(ch11, N, nodes, pos2, layers2);
 
 
    int max_chain_len = 0;
    vector<bool> chain_nodes(N, false);
    for(int i=0; i<the_chain.size(); ++i) {
        chain_nodes[the_chain[i]] = true;
    }
    for(int i=0; i<N; ++i) {
        if (chain_nodes[i]) {
            const Node& node = nodes[i];
            for(int j=0; j<node.adj.size(); ++j) {
                if (chain_nodes[node.adj[j]]) {
                    max_chain_len = max(max_chain_len, node.len[j]);
                }
            }
        }
    }
 
    const bool chain_odd = the_chain.size()&1;
    if (chain_odd) { // odd length chain
        int half_count = the_chain.size() / 2;
        flip(layers2, half_count, 0, pos2);
        optimize_offset(layers1, pos1, layers2, pos2);
    } else {
        int half_count = the_chain.size() / 2 - 1;
        flip(layers2, half_count, L2, pos2);
        optimize_offset(layers1, pos1, layers2, pos2);
    }
 
    res = pos1;
    for(int i=0; i<layers2.size(); ++i) {
        for(int j=0; j<layers2[i].size(); ++j) {
            int index = layers2[i][j];
            res[index] = pos2[index];
        }
    }
    LL sum = 0;
    for(int i=0; i<N; ++i) {
        if (!chain_nodes[i]) {
            sum += res[i].first;
        }
    }
    int ave = sum/(N-the_chain.size());
 
    int ch1L = (nodes[ch1].adj[0] == ch0) ? nodes[ch1].len[0] : nodes[ch1].len[1];
    int ch11L = (nodes[ch11].adj[0] == ch10) ? nodes[ch11].len[0] : nodes[ch11].len[1];
 
    for(int i=1; i<the_chain.size()-1; ++i) {
        int index = the_chain[i];
        int vL = nodes[index].len[0];
        int uL = nodes[index].len[1];
        if (i & 1) {
            res[index].first = ave + max(vL, uL) / 2 + 1;
        } else {
            res[index].first = ave - max(vL, uL) / 2 - 1;
        }
        int iX = res[index].first;
        res[index].second = -(i / 2);
    }
    if (res[ch1].first - res[ch0].first < ch1L) {
        res[ch0].first = res[ch1].first - ch1L;
    }
 
    if (chain_odd) {
        if (res[ch11].first - res[ch10].first < ch11L) {
            res[ch10].first = res[ch11].first - ch11L;
        }
    } else {
        if (res[ch10].first - res[ch11].first < ch11L) {
            res[ch10].first = res[ch11].first + ch11L;
        }
    }
 
    for(int i=1; i<the_chain.size()-1; ++i) {
        int index = the_chain[i];
        int v = nodes[index].adj[0];
        int u = nodes[index].adj[1];
        int vL = nodes[index].len[0];
        int uL = nodes[index].len[1];
        int iX = res[index].first;
        int uX = res[u].first;
        int vX = res[v].first;
        if (abs(iX - uX) < uL) {
            abort();
        }
        if (abs(iX - vX) < vL) {
            abort();
        }
        if (i & 1) {
            int propX = max(uX + uL, vX + vL);
            if (propX < iX) {
                res[index].first = propX;
            }
        } else {
            int propX = min(uX - uL, vX - vL);
            if (propX > iX) {
                res[index].first = propX;
            }
        }
    }
 
    return res;
}
 
vector<map<int,vector<int>>> dfs_graph_combos(const int from_index, const int to_index, const vector<Node>& nodes) {
    vector<map<int,vector<int>>> res;
    vector<int> kids;
    for(int i=0; i<nodes[to_index].adj.size(); ++i) {
        if (nodes[to_index].adj[i] != from_index) {
            kids.push_back(nodes[to_index].adj[i]);
        }
    }
    int num_kids = kids.size();
    if (num_kids == 0) {
        return res;
    }
 
    vector<int> perm(num_kids);
    for(int i=0; i<num_kids; ++i) {
        perm[i] = i;
    }
    do {
        vector<int> v(num_kids);
        for(int i=0; i<num_kids; ++i) {
            v[i] = kids[perm[i]];
        }
        map<int,vector<int>> m;
        m[to_index] = v;
        res.push_back(m);
    } while (next_permutation(perm.begin(), perm.end()));
 
    for(int k=0; k<num_kids; ++k) {
        vector<map<int,vector<int>>> next_res;
        vector<map<int,vector<int>>> m = dfs_graph_combos(to_index, kids[k], nodes);
        if (m.size() == 0) continue;
        for(int i=0; i<res.size(); ++i) {
            for(int j=0; j<m.size(); ++j) {
                map<int,vector<int>> combo = res[i];
                for(auto it = m[j].begin(); it != m[j].end(); ++it) {
                    combo[it->first] = it->second;
                }
                next_res.push_back(combo);
            }
        }
        swap(next_res, res);
    }
 
    return res;
};
 
vector<map<int,vector<int>>> get_graph_combos(const Edge& e, const vector<Node>& nodes) {
    vector<map<int,vector<int>>> m1 = dfs_graph_combos(e.u, e.v, nodes);
    vector<map<int,vector<int>>> m2 = dfs_graph_combos(e.v, e.u, nodes);
 
    vector<map<int,vector<int>>> res;
    for(int i=0; i<m1.size(); ++i) {
        for(int j=0; j<m2.size(); ++j) {
            map<int,vector<int>> combo = m1[i];
            for(auto it = m2[j].begin(); it != m2[j].end(); ++it) {
                combo[it->first] = it->second;
            }
            res.push_back(combo);
        }
    }
    return res;
};
 
int combo_random(int i) { return rand()%i; }
struct GraphCombo {
    int u, v;
    map<int, vector<int>> m;
    GraphCombo(const int U, const int V, const map<int, vector<int>>& M) : u(U), v(V), m(M) {}
};
 
int optimize_placement(GraphCombo combo, const vector<Node>& nodes, const vector<Node>& snodes,
                       const vector<bool>& core, VII& pos, vector<vector<int>>& layers)
{
    const int N = nodes.size();
    const int from_index = combo.u;
    const int to_index = combo.v;
    if (!core[from_index] || !core[to_index]) abort();
 
    vector<int> to_process;
    const int start_index = to_index;
    to_process.push_back(start_index);
    pos.resize(N);
    pos[start_index] = II(0,0);
    layers.resize(0);
    layers.push_back(to_process);
 
    vector<Node> lodes(N);
    VII ups;
    for(int i=0; i<nodes[start_index].adj.size(); ++i) {
        int next_index = nodes[start_index].adj[i];
        if ((next_index != from_index) && (!core[next_index])) {
            ups.push_back(II(nodes[start_index].len[i], next_index));
        }
    }
    sort(ups.begin(), ups.end());
    int max_len = ups.back().first;
    for(int i=0; i<combo.m[start_index].size(); ++i) {
        ups.push_back(II(max_len+i+1, combo.m[start_index][i]));
    }
    for(int i=0; i<ups.size(); ++i) {
        lodes[start_index].adj.push_back(ups[i].second);
        lodes[start_index].len.push_back(ups[i].first);
    }
 
    int layer = 1;
    while (to_process.size()) {
        vector<int> next_process;
        vector<int> next_layer;
        vector<pair<int, II>> next_line;
        int x_bound = (layer & 1) ? -100000000 : 100000000;
        for(int k = 0; k < to_process.size(); ++k) {
            int index = to_process[k];
            const Node &bnode = lodes[index];
            for (int i = 0; i < bnode.adj.size(); ++i) {
                int next_index = bnode.adj[i];
 
                int next_len = 5000;
                int cur_X = pos[index].first;
                int next_X = (layer & 1) ? max(cur_X + next_len, x_bound + 1)
                                         : min(cur_X - next_len, x_bound - 1);
                x_bound = next_X;
                pos[next_index] = II(next_X, layer);
                ups.resize(0);
                for (int j = 0; j < nodes[next_index].adj.size(); ++j) {
                    int ch_index = nodes[next_index].adj[j];
                    if ((ch_index != index) && !core[ch_index]){
                        ups.push_back(II(nodes[next_index].len[j], nodes[next_index].adj[j]));
                    }
                }
                sort(ups.begin(), ups.end());
                if (core[next_index]) {
                    max_len = ups.back().first;
                    for(int j=0; j<combo.m[next_index].size(); ++j) {
                        ups.push_back(II(max_len+j+1, combo.m[next_index][j]));
                    }
                }
                Node &node = lodes[next_index];
                for (int j = 0; j < ups.size(); ++j) {
                    node.adj.push_back(ups[j].second);
                    node.len.push_back(ups[j].first);
                }
                if (ups.size()) {
                    next_process.push_back(next_index);
                }
                next_layer.push_back(next_index);
                next_line.push_back(pair<int,II>(next_index, II(bnode.len[i], abs(cur_X - pos[next_index].first))));
            }
        }
        int excess = next_line.back().second.second - next_line.back().second.first;
        int lastX = pos[next_line.back().first].first;
        int inc_dir = (layer&1) ? -1 : 1;
        for(int propX = lastX + inc_dir, j=next_line.size()-2; j>=0; --j, propX += inc_dir) {
            int curX = pos[next_line[j].first].first;
            int diffX = abs(propX - curX);
            pos[next_line[j].first].first = propX;
            next_line[j].second.second += diffX;
            excess = min(excess, next_line[j].second.second - next_line[j].second.first);
        }
        for(int i=0; i<next_line.size(); ++i) {
            pos[next_line[i].first].first += inc_dir*excess;
        }
        reverse(next_process.begin(), next_process.end());
        reverse(next_layer.begin(), next_layer.end());
        swap(to_process, next_process);
        if (next_layer.size())
            layers.push_back(next_layer);
        ++layer;
    }
 
    return compress(from_index, N, nodes, pos, layers);
}
 
VII solve_type2(const int N, const vector<Node>& nodes, const int seed, double time_limit) {
    VII res(N);
    LL best_score = 0;
 
    vector<Edge> sedges;
    vector<Node> snodes(N);
    vector<bool> core_nodes(N, false);
    map<II,int> edge_len;
    for(int i=0; i<N; ++i) {
        core_nodes[i] = nodes[i].adj.size() > 1;
    }
    for(int i=0; i<N; ++i) {
        const int sz = nodes[i].adj.size();
        if (sz > 1) {
            for(int j=0; j<sz; ++j) {
                int v = nodes[i].adj[j];
                if ((i<v) && core_nodes[v]) {
                    const int L = nodes[i].len[j];
                    sedges.push_back(Edge(i, v, L));
                    edge_len[II(i,v)] = L;
                    edge_len[II(v,i)] = L;
                    snodes[i].adj.push_back(v);
                    snodes[v].adj.push_back(i);
                    snodes[i].len.push_back(L);
                    snodes[v].len.push_back(L);
                }
            }
        }
    }
 
    vector<GraphCombo> combos;
    for(int i=0; i<sedges.size(); ++i) {
        vector<map<int,vector<int>>> m = get_graph_combos(sedges[i], snodes);
        for(int j=0; j<m.size(); ++j) {
            combos.push_back(GraphCombo(sedges[i].u, sedges[i].v, m[j]));
        }
    }
    srand(seed);
    random_shuffle(combos.begin(), combos.end(), combo_random);
 
    double time_start = double(clock())/CLOCKS_PER_SEC;
    for(int i=0; (i<combos.size()) && (double(clock())/CLOCKS_PER_SEC - time_start < time_limit); ++i) {
        VII pos1, pos2;
        vector<vector<int>> layers1, layers2;
        int L1 = optimize_placement(combos[i], nodes, snodes, core_nodes, pos1, layers1);
        swap(combos[i].u, combos[i].v);
        int L2 = optimize_placement(combos[i], nodes, snodes, core_nodes, pos2, layers2);
        swap(combos[i].u, combos[i].v);
 
        flip(layers2, 0, L2, pos2);
        optimize_offset(layers1, pos1, layers2, pos2);
        int u = layers1[0][0];
        int v = layers2[0][0];
        int L0 = edge_len[II(u, v)];
        if (L0 > abs(pos1[u].first - pos2[v].first)) {
            int offset = (L0 - abs(pos1[u].first - pos2[v].first))/2 + 1;
            pos1[u].first -= offset;
            pos2[v].first += offset;
        }
        int offset_y = ((pos1[u].first < pos2[layers2[1][0]].first)
                        && (pos2[v].first > pos1[layers1[1][0]].first)) ? 1 : 0;
        for(int k=0; k<layers2.size(); ++k) {
            for(int j=0; j<layers2[k].size(); ++j) {
                int index = layers2[k][j];
                pos1[index] = pos2[index];
                pos1[index].second += offset_y;
            }
        }
 
        LL score = calculate_raw_score(pos1);
        if ((best_score == 0) || (score < best_score)) {
            best_score = score;
            res = pos1;
        }
    }
 
    return res;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int N;
    cin >> N;
    vector<Node> nodes(N);
    for(int i=1; i<N; ++i) {
        int u, v, L;
        cin >> u >> v >> L;
        --u; --v;
        nodes[u].adj.push_back(v);
        nodes[u].len.push_back(L);
        nodes[v].adj.push_back(u);
        nodes[v].len.push_back(L);
    }
    int det_type = graph_type(nodes);
    VII res = (N < 100) ? solve_simple(N, nodes) :
              (((det_type == 1) || (det_type == 4)) ? solve_type1(N, nodes, 1.9) :
               ((det_type == 2) ? solve_type2(N, nodes, 12345, 1.9) : solve_type3(N, nodes)));
    for(int i=0; i<N; ++i) {
        cout << res[i].first << " " << res[i].second << "\n";
    }
 
    return 0;
} 