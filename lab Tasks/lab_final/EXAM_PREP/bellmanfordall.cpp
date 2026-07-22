#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

//////////////////////////////////////////////////////////////////
// EDGE REPRESENTATION
//////////////////////////////////////////////////////////////////
struct Edge{
    int u, v;
    ll w;
};

//////////////////////////////////////////////////////////////////
// 1. STANDARD BELLMAN-FORD (DISTANCE ONLY)
//////////////////////////////////////////////////////////////////
vector<ll> bellmanFord(int n, int src, vector<Edge>& edges){
    vector<ll> dist(n, INF);
    dist[src] = 0;

    for(int i = 1; i <= n - 1; i++){
        bool changed = false;

        for(auto e : edges){
            if(dist[e.u] == INF) continue;

            if(dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }

        if(!changed) break;
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 2. BELLMAN-FORD WITH PATH RECONSTRUCTION
//////////////////////////////////////////////////////////////////
vector<ll> bellmanFordPath(
    int n,
    int src,
    vector<Edge>& edges,
    vector<int>& parent
){
    vector<ll> dist(n, INF);
    parent.assign(n, -1);

    dist[src] = 0;

    for(int i = 1; i <= n - 1; i++){
        bool changed = false;

        for(auto e : edges){
            if(dist[e.u] == INF) continue;

            if(dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                changed = true;
            }
        }

        if(!changed) break;
    }

    return dist;
}

vector<int> getPath(int src, int dst, vector<int>& parent){
    vector<int> path;

    if(src == dst && parent[src] == -1){
        path.push_back(src);
        return path;
    }

    if(parent[dst] == -1) return path;

    for(int v = dst; v != -1; v = parent[v]){
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

//////////////////////////////////////////////////////////////////
// 3. NEGATIVE CYCLE DETECTION (REACHABLE FROM SOURCE)
//////////////////////////////////////////////////////////////////
bool hasNegativeCycle(int n, int src, vector<Edge>& edges){
    vector<ll> dist(n, INF);
    dist[src] = 0;

    for(int i = 1; i <= n - 1; i++){
        for(auto e : edges){
            if(dist[e.u] == INF) continue;

            if(dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    for(auto e : edges){
        if(dist[e.u] == INF) continue;

        if(dist[e.u] + e.w < dist[e.v]){
            return true;
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////
// 4. FIND ONE NEGATIVE CYCLE
//////////////////////////////////////////////////////////////////
vector<int> findNegativeCycle(int n, vector<Edge>& edges){
    vector<ll> dist(n, 0);
    vector<int> parent(n, -1);

    int x = -1;

    for(int i = 1; i <= n; i++){
        x = -1;

        for(auto e : edges){
            if(dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }

    if(x == -1) return {};

    for(int i = 0; i < n; i++){
        x = parent[x];
    }

    vector<int> cycle;
    int cur = x;

    do{
        cycle.push_back(cur);
        cur = parent[cur];
    }while(cur != x);

    cycle.push_back(x);
    reverse(cycle.begin(), cycle.end());

    return cycle;
}

//////////////////////////////////////////////////////////////////
// 5. COUNT SHORTEST PATHS (ONLY SAFE WHEN NO ZERO/NEGATIVE CYCLE
//    ON SHORTEST-PATH DAG)
//////////////////////////////////////////////////////////////////
vector<ll> bellmanFordCountPaths(
    int n,
    int src,
    vector<Edge>& edges,
    vector<ll>& ways
){
    vector<ll> dist(n, INF);
    dist[src] = 0;

    for(int i = 1; i <= n - 1; i++){
        bool changed = false;

        for(auto e : edges){
            if(dist[e.u] == INF) continue;

            if(dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }

        if(!changed) break;
    }

    vector<vector<int>> dag(n);
    vector<int> indeg(n, 0);

    for(auto e : edges){
        if(dist[e.u] == INF) continue;

        if(dist[e.u] + e.w == dist[e.v]){
            dag[e.u].push_back(e.v);
            indeg[e.v]++;
        }
    }

    ways.assign(n, 0);
    ways[src] = 1;

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v : dag[u]){
            ways[v] += ways[u];
            indeg[v]--;

            if(indeg[v] == 0){
                q.push(v);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 6. PRINT ALL SHORTEST PATHS (MULTI-PARENT)
//////////////////////////////////////////////////////////////////
vector<ll> bellmanFordAllParents(
    int n,
    int src,
    vector<Edge>& edges,
    vector<vector<int>>& parents
){
    vector<ll> dist(n, INF);
    dist[src] = 0;
    parents.assign(n, {});

    for(int i = 1; i <= n - 1; i++){
        bool changed = false;

        for(auto e : edges){
            if(dist[e.u] == INF) continue;

            ll nd = dist[e.u] + e.w;

            if(nd < dist[e.v]){
                dist[e.v] = nd;
                parents[e.v].clear();
                parents[e.v].push_back(e.u);
                changed = true;
            }
            else if(nd == dist[e.v]){
                parents[e.v].push_back(e.u);
            }
        }

        if(!changed) break;
    }

    return dist;
}

void printAllShortestPaths(
    int u,
    int src,
    vector<vector<int>>& parents,
    vector<int>& path
){
    if(u == src){
        cout << src << " ";
        for(int i = (int)path.size() - 1; i >= 0; i--){
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int p : parents[u]){
        path.push_back(u);
        printAllShortestPaths(p, src, parents, path);
        path.pop_back();
    }
}

//////////////////////////////////////////////////////////////////
// 7. LONGEST PATH IN A GRAPH WITH POSSIBLE NEGATIVE WEIGHTS
//    (By negating weights and checking for negative cycles)
//////////////////////////////////////////////////////////////////
vector<ll> longestPathUsingBellmanFord(
    int n,
    int src,
    vector<Edge> edges
){
    for(auto &e : edges){
        e.w = -e.w;
    }

    vector<ll> dist = bellmanFord(n, src, edges);

    for(int i = 0; i < n; i++){
        if(dist[i] != INF){
            dist[i] = -dist[i];
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// MAIN (EXAMPLE INPUT)
//////////////////////////////////////////////////////////////////
int main(){
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // Example: standard Bellman-Ford from source 0
    vector<ll> dist = bellmanFord(n, 0, edges);

    for(int i = 0; i < n; i++){
        if(dist[i] == INF) cout << "INF\n";
        else cout << "dist[" << i << "] = " << dist[i] << "\n";
    }

    return 0;
}